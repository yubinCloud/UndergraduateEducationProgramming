#include "MatrixChain.h"
#include <iostream>
#include <utility>


/*
 * ���캯��
 */
MatrixChain::MatrixChain(std::vector<int> inputVector) :
    P(std::move(inputVector)),
    memo(P.size(), vector<int>(P.size(), 0)),
    separateTable(P.size(), vector<int>(P.size()))
	{}


/*
 * ��ӡ����õ�����˴���
 */
void MatrixChain::printResult()
{
    calculate();  // ���㱸��¼
    output();  // ���
}


void MatrixChain::calculate()
{
    const int size = static_cast<int>(P.size()) - 1;  // ��������
	
	for(int chainLen = 2; chainLen <= size; chainLen++)
    {
	    for (int begin = 1; begin <= size - chainLen + 1; begin++) // begin: ��ǰ���������ǰ�߽�
	    {
		    int end = begin + chainLen - 1; // end: ��ǰ��������ĺ�߽�
		    memo[begin][end] = memo[begin + 1][end] + P[begin - 1] * P[begin] * P[end];
		    separateTable[begin][end] = begin;

		    // �������зָ�λ�ã�from begin+1 to end-1��
		    for (int sepPos = begin + 1; sepPos < end; sepPos++) // sepPos: separate position
		    {
			    // calAmount: calculated amount ������
			    int calAmount = memo[begin][sepPos] + memo[sepPos + 1][end] + P[begin - 1] * P[sepPos] * P[end];

			    if (calAmount < memo[begin][end])
			    {
				    memo[begin][end] = calAmount; // update memo
				    separateTable[begin][end] = sepPos; // update separateTable
			    }
		    }
	    }
    }
}


void MatrixChain::output()
{
	int size = static_cast<int>(P.size()) - 1;
	for(int i = 1; i != size; i++)
	{
		for(int j = i + 1; j <= size; j++)
		{
			std::cout << "s[" << i << "," << j << "]=" << separateTable[i][j] << "   ";
		}
		std::cout << std::endl;
	}
}
