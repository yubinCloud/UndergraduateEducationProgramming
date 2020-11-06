#pragma once

/*
 * �������˷��㷨�ĵ����汾
 * ������������㷨����������P55
 */

#include <vector>

using std::vector;

class MatrixChain
{
private:
	vector<int> P;  // ��������P = <P0, P1, ..., Pn>
	vector<vector<int>> memo;  // ����¼��memo[i][j]��ʾ A(i..j)�ļ������
	vector<vector<int>> separateTable; // ����¼��[i][j]��ʾ�ָ�λ��
	
	void calculate(); // �������������¼
	void output();  // �����������������̨
public:
	MatrixChain(vector<int>);  // ���캯��, ����һ����������

	void printResult();  // ��ӡ�����Ľ������������˵Ĵ���
};

