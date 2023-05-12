/**
 * 此类主要是通过websocket接收文件
 */
#ifndef __WEBSOCKETFILERECV_HPP__
#define __WEBSOCKETFILERECV_HPP__


#include <iostream>
#include <atomic>
#include <string>

#include "LOG.hpp"
#include "mongoose.h"
#include "CJsonObject.hpp"

namespace micagent{
using namespace std;
using namespace neb;

class WSFileRecv{
public:

    void run(void);
    void stop(void);
private:
    WSFileRecv(const string& ip, short port, const string& savePath)
        :_url{string("ws://"+ip+":"+to_string(port)).c_str()},
        _done{false}
    {
DEBUG_MSG(_url)
    }

    static void _handler(struct mg_connection* c, int ev, void* ev_data, void* fn_data);

    struct mg_mgr _mgr;
    atomic_bool _done;
    struct mg_connection* _conn;    //websocket连接
    const char* _url;
};
}


#endif // !__WEBSOCKETFILERECV_HPP__
