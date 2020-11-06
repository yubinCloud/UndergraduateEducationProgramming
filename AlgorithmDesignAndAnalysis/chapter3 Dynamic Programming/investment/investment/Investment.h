#pragma once

#include "BenefitFunc.h"


/*
 * Ͷ�ʹ滮��
 */
class Investment
{
private:
	int allMoney; // �ܹ���Ǯ��
	int itemCount; // �ܹ���Ͷ����Ŀ��
	BenefitFunc benefitFunc;  // Ч�溯��
	std::vector<std::vector<int>> memo; // ����¼,[k][x]��ʾǰk����ĿͶ��x��Ԫ���������
	std::vector<std::vector<int>> mark;  // ��Ǻ�����mark[k][x]��ʾmemo[k][x]ȡ�����ֵ��Ӧ�÷������k����Ŀ��Ǯ��

	void calculate();  // ���������¼�ͱ�Ǻ���
	void output() const;  // ���������������׼���
	int findBestSolution(const int curItem, const int curMoney);  // �����ǰcurItem����Ŀ��Ͷ��curMoneyʱ���������
public:
	Investment(const BenefitFunc);  // ���캯��������һ��Ч�溯����
	void printResult();  // ���㲢��ӡ���
};

