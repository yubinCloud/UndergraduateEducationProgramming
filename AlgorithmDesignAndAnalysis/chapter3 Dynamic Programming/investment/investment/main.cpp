#include "Investment.h"
#include <iostream>
#include <vector>

using std::vector;

int main()
{
	// benefitTable[i][j]表示第i-1个项目投资j万元所得的效益
	const vector<vector<int>> benefitTable = { {0,11,12,13,14,15},
											{0,0,5,10,15,20},
											{0,2,10,30,32,40},
											{0,20,21,22,23,24} };
	// 根据效益表创建投资项目的对象
	Investment investment(benefitTable);
	// 计算并打印计算结果
	investment.printResult();

	return 0;
}