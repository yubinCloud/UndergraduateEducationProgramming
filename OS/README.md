# OS-Course

本科操作系统课程的实验代码

## InterProcess Communication 进程间通信

### boost_ipc

由 C++ 的`boost::interprocess`实现的共享内存方式的进程间通信

### shared_memory

使用C语言的`sys/ipc.h`和`sys/shm.h`库来发起系统调用实现共享内存机制的两个进程通信

### anonymous_pipe

使用C语言`unistd.h`中的`int pipe(int pipefd[2])`来发起系统调用实现管道方式的两个进程通信

## Exp1-process_control

实验1：进程的描述与控制

