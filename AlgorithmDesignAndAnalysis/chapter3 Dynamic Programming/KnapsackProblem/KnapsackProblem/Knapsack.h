#pragma once

#include <vector>
#include "ArticleList.h"
#include "F.h"

class Knapsack
{
private:
	const int weightLimit;  // 背包重量限制
	const ArticleList list;  // 可选择的物品清单
	const int articleCount;  // 物品清单中的数量
	F memo;  // 备忘录函数,memo[i][j]表示从前i个物品中重量上限为j时的最大价值
	F mark;  // 标记函数，mark[i][j]表示计算memo[i][j]时所用到的最大物品的序号

	void calculate();  // 计算memo和mark
	void output() const; // 输出计算结果到标准输出
	void initBorderCondition();  // 初始化边界条件
	void traverseCalculate();  // 遍历个情况计算
public:
	Knapsack(int, ArticleList&);
	void printResult();
};

