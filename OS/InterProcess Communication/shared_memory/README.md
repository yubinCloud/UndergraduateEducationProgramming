# shared_memory

使用C语言的`sys/ipc.h`和`sys/shm.h`库来发起系统调用实现**共享内存机制**的两个进程通信

### 启动方式
1. 在Linux系统下，分别编译`writeEnd`和`readEnd`两个文件下的`main.c`。
2. 首先运行`writeEnd`下的程序，再运行`readEnd`下的程序即可看到运行结果。