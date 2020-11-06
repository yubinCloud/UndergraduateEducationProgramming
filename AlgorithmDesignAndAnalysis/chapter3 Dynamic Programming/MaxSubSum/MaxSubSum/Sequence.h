#pragma once

#include <vector>

using std::vector;

template <typename T>
class Sequence
{
private:
	std::vector<T> seq;  // �����ԭʼ����
	std::vector<T> memo; // ����¼��memo[i]Ϊseq[0...i]�б������Ԫ��seq[i]������Ӷκ�

	/*
	 * ��������Ӷκ������Ӷε����λ��
	 */
	unsigned calculateSubLastIndex()
	{
		int curSum = 0; // ��ǰ����Ӷκ�
		int preSum = 0; // ǰһ������Ӷκ�
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
	 * ���캯��
	 */
	Sequence(std::vector<T>& seq) 
		:seq(std::move(seq)), memo(this->seq.size())
	{ }


	/*
	 * ��ȡ����Ӷκ����ڵ�����
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
	 * ��ӡ������
	 */
	void printResult()
	{
		vector<T> resSeq = std::move(getMaxSubSumSeq());

		for (auto n : resSeq)
			std::cout << n << std::endl;
	}
};

