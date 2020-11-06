# 计算机网络编程

使用C/C++的socket进行的网络编程

|   Name    |          Description           | Note |
| :-------: | :----------------------------: | :--: |
| time_sync | 基于流式套接字的时间同步服务器 |      |
|           |                                |      |
|           |                                |      |

## 简介

### 基于流式套接字的时间同步服务器

要求使用流式套接字编程，实现时间同步服务器和客户端，该服务器能够接收客户端的查询请求，获取本地时间，并将结果发送回客户端，客户端将该时间显示出来，如图1所示。

提示&注意：

+  time()函数、ctime()函数为时间处理函数。

+ 客户的recv函数需要循环接收。

![ip1](https://raw.githubusercontent.com/yubinCloud/MyImgRepo/master/imgs/ip1.png)