#pragma once

#include <vector>
#include "ArticleList.h"
#include "F.h"

class Knapsack
{
private:
	const int weightLimit;  // ������������
	const ArticleList list;  // ��ѡ�����Ʒ�嵥
	const int articleCount;  // ��Ʒ�嵥�е�����
	F memo;  // ����¼����,memo[i][j]��ʾ��ǰi����Ʒ����������Ϊjʱ������ֵ
	F mark;  // ��Ǻ�����mark[i][j]��ʾ����memo[i][j]ʱ���õ��������Ʒ�����

	void calculate();  // ����memo��mark
	void output() const; // �������������׼���
	void initBorderCondition();  // ��ʼ���߽�����
	void traverseCalculate();  // �������������
public:
	Knapsack(int, ArticleList&);
	void printResult();
};

