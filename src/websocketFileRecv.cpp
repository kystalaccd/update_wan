#include "websocketFileRecv.hpp"

namespace micagent{

void WSFileRecv::run(void){
    mg_mgr_init(&_mgr);
    mg_log_set(MG_LL_DEBUG);
    _conn = mg_ws_connect(&_mgr, _url, _handler, &_done, NULL);
    while(_conn && _done == false){
        mg_mgr_poll(&_mgr, 1000);
    }
    mg_mgr_free(&_mgr);
}

void WSFileRecv::stop(void){
    _done.exchange(true);
}

}