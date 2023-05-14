# 第二代米灵云远程升级协议（服务器与设备间的协议）

## 一、设备上线注册协议

### 1.1. 协议说明

1. 使用WebSocket协议，端口号为6007
2. 报文格式为json格式
3. 每个设备应该有自己的版本号，版本类型，以及升级程序的版本号，以此保证升级的正确性
4. 设备上线时主动向服务器发送

### 1.2. 协议内容

* 请求url

```
ws://139.168.32.23:6007/DevRegister
```

* 请求body

```json
{
    "ProtocolCode":1010,
    "Parameters":{
        "DeviceId":"10001",
        "DeviceType":"TS",
        "ProgVersion":"200200"
    }
}
```

> 注释：
>
> DeviceId	设备编号
>
> DeviceType	设备类型
>
> ProgVersion	升级程序版本号

* 相应body

```json
{
    "ProtocolCode":1011,
    "Parameters":{
        "DeviceId":"10010",
        "Status":0
    }
}
```

> 注释
>
> Status为状态码
>
> 0	注册成功
>
> 其它	注册失败

## 二、升级请求协议

### 2.1. 协议说明

1. 使用WebSocket协议，使用端口号6007，与1010协议使用同一WebSocket连接
2. 报文格式为json格式
3. 当服务器收到来自浏览器的升级请求时，向设备发送此内容，设备验证升级的合法性，返回状态码，如果为0代表可以升级

### 2.2. 协议内容

* 请求body

```json
{
    "ProtocolCode":1012,
    "Parameters":{
        "FileName":"updateImage",
        "FileSize":4096,
        "DeviceId":"10010",
        "DeviceType":"TX", 
        "ProgVersion":"1.0.0",
        "LoadCondition":0
    }
}
```

> 注释
>
> FileName	文件名
>
> FileSize	文件大小
>
> DeviceId	设备编号
>
> DeviceType	设备类型
>
> ProgVersion	升级程序版本
>
> LoadCondition	服务器负载状况，为0代表服务器较空闲，从0依次递增，数字越大，负载越重

* 相应body

```json
{
    "ProtocolCode":1013,
    "Parameters":{
        "DeviceId":"10010",
        "Status":0
    }
}
```

> 注释
>
> Status	状态码：
>
> 0	验证通过，可以升级
>
> 其它	验证失败，拒绝升级
>
> -1 升级包不匹配
>
> -2 升级包过大，设备内存不足

## 三、升级包传输协议

### 3.1. 协议说明

1. 使用HTTP协议，端口号6008
2. 在升级请求通过后，由设备主动向服务器发送下载请求，服务器回应状态码以及文件相关内容
3. 服务器回应状态码为0时，代表下载正常，包含文件内容；其它状态码请见注释

### 3.2. 协议内容

* 请求url

```
http://139.168.32.23:6008/download
```

* 请求body

```json
{
    "ProtocolCode":1014,
    "Parameters":{
        "DeviceId":"10010",
        "FileName":"updateImage",
        "Start":0,
        "End":2047
    }
}
```

> 注释
>
> FileName	文件名
>
> Start和End	要下载的文件范围（最大为2048个字节）

* 响应body

```json
{
    "ProtocolCode":1015,
    "Parameters":{
        "Status":0,
        "FileName":"updateImage",
        "Start":0,
        "End":2047,
        "Check":"1BC29B36F623BA82AAF6724FD3B16718",
        "FileChunk":"***********************************************************************"
    }
}
```

> 注释
>
> Check	MD5校验码，取自发送过来的文件块
>
> FileChunk	base64加密过后的文件块实际内容
>
> Status状态码
>
> 0	正常，包含实际的文件块内容
>
> 1	错误，要下载的文件不存在
>
> 2	其它错误
