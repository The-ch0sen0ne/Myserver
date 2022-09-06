# Myserver
项目描述：本项目是使用C++11开发的基于Linux的web多线程服务器，实现了对HTTP请求的简单相应

主要工作：
使用epoll电平触发实现IO多路复用
使用主从Reactor模式，主Reactor线程负责创建新连接，副Reactor线程负责处理连接的各种事件
每个连接都配备独立的动态读写缓冲区
通过时间轮实现踢掉空闲连接的功能


webbench测压结果
![image](https://github.com/The-ch0sen0ne/Myserver/blob/main/source/result.png)


目前能简单实现对get请求的相应，对HTTP正文部分的处理是读取之后直接丢弃:


![image](https://github.com/The-ch0sen0ne/Myserver/blob/main/source/show.png)
