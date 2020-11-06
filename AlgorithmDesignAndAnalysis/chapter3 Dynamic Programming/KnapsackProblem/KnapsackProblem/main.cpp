#include <iostream>
#include <vector>

#include "Knapsack.h"

using std::vector;

int main()
{
	// ��Ʒ�б�
	vector<Article> articles({ Article(2, 1), Article(3, 3),
		Article(4, 5),Article(7, 9) });

	ArticleList articleList(articles);

	// ������Ʒ�б����ɱ�������
	Knapsack knapsack(10, articleList);
	// ���㲢��ӡ������
	knapsack.printResult();

	return 0;
}