# boost_ipc

借助`boost::interprocess`实现的两个进程之间通过**共享内存机制**的通信

### 启动方式
1. 下载并使用MSVC完成对boost库的编译。
2. 将boost的路径附加到`writeProcess`和`readProcess`项目的`包含目录`与`库目录`中。
3. 分别编译两个项目，首先运行`writeProcess`，输入一个name并结束程序，然后运行`readProcess`，可以看到此时回显出之前所输入的name。

### 运行效果
在`writeProcess`进程中输入的name会被`readProcess`回显出来。