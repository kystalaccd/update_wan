/**
 * 多线程下载
*/
#ifndef __FILEDOWNLOAD_HPP__
#define __FILEDOWNLOAD_HPP__

#include <string>

#include "mongoose.h"

namespace micagent{
using namespace std;


using fileSize=long;    //文件大小
using threadNum=unsigned char;    //线程数
using chunkSize=int;    //每次请求的文件块大小

class fileDownload{
public:
    fileDownload(string ip, short port, string uri, chunkSize cSize, fileSize fSize, threadNum tNum)
    :_url{string("http://"+ip+":"+to_string(port)+uri).c_str()},
    _cSize{cSize},
    _fSize{fSize},
    _tNum{tNum}
    {
    }

private:
    const char* _url;
    chunkSize _cSize;
    fileSize _fSize;
    threadNum _tNum;
    string _savePath;
};

}


#endif //!__FILEDOWNLOAD_HPP__