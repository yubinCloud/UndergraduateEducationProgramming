#pragma once

#include <vector>

using std::vector;

template <typename T>
class Sequence
{
private:
	std::vector<T> seq;  // 输入的原始序列
	std::vector<T> memo; // 备忘录，memo[i]为seq[0...i]中必须包含元素seq[i]的最大子段和

	/*
	 * 计算最大子段和所在子段的最后位置
	 */
	unsigned calculateSubLastIndex()
	{
		int curSum = 0; // 当前最大子段和
		int preSum = 0; // 前一个最大子段和
		unsigned lastIdx = 0;

		for (unsigned i = 0; i != seq.size(); i++)
		{
			preSum = preSum > 0 ? preSum + seq[i] : seq[i];
			memo[i] = preSum;

			if (preSum > curSum)
			{
				curSum = preSum;
				lastIdx = i;
			}
		}

		return lastIdx;
	}
	
public:
	/*
	 * 构造函数
	 */
	Sequence(std::vector<T>& seq) 
		:seq(std::move(seq)), memo(this->seq.size())
	{ }


	/*
	 * 获取最大子段和所在的序列
	 */
	std::vector<T> getMaxSubSumSeq()
	{
		auto idx = calculateSubLastIndex();

		vector<T> resSeq;
		int maxSum = memo[idx];

		while (maxSum != 0)
		{
			resSeq.push_back(seq[idx]);
			maxSum -= seq[idx];
			--idx;
		}
		std::reverse(resSeq.begin(), resSeq.end());

		return resSeq;
	}

	/*
	 * 打印计算结果
	 */
	void printResult()
	{
		vector<T> resSeq = std::move(getMaxSubSumSeq());

		for (auto n : resSeq)
			std::cout << n << std::endl;
	}
};

