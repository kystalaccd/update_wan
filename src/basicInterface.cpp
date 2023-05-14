#include "basicInterface.hpp"

namespace micagent{

void basicInterface::run(void){
    _running.exchange(true);
    mg_mgr_init(&_mgr);
#ifdef _DEBUG_
mg_log_set(MG_LL_DEBUG);
#endif
    union handler_param fn_data{_running};
    _connection = mg_ws_connect(&_mgr, _url, _handler, &fn_data, WEBSOCKET_HEADER); 
    while(_connection && _running){
        mg_mgr_poll(&_mgr, POLLDELAY);
    }
    mg_mgr_free(&_mgr);
} 

void basicInterface::_handler(struct mg_connection* c, int ev, void* ev_data, void* fn_data){
    if (ev == MG_EV_OPEN) {
        c->is_hexdumping = 1;
    } else if (ev == MG_EV_ERROR) {
        MG_ERROR(("%p %s", c->fd, (char *) ev_data));
    } else if (ev == MG_EV_WS_OPEN) {
        //设备上线注册
        struct deviceInfo di;
        CJsonObject deviceinfo(di.getDeviceJson());

        //测试版本，设备注册协议号为1010
        interfaceMap[1010].parser(c, deviceinfo);
    } else if (ev == MG_EV_WS_MSG) {
        //解析报文信息
        struct mg_ws_message *wm = (struct mg_ws_message *) ev_data;
        CJsonObject wsMsg(string(wm->data.ptr));
        protocolCode MsgCode;
        CJsonObject MsgContent;

        if(_getMsgType(wsMsg, MsgCode) && _getMsgContent(wsMsg, MsgContent)){
            interfaceMap[MsgCode].parser(c, MsgContent);    //具体的处理行为
        }
        else{
            //无效的控制报文, 测试版本等待增加

        }
    }
}

void basicInterface::stop(void){
    _running.exchange(false);
}

}