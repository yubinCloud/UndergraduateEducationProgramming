#pragma once

#include "BenefitFunc.h"


/*
 * 投资规划类
 */
class Investment
{
private:
	int allMoney; // 总共的钱数
	int itemCount; // 总共的投资项目数
	BenefitFunc benefitFunc;  // 效益函数
	std::vector<std::vector<int>> memo; // 备忘录,[k][x]表示前k个项目投资x万元的最大收益
	std::vector<std::vector<int>> mark;  // 标记函数，mark[k][x]表示memo[k][x]取得最大值是应该分配给第k个项目的钱数

	void calculate();  // 计算出备忘录和标记函数
	void output() const;  // 将计算结果输出至标准输出
	int findBestSolution(const int curItem, const int curMoney);  // 计算出前curItem个项目共投资curMoney时的最大收益
public:
	Investment(const BenefitFunc);  // 构造函数，接受一个效益函数类
	void printResult();  // 计算并打印结果
};

