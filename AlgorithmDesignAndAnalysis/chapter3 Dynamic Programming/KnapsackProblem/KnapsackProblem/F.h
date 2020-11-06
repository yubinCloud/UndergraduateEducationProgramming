#pragma once

#include <vector>


/*
 * 优化函数
 */
class F
{
private:
    std::vector<std::vector<int>> table;
public:
    F(int , int);
    int operator()(int article, int weight) const;  // 读取operator[article][weight]的值，weight<0时返回无穷小
    std::vector<int>& operator[](int article);  // 代理，将[]运算转移到table中
};

