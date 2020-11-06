#pragma once

#include <vector>

/*
 * 效益函数
 */
class BenefitFunc
{
private:
	/*
	 * benefitTable[i][j]表示第i-1个项目投资j万元的效益
	 */
	std::vector<std::vector<int>> benefitTable;  // 投资金额与投资项目的对应表
public:
	BenefitFunc(std::vector<std::vector<int>>);  // 构造函数
	int operator()(const int item, const int money) const;  // 重载对象调用运算符

	int getItemCount() const; // 获取投资项目的数量
	int getAllMoney() const;  // 获取总投资额
};

