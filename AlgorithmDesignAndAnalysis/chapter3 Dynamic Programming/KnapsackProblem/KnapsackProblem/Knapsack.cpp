#include "Knapsack.h"

#include <iostream>

using std::vector;

Knapsack::Knapsack(int limit, ArticleList& articleList)
	:weightLimit(limit), list(std::move(articleList)), articleCount(list.getArticleCount()),
	memo(articleCount, limit),
	mark(articleCount, limit)
	{}


void Knapsack::printResult()
{
	calculate();
	output();
}


void Knapsack::calculate()
{
	// 初始化边界条件
	initBorderCondition();

	// 遍历每种物品和重量限制的情况计算
	traverseCalculate();
}


void Knapsack::initBorderCondition()
{
	// 背包不装物品的价值为0,vector初始化时自动完成

	// 背包重量限制为0时最大价值为0,vector初始化时自动完成

	// 第一件物品在各重量限制时所能装的最大价值
	for (int i = 0; i <= weightLimit; i++)
	{
		memo[1][i] = (i / list[1].weight) * list[1].value;
	}
}

void Knapsack::traverseCalculate()
{
	for(int curArticle = 2; curArticle <= articleCount; curArticle++)
	{
		for(int curWeight = 1; curWeight <= weightLimit; curWeight++)
		{
			// 不装curArticle的情况
			int val1 = memo(curArticle - 1, curWeight);
			// 装curArticle的情况
			int val2 = memo(curArticle, curWeight - list[curArticle].weight) + list[curArticle].value;

			if(val1 >= val2)
			{
				memo[curArticle][curWeight] = val1;
				mark[curArticle][curWeight] = mark(curArticle - 1, curWeight);
			}
			else  // val1 < val2
			{
				memo[curArticle][curWeight] = val2;
				mark[curArticle][curWeight] = curArticle;
			}
		}
	}
}


void Knapsack::output() const
{
	vector<int> planTable(articleCount + 1, 0);  // 所有物品应该装入的数量
	int curWeight = weightLimit;
	int curArticle = articleCount;

	while(mark(curArticle, curWeight) > 0)
	{
		curArticle = mark(curArticle, curWeight);
		planTable[curArticle]++;
		curWeight -= list[curArticle].weight;
	}

	for(int i = 1; i <= articleCount; i++)
	{
		std::cout << "article" << i << ": " << planTable[i] << std::endl;
	}
}
