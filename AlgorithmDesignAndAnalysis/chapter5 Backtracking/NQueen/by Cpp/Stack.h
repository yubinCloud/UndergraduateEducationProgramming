#pragma once
#include "Queen.h"
#define DEFAULTCAPACITY 5

typedef Queen ElemType; // 将皇后类型作为栈的元素类型

typedef struct STACK {
    ElemType* _elem = 0;  // 栈中元素数组的首地址
    int _size = 0;  // 栈中元素数量
    int _capacity = 0;  // 栈的容量
} Stack;


/*
 * 初始化栈
 * 容量默认初始化为DEFAULTCAPICITY大小
 */
void stack_init(Stack& self);

/*
 * 销毁栈
 */
void stack_destroy(Stack& self);

/*
 * 返回栈的大小
 */
int stack_size(Stack const& self);

/*
 * 对一个栈进行扩容检查
 * 若需要扩容，则容量翻倍
 * 若不需要扩容，则直接返回
 */
void stack_expand(Stack& self);

/*
 * 将一个元素压入栈中
 */
void stack_push(Stack& self, ElemType aElem);

/*
 * 将一个栈中的一个元素弹出
 */
ElemType stack_pop(Stack& self);



/*
 * 检查一枚皇后棋子与其他已放置的皇后是否产生冲突
 */
int checkQueen(Queen queen, Stack const& self);