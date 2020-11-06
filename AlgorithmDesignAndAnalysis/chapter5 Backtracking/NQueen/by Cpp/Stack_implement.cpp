#include "Stack.h"
#include <stdlib.h>

/*
 * 数组复制，将数组列表source中的数组元素依次复制到aim数组中
 */
void arrayCopy(Stack* source, ElemType* aim)
{
    for(int i = 0; i < source->_size; i++)
    {
        aim[i] = source->_elem[i];
    }
}

/*
 * 初始化栈
 * 容量默认初始化为DEFAULTCAPICITY大小
 */
void stack_init(Stack& self)
{
    self._elem = (ElemType*)malloc(DEFAULTCAPACITY * sizeof(ElemType));
    self._size = 0;
    self._capacity = DEFAULTCAPACITY;
}

/*
 * 销毁栈
 */
void stack_destroy(Stack& self)
{
    free(self._elem);
    self._elem = NULL;
    self._size = 0;
    self._capacity = 0;
}

/*
 * 返回栈的大小
 */
int stack_size(Stack const& self)
{
    return self._size;
}


/*
 * 对一个栈进行扩容检查
 * 若需要扩容，则容量翻倍
 * 若不需要扩容，则直接返回
 */
void stack_expand(Stack& self)
{
    // 无需扩容的情况
    if(self._size < self._capacity)
    {
        return ;
    }
    // 需要扩容的情况
    ElemType* newElems;
    if(self._capacity < DEFAULTCAPACITY)
    {
        newElems = (ElemType*)malloc(DEFAULTCAPACITY * sizeof(ElemType));
        self._capacity = DEFAULTCAPACITY;
    }
    else
    {
        newElems = (ElemType*)malloc(2 * self._capacity * sizeof(ElemType));
        self._capacity <<= 1;
    }
    arrayCopy(&self, newElems);
    free(self._elem);
    self._elem = newElems;
}

/*
 * 将一个元素压入栈中
 */
void stack_push(Stack& self, ElemType aElem)
{
    stack_expand(self);
    self._elem[self._size] = aElem;
    self._size++;
}

/*
 * 将一个栈中的一个元素弹出
 */
ElemType stack_pop(Stack& self)
{
    return self._elem[--self._size];
}


/*
 * 检查一枚皇后棋子与其他已放置的皇后是否产生冲突
 */
int checkQueen(Queen queen, Stack const& self)
{
    Queen other;
    for(int i = 0; i < self._size; i++)
    {
        other = self._elem[i];
        if(queen.x == other.x || queen.y == other.y)  // 行冲突或列冲突
            return 0;
        if(queen.x + queen.y == other.x + other.y)   // 沿着正对角线冲突
            return 0;
        if(queen.x - queen.y == other.x - other.y)  // 沿着反对角线冲突
            return 0;
    }
    return 1;  // 与任何皇后不冲突，成功返回1
}