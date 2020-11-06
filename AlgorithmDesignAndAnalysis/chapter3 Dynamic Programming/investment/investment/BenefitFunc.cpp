#include "BenefitFunc.h"

#include <utility>

BenefitFunc::BenefitFunc(std::vector<std::vector<int>> benefitTable):
	benefitTable(std::move(benefitTable))
	{}


int BenefitFunc::operator()(const int item, const int money) const
{
	// ����vector��0��ʼ����������Ŀ����1��ʼ����������Ҫitem-1
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
