#ifndef __UPDATEMANAGER_HPP__
#define __UPDATEMANAGER_HPP__


#include "basicInterface.hpp"
#include "fileDownload.hpp"

namespace micagent{

class updateManager: public basicInterface{
public:
    updateManager(const protocolCode& protocolType=1012){_protocolType=protocolType;}

    /**
     * @brief 命令解析
     * @param c WebSocket连接
     * @param content 协议报文的内容
    */
    virtual parserRet parser(struct mg_connection* c, const CJsonObject& content);
private:
    /**
     * @brief 验证升级包合法性
    */
    int _verify(const CJsonObject& content) const;

    /**
     * @brief 获取文件大小
    */
    fileSize _getFileSize(const CJsonObject& content) const; 
};

}


#endif //!__UPDATEMANAGER_HPP__