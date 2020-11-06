#pragma once

#include <vector>

/*
 * Ч�溯��
 */
class BenefitFunc
{
private:
	/*
	 * benefitTable[i][j]��ʾ��i-1����ĿͶ��j��Ԫ��Ч��
	 */
	std::vector<std::vector<int>> benefitTable;  // Ͷ�ʽ����Ͷ����Ŀ�Ķ�Ӧ��
public:
	BenefitFunc(std::vector<std::vector<int>>);  // ���캯��
	int operator()(const int item, const int money) const;  // ���ض�����������

	int getItemCount() const; // ��ȡͶ����Ŀ������
	int getAllMoney() const;  // ��ȡ��Ͷ�ʶ�
};

