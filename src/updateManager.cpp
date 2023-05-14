#include "updateManager.hpp"
#include "deviceInfo.hpp"

namespace micagent{
parserRet updateManager::parser(struct mg_connection* c, const CJsonObject& content){
    //验证升级合法性
    switch(_verify(content)){
        case 0: //验证通过

            break;
        case -1:
            break;
        case -2:
            break;
        default:
            break;
    }

}


int updateManager::_verify(const CJsonObject& content)const{
    //测试阶段
    return 0;
}

fileSize updateManager::_getFileSize(const CJsonObject& content)const{
    //测试阶段
    return 8192;
}
}