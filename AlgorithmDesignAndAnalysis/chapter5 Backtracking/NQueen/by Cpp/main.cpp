#include <stdio.h>
#include "Queen.h"

int main()
{
    /* 输入放入的数量 */
    int number;
    printf("请输入想要放置的皇后数量：");
    scanf("%d",&number);
    /* 求解方案数 */
    int solution = placeQueens(number);
    /* 输出 */
    printf("共有%d种放置方式", solution);
    return 0;
}

