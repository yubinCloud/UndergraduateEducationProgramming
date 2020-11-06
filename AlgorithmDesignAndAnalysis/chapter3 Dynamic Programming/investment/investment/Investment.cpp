#include "Investment.h"
#include <iostream>
#include <string>

using std::string;
using std::vector;

Investment::Investment(BenefitFunc benefitFunc):
	allMoney(benefitFunc.getAllMoney()), itemCount(benefitFunc.getItemCount()),
	benefitFunc(std::move(benefitFunc)),
	memo(itemCount + 1, vector<int>(allMoney + 1, 0)),
	mark(itemCount + 1, vector<int>(allMoney + 1, 0))
	{}

void Investment::printResult()
{
	calculate();
	output();
}

void Investment::calculate()
{
	// 初始化边界条件
	// 所有项目投资0万元获得0收益
	for (auto item : memo)
		item[0] = 0;
	// 前1个项目投资i万元获得的收益 = 第1个项目投资i万元获得的收益，同时这也是前1个项目投资i万元的最大收益
	for(int i = 0; i <= allMoney; i++)
	{
		memo[1][i] = benefitFunc(1, i);
		mark[1][i] = i;
	}

	// 自底向上遍历每种情况
	for(int curItem = 2; curItem <= itemCount; curItem++)  // 从第2个项目开始(第一个已在初始化中完成)计算，直到最后一个项目
	{
		// 给前curItem个项目的钱，从1万开始（0万已在初始化中完成），直到allMoney
		for(int curMoney = 1; curMoney <= allMoney; curMoney++)
		{
			// 记下前curItem项目总投资curMoney时的最大收益
			memo[curItem][curMoney] = findBestSolution(curItem, curMoney);
		}
	}
}

void Investment::output() const
{
	int money = allMoney;
	for(int item = itemCount; item != 0; item--)
	{
		int curInvest = mark[item][money];
		std::printf("第%d个项目投资%d万元\n", item, curInvest);
		money -= curInvest;
	}
}


/*
 * 计算前curItem个项目总投资curMoney万元获得的最大收益
 */
int Investment::findBestSolution(const int curItem, const int curMoney)
{
	int bestBenefit = 0;  

	for(int lastItemMoney = 0; lastItemMoney <= curMoney; lastItemMoney++)
	{
		// 使用递推方程求解
		const int tempBenefit = benefitFunc(curItem, lastItemMoney) + memo[curItem - 1][curMoney - lastItemMoney];
		if (tempBenefit > bestBenefit)
		{
			bestBenefit = tempBenefit;
			mark[curItem][curMoney] = lastItemMoney;
		}
	}

	return bestBenefit;
}
