#pragma once

#include <vector>


/*
 * �Ż�����
 */
class F
{
private:
    std::vector<std::vector<int>> table;
public:
    F(int , int);
    int operator()(int article, int weight) const;  // ��ȡoperator[article][weight]��ֵ��weight<0ʱ��������С
    std::vector<int>& operator[](int article);  // ������[]����ת�Ƶ�table��
};

