/**
 * 获取设备信息
*/
#ifndef __DEVICEINFO_HPP__
#define __DEVICEINFO_HPP__

#include <string>

#include "CJsonObject.hpp"

namespace micagent{
using namespace std;
using namespace neb;

struct deviceInfo{
public:
    //测试阶段
    deviceInfo(void):_id("10000"), _type("TX"), _progVersion("1.0.0"){}
    string getId() const {return _id;}
    string getType() const {return _type;}
    string getProgVersion() const {return _progVersion;}
    struct deviceInfo getDeviceInfo() const { return *this;}
    CJsonObject getDeviceJson() const {
        CJsonObject ret;
        ret.Add("DeviceId", _id);
        ret.Add("DeviceType", _type);
        ret.Add("ProgVersion", _progVersion);
        return ret;
    }
private:
    string _id; //设备id
    string _type;   //设备类型
    string _progVersion;    //程序版本
};
}


#endif //!__DEVICEINFO_HPP__