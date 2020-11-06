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
	// ��ʼ���߽�����
	// ������ĿͶ��0��Ԫ���0����
	for (auto item : memo)
		item[0] = 0;
	// ǰ1����ĿͶ��i��Ԫ��õ����� = ��1����ĿͶ��i��Ԫ��õ����棬ͬʱ��Ҳ��ǰ1����ĿͶ��i��Ԫ���������
	for(int i = 0; i <= allMoney; i++)
	{
		memo[1][i] = benefitFunc(1, i);
		mark[1][i] = i;
	}

	// �Ե����ϱ���ÿ�����
	for(int curItem = 2; curItem <= itemCount; curItem++)  // �ӵ�2����Ŀ��ʼ(��һ�����ڳ�ʼ�������)���㣬ֱ�����һ����Ŀ
	{
		// ��ǰcurItem����Ŀ��Ǯ����1��ʼ��0�����ڳ�ʼ������ɣ���ֱ��allMoney
		for(int curMoney = 1; curMoney <= allMoney; curMoney++)
		{
			// ����ǰcurItem��Ŀ��Ͷ��curMoneyʱ���������
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
		std::printf("��%d����ĿͶ��%d��Ԫ\n", item, curInvest);
		money -= curInvest;
	}
}


/*
 * ����ǰcurItem����Ŀ��Ͷ��curMoney��Ԫ��õ��������
 */
int Investment::findBestSolution(const int curItem, const int curMoney)
{
	int bestBenefit = 0;  

	for(int lastItemMoney = 0; lastItemMoney <= curMoney; lastItemMoney++)
	{
		// ʹ�õ��Ʒ������
		const int tempBenefit = benefitFunc(curItem, lastItemMoney) + memo[curItem - 1][curMoney - lastItemMoney];
		if (tempBenefit > bestBenefit)
		{
			bestBenefit = tempBenefit;
			mark[curItem][curMoney] = lastItemMoney;
		}
	}

	return bestBenefit;
}
