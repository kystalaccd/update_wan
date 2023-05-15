#include "fileDownload.hpp"

namespace micagent{
int fileDownload::downloadTask::start(void){
    //step 01. 分割下载任务，每个下载任务占用一个线程
    fileSize_t filePartSize = _fSize / static_cast<long>(_tNum);
    //step 02.  每个下载任务循环请求多次，每次将接收到的文件块存入临时文件中

    //step 03.  当每个下载任务都完成时，将所有临时文件整合成最终的文件
}
}