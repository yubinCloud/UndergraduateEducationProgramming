/**
 * 读端的代码
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>


int main(int argc, char *argv[])
{
    const int SHM_SIZE = 512;  // 共享内存区的大小

    // 创建key值
    key_t key = ftok("../", 2020);
    if(key == -1) {
        perror("ftok");
    }

    system("ipcs -m"); //查看共享内存

    // 打开共享内存
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if(shmid < 0)
    {
        perror("shmget");
        exit(-1);
    }

    // 映射
    void* shmPtr = shmat(shmid, NULL, 0);
    if(shmPtr < 0) {
        perror("shmat");
        exit(-1);
    }

    // 读共享内存区数据
    printf("data = [%s]", (char*)shmPtr);

    // 将共享内存和当前进程分离
    int ret = shmdt(shmPtr);
    if(ret < 0) {
        perror("shmdt");
        exit(1);
    } else {
        printf("\ndeleted shared-memory\n");
    }

    // 删除共享内存
    shmctl(shmid, IPC_RMID, NULL);

    system("ipcs -m"); //查看共享内存

    return 0;
}