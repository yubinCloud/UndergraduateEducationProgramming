#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

static const char* const FIFO_NAME = "myFifo";

int main()
{
    /* 判断一下管道文件是否存在，不存在就退出程序 */
    int result = access( FIFO_NAME, F_OK );
    if( result == -1 )
    {
        printf( "error:can't find the fifo.\n" );
        return 1;
    }

    /* 以只写的方式打开管到文件 */
    int fifo_fd = open( FIFO_NAME, O_WRONLY );
    if( fifo_fd < 0 )
    {
        printf( "error:can't open a fifo.\n" );
        return 1;
    }

    char buffer[32];
    /* 循环向管到文件中写入数据 */
    do
    {
        memset( buffer, 0, 32 );
        printf( "Please input something:" );
        scanf( "%s", buffer );
        ssize_t buffer_len = write(fifo_fd, buffer, strlen( buffer ));
        printf( "write:%s\n", buffer );
    }
    while( memcmp( buffer, "close", 5 ) != 0 );

    close( fifo_fd );
    unlink( FIFO_NAME );

    return 0;
}
