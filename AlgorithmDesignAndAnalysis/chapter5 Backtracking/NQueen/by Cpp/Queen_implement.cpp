#include "Stack.h"
#include "Queen.h"

/*
 * N皇后算法，返回一个解决方法的数量
 */
int placeQueens(int N)
{
    int nSolu = 0;  // 解决方案数
    Stack stack;  // 存放（部分）解的栈
    stack_init(stack);
    Queen queen = {0, 0};  // 从原点位置出发
    do {  // 反复试探、回溯
        if( N <= stack_size(stack) || N <= queen.y )  // 若已经出界，则
        {
            queen = stack_pop(stack);  // 回溯一行，并继续试探下一列
            queen.y++;
        }
        else  // 否则，试探下一行
        {
            while( (queen.y < N) && !checkQueen(queen, stack) )  // 通过与已有皇后对比
            {
                queen.y++;  // 尝试找到可摆放下一个皇后的列
            }
            if(N > queen.y)  // 若存在可摆放的列
            {
                stack_push(stack, queen);  // 摆上当前皇后，并
                if( N <= stack_size(stack) ) // 若部分解已经成为全局解，则通过变量 nSolu 来计数
                    nSolu++;
                queen.x++; // 转入下一行，从第0列开始，试探下一个皇后
                queen.y = 0;
            }
        }
    } while( (queen.x > 0) || (queen.y < N)); // 所有分支均已经穷举完毕，算法结束

    stack_destroy(stack);
    return nSolu;
}
