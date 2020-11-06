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
	// ��ʼ���߽�����
	initBorderCondition();

	// ����ÿ����Ʒ���������Ƶ��������
	traverseCalculate();
}


void Knapsack::initBorderCondition()
{
	// ������װ��Ʒ�ļ�ֵΪ0,vector��ʼ��ʱ�Զ����

	// ������������Ϊ0ʱ����ֵΪ0,vector��ʼ��ʱ�Զ����

	// ��һ����Ʒ�ڸ���������ʱ����װ������ֵ
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
			// ��װcurArticle�����
			int val1 = memo(curArticle - 1, curWeight);
			// װcurArticle�����
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
	vector<int> planTable(articleCount + 1, 0);  // ������ƷӦ��װ�������
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
