#include "Investment.h"
#include <iostream>
#include <vector>

using std::vector;

int main()
{
	// benefitTable[i][j]��ʾ��i-1����ĿͶ��j��Ԫ���õ�Ч��
	const vector<vector<int>> benefitTable = { {0,11,12,13,14,15},
											{0,0,5,10,15,20},
											{0,2,10,30,32,40},
											{0,20,21,22,23,24} };
	// ����Ч�����Ͷ����Ŀ�Ķ���
	Investment investment(benefitTable);
	// ���㲢��ӡ������
	investment.printResult();

	return 0;
}