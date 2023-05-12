# Mongoose中提供的有关websocket的API

### 一、结构体 `struct mg_ws_message`

```cpp
/*
简述
	这个结构体代表WebSocket传输的消息
成员
	flags标志位与 RFC 6455 section 5.2.文档中描述的一致
	要获知接收到的消息为何种类型时，可以查看flags的低四位
*/
struct mg_ws_message{
	struct mg_str data;
	uint8_t flags;
};
```

可能的 `WebSocket`消息类型有：

```cpp
#define WBSOCKET_OP_CONTINUE 0
#define WBSOCKET_OP_TEXT 1
#define WBSOCKET_OP_BINARY 2
#define WBSOCKET_OP_CLOSE 8
#define WBSOCKET_OP_PING 9
#define WBSOCKET_OP_PONG 10
```


查看消息类型的例子

```cpp
void fn(struct mg_connection* c, int ev, void* ev_data, void* fn_data){
	if(ev==MG_EV_WS_MSG){
		struct mg_ws_message* wm = (struct mg_ws_message*)ev_data;
		msgtype = wm->flags & 0x0F;
		if(msgtype == WEBSOCKET_OP_BINARY){
			//处理二进制数据
		}
		else if(msgtype == WEBSOCKET_OP_TEXT){
			//处理文本数据
		}
	}
}
```

在调用 `mg_ws_send()`或者 `mg_ws_printf()`发送消息时，使用在RFC 6455 section 5.6中描述的合适的消息类型。



### 二、API

#### 2.1. `mg_ws_connect()`

```cpp
/*
功能：
	创建一个client WebSocket连接
注意：
	这个函数并不是实际连接到通信对端，它只是分配所需的资源并开始connect进程。当通信对端真正建立好连接时，MG_EV_CONNECT事件被送往connection event handler
函数参数：
	mgr	事件管理
	url	要连接的url，e.g. http://google.com
	fn	事件处理函数
	fn_data	fn所需的数据，这个万能指针也存储在connection structure中（c->fn_data）
	fmt	额外的HTTP请求头，可以置为NULL
返回值：
	成功	指向创建好的连接的指针
	失败	范湖NULL
*/
struct mg_connection* mg_ws_connect(struct mg_mgr* mgr, const char* url, mg_event_handler_t fn, void* fn_data, const char* fmt, ...)
```


使用示例：

```cpp
struct mg_connection* c = mg_ws_connect(&mgr, "ws://test_ws_server.com:1000", handler, NULL,
"%s", "Sec-WebSocket-Protocol: echo\r\n");
if(c==NULL)
	fatal("Cannot create connection");
```


#### 2.2.`mg_ws_upgrade()`

```cpp

```
