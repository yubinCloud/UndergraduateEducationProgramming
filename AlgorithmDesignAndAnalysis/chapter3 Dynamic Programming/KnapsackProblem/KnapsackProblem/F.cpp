#include "F.h"
#include <climits>

F::F(int articleCount, int weightLimit)
	: table (articleCount + 1, std::vector<int>(weightLimit + 1, 0))
{}


int F::operator()(int article, int weight) const
{
	if (weight < 0)
		return INT_MIN;
	return table[article][weight];
}


std::vector<int>& F::operator[](int article)
{
	return table[article];
}
