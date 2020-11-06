#include <iostream>
#include <vector>

#include "Knapsack.h"

using std::vector;

int main()
{
	// 物品列表
	vector<Article> articles({ Article(2, 1), Article(3, 3),
		Article(4, 5),Article(7, 9) });

	ArticleList articleList(articles);

	// 根据物品列表生成背包对象
	Knapsack knapsack(10, articleList);
	// 计算并打印计算结果
	knapsack.printResult();

	return 0;
}