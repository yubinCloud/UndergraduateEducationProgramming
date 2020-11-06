#pragma once

/*
 * 矩阵链乘法算法的迭代版本
 * 具体分析见《算法设计与分析》P55
 */

#include <vector>

using std::vector;

class MatrixChain
{
private:
	vector<int> P;  // 输入向量P = <P0, P1, ..., Pn>
	vector<vector<int>> memo;  // 备忘录，memo[i][j]表示 A(i..j)的计算次数
	vector<vector<int>> separateTable; // 备忘录，[i][j]表示分隔位置
	
	void calculate(); // 计算出两个备忘录
	void output();  // 将计算结果输出到控制台
public:
	MatrixChain(vector<int>);  // 构造函数, 接受一个输入向量

	void printResult();  // 打印计算后的结果，即矩阵相乘的次序
};

