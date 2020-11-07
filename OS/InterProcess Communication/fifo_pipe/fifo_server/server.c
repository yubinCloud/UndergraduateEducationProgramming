#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

static const char* const FIFO_NAME = "myFifo";

int main()
{
    char buffer[32];

    // 先删除之前可能遗留的管道文件，然后再次创建它
    unlink(FIFO_NAME);
    int result = mkfifo(FIFO_NAME, 0777);
    if (result != 0)
    {
        printf("error:can't create a fifo.\n");
        return 1;
    }

    // 以只读的方式打开管道文件
    int fifo_fd = open(FIFO_NAME, O_RDONLY);
    if (fifo_fd < 0)
    {
        printf("error:can't open a fifo.\n");
        return 1;
    }

    // 循环从管到文件中读取数据
    do
    {
        memset(buffer, 0, 32);
        ssize_t buffer_len = read(fifo_fd, buffer, 31);
        buffer[buffer_len] = '\0';
        printf("read:%s\n", buffer);
    } while (memcmp(buffer, "close", 5) != 0);

    close(fifo_fd);
    unlink(FIFO_NAME);

    return 0;
}