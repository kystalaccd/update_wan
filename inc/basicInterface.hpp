#ifndef __BASICINTERFACE_HPP__
#define __BASICINTERFACE_HPP__

#include <atomic>
#include <map>

#include "CJsonObject.hpp"
#include "mongoose.h"
#include "LOG.hpp"
#include "deviceInfo.hpp"

#define WEBSOCKET_HEADER NULL
#define POLLDELAY 1000


namespace micagent{
using namespace std;
using namespace neb;

using protocolCode = int;
using Registered = map<protocolCode, basicInterface&>;
using parserRet = void;

Registered interfaceMap;    //存放注册好的命令接口

class basicInterface{
    union handler_param{    //传给handler的参数
        atomic_bool& running;
    };
public:
    basicInterface(const basicInterface&)=delete;
    basicInterface& operator=(const basicInterface&)=delete;

    /**
     * @brief 构造函数
    */
    basicInterface(const string& ip, short port, const string& savePath)
        :_url{string("ws://"+ip+":"+to_string(port)).c_str()},
        _running{false},
        _mgr{0},
        _connection{NULL},
        _protocolType{-1}   //接口基类不执行任何命令解析行为
    {
DEBUG_MSG(_url)
    }

    /**
     * @brief 析构函数
    */
    ~basicInterface(void){stop();}


    /**
     * @brief 注册新的命令接口，成功注册后，当有对应协议的报文发送过来时，就会执行对应的行为
     * @param type 协议编号
     * @param interface 对应的行为编号 
     * @return 返回0代表注册成功; 返回-1代表将基类注册进来了，失败; 返回-2代表类型不匹配，注册失败;
    */
    static int interfaceRegister(const protocolCode& type, const basicInterface& interface){
        if(type==interface.getType()){
            if(type==-1){
                return -1;
            }
            interfaceMap[type]=interface;
            return 0;
        }
        else{
            return -2;
        }
    }

    /**
     * @brief 开始运行
    */
    void run(void);

    /**
     * @brief 停止运行
    */
    void stop(void);

    /**
     * @brief 获取协议编号
    */
    protocolCode getType() const {
        return _protocolType;
    }


private:
    /**
     * @brief 事件处理函数
     * @param c WebSocket连接
     * @param ev 事件类型
     * @param ev_data 事件相关的数据
     * @param fn_data 事件处理需要的具体内容
    */
    static void _handler(struct mg_connection* c, int ev, void* ev_data, void* fn_data);

    /**
     * @brief 获取json格式报文的协议类型
     * @param msg json格式报文
     * @param type 协议号
     * @return 成功获取时返回true，否则返回false
    */
    static bool _getMsgType(const CJsonObject& msg, protocolCode& type){
        return msg.Get("ProtocolCode", type);
    }

    /**
     * @brief 获取json格式报文的协议内容
     * @param msg json格式报文
     * @param content 协议内容
     * @return 成功获取时返回true，否则返回false
    */
    static bool _getMsgContent(const CJsonObject& msg, CJsonObject& content){
        return msg.Get("Parameters", content);
    }


protected:
    /**
     * @brief 命令解析
     * @param c WebSocket连接
     * @param content 协议报文的内容
    */
    virtual parserRet parser(struct mg_connection* c, const CJsonObject& content)=0;


    protocolCode _protocolType; //协议编号，以此执行对应的行为
private:
    struct mg_connection* _connection;    //websocket连接
    struct mg_mgr _mgr; //mongoose的事件管理器
    atomic_bool _running;   //运行开关
    const char* _url;   //记录服务器的url，使用WebSocket协议
};

}


#endif