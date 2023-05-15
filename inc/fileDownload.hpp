/**
 * 多线程下载
*/
#ifndef __FILEDOWNLOAD_HPP__
#define __FILEDOWNLOAD_HPP__

#include <queue>
#include <string>

#include "mongoose.h"
#include "ThreadPool.h"

namespace micagent{
using namespace std;


using fileSize_t=long;    //文件大小
using threadNum_t=unsigned char;    //线程数
using chunkSize_t=int;    //每次请求的文件块大小

class fileDownload{
    friend struct downloadTask;
public:
    /**
     * @brief 文件下载任务
    */
    struct downloadTask{
        struct breakpoint{
            //测试版本
            int a;
        };
    public:
        downloadTask(int id, string fN, fileSize_t fS, string sP, threadNum_t tN)
        :_id{id}, _fileName{fN}, _fSize{fS}, _savePath{sP}, _tNum{tN}
        {
            
        }

        /**
         * @brief 开始下载任务
        */
        int start(void);

        /**
         * @brief 停止下载
        */
        struct breakpoint suspend(void);

        /**
         * @brief 终止下载
        */
        int stop(void);
        
    private:
        int _id;    //下载任务编号
        string _fileName;   //文件名称
        fileSize_t _fSize;    //要下载的文件的大小
        string _savePath;   //文件保存路径
        threadNum_t _tNum;  //本次下载使用的线程数
    };


    /**
     * @brief 构造函数
     * @param ip ip地址
     * @param port 端口号
     * @param uri
     * @param cSize 每次请求的最大文件块大小
     * @param maxThreadNum 下载的最大线程数
     * @param defaultPath 默认下载路径
    */
    fileDownload(string ip, short port, string uri, chunkSize_t cSize, threadNum_t maxThreadNum, string defaultPath)
    :_url{string("http://"+ip+":"+to_string(port)+uri).c_str()},
    _cSize{cSize},
    _maxThreadNum{maxThreadNum},
    _defaultPath{defaultPath},
    _threadpool{maxThreadNum}
    {
    }

    /**
     * @brief 添加下载任务
     * @param fileName 要下载的文件名
     * @param fSize 文件大小
     * @param tNum 下载线程数
     * @param savePath 文件保存路径（没有指明时，使用默认路径+原文件名）
    */
    int addTask(string fileName, fileSize_t fSize, threadNum_t tNum, const char* savePath=nullptr);

    /**
     * @brief 开始下载任务，每次下载一个任务
    */
    int startDownload(void);

private:
    const char* _url;
    chunkSize_t _cSize;   //每次下载的文件块的大小
    threadNum_t _maxThreadNum;    //最大线程数
    string _defaultPath;   //文件默认保存路径
    ThreadPool _threadpool; //线程池
    queue<struct downloadTask> _taskQueue;  //下载任务队列
};

}


#endif //!__FILEDOWNLOAD_HPP__