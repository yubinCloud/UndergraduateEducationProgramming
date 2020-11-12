/**
 * 管道的方式实现进程通信
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    puts("begin running...");

    int fd[2];  // file descriptors
    int ret = pipe(fd);

    if (ret == -1) {
        perror("anonymous_pipe error\n");
        return 1;
    }

    pid_t processId = fork();  // fork 一个子进程

    if (processId == 0) {  // child process
        int i = 0;
        close(fd[0]);  // 关闭与fd[0]的连接，从而只保留与fd[1]的连接
        printf("------------------I am %d child process, my parent process is %d.------------------\n", getpid(), getppid());
        char* childMsg = (char*) malloc(50);
        printf("Please enter your name to child process:  ");
        scanf("%s", childMsg);
        childMsg[49] = '\0';
        while (i < 5) {
            write(fd[1], childMsg, strlen(childMsg) + 1);
            sleep(1);
            ++i;
        }
        free(childMsg);
    }
    else if (processId > 0) {  // father process
        close(fd[1]);  // 关闭与fd[1]的连接

        printf("------------------I am %d father process, my parent process is %d.------------------\n", getpid(), getppid());

        char msg[100];
        int j = 0;
        while (j < 5) {
            memset(msg, '\0', sizeof(msg));  // 将msg全部设置为'\0'
            ssize_t s = read(fd[0], msg, sizeof(msg));

            if (s > 0) {
                msg[s - 1] = '\0';
            }
            printf("Your name: %s\n", msg);
            ++j;
        }
    }
    else {  // error
        perror("fork error\n");
        return 2;
    }
    return 0;
}
