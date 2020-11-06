#pragma once

/*
 * 皇后棋子的声明
 */
typedef struct QUEEN {
    int x;  // 行坐标
    int y;  // 列坐标
} Queen;


/*
 * N皇后算法，返回一个解决方法的数量
 */
int placeQueens(int N);
