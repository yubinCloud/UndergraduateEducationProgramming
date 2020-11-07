/**
 * 写端的代码
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>


int main(int argc, char* argv[])
{
    const int SHM_SIZE = 512;  // 共享内存的大小


    // 把一个已存在的路径名和一个整数标识符转换成一个key_t值，称为IPC键值（也称IPC key键值）
    key_t key = ftok("../", 2020);
    if (key == -1) {
        perror("ftok");
    }

    // 创建一块SHM_SIZE大小的可读可写共享内存块
    int shmId = shmget(key, SHM_SIZE, IPC_CREAT | 0666);  // 共享内存的标识符
    if (shmId < 0) {
        perror("shmget");
        exit(-1);
    }

    // 将共享内存段映射到调用进程的数据段中
    void* segPtr = shmat(shmId, NULL, 0);
    if (segPtr < 0) {
        perror("shmat");
        _exit(-1);
    }

    // 拷贝数据到共享内存区
    printf("Copy data to shared-memory\n");
    bzero(segPtr, SHM_SIZE);  // 共享内存清空
    strcpy(segPtr, "how are you, yuBin?");

    return 0;
}
