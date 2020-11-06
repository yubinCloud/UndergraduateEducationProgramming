#include "BenefitFunc.h"

#include <utility>

BenefitFunc::BenefitFunc(std::vector<std::vector<int>> benefitTable):
	benefitTable(std::move(benefitTable))
	{}


int BenefitFunc::operator()(const int item, const int money) const
{
	// 由于vector从0开始计数，而项目是由1开始计数，故需要item-1
	return benefitTable[item - 1][money];
}


int BenefitFunc::getItemCount() const
{
	return benefitTable.size();
}


int BenefitFunc::getAllMoney() const
{
	int allMoney = 0;
	for(auto item: benefitTable)
	{
		if (allMoney < item.size() - 1)
			allMoney = item.size() - 1;
	}

	return allMoney;
}
