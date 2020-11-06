#pragma once
#include <vector>

enum class Status { Y, NX, NY };  // 标记状态，分别表示两序列最后一项相等、不考虑X、不考虑Y


template <typename T>
class LCS
{
private:
	std::vector<T> seqX;  // 第一个序列
	std::vector<T> seqY;  // 第二个序列
	std::vector<T> commonSeq;  // 公共序列

	std::vector<std::vector<int>> memo;  // 记录最长公共子序列的长度
	std::vector<std::vector<Status>> mark;  // 记录最长公共子序列是怎样选取的


	/*
	 * if xPos and yPos are nonnegative, return memo[xPos][yPos]
	 * if one of them is negative, return 0
	 */
	int getMemoValue(int xPos, int yPos) const
	{
		if (xPos >= 0 && yPos >= 0)
			return memo[xPos][yPos];
		else // 其中一个为0时
			return 0;
	}

	/*
	 * calculate memo and mark
	 */
	void calculateMemoAndMark()  // 计算memo和mark
	{
		for (int xPos = 0; xPos != seqX.size(); xPos++)
		{
			for (int yPos = 0; yPos != seqY.size(); yPos++)
			{
				if (seqX[xPos] == seqY[yPos])
				{
					memo[xPos][yPos] = getMemoValue(xPos - 1, yPos - 1) + 1;
					mark[xPos][yPos] = Status::Y;
				}
				else if (getMemoValue(xPos - 1, yPos) >= getMemoValue(xPos, yPos - 1))
				{
					memo[xPos][yPos] = getMemoValue(xPos - 1, yPos);
					mark[xPos][yPos] = Status::NX;
				}
				else
				{
					memo[xPos][yPos] = getMemoValue(xPos, yPos - 1);
					mark[xPos][yPos] = Status::NY;
				}
			}
		}
	}

	/*
	 * generate common sequence according to mark
	 */
	void generateCommonSeq(int xPos, int yPos)  // 根据mark生成commonSeq
	{
		// 递归基情况
		if (xPos == -1 || yPos == -1)
		{
			std::reverse(commonSeq.begin(), commonSeq.end());
			return;
		}

		switch (mark[xPos][yPos])
		{
		case Status::Y:  // seqX[xPos] == seqY[yPos]
		{
			commonSeq.push_back(seqX[xPos]);
			generateCommonSeq(xPos - 1, yPos - 1);
			break;
		}
		case Status::NX:  // needn't to consider seqX[xPos]
		{
			generateCommonSeq(xPos - 1, yPos);
			break;
		}
		case Status::NY:  // needn't to consider seqY[yPos]
		{
			generateCommonSeq(xPos, yPos - 1);
			break;
		}
		}
	}

public:
	/*
	 * constructor, receive two sequence
	 */
	LCS(const std::vector<T>& seq1, const std::vector<T>& seq2)
		: seqX(std::move(seq1)), seqY(std::move(seq2)),
		commonSeq(std::vector<T>()),
		memo(seqX.size(), std::vector<int>(seqY.size(), 0)),
		mark(seqX.size(), std::vector<Status>(seqY.size()))
	{}

	/*
	 * need to be called by user
	 * calculate the common sequence 
	 */
	void calculate()
	{
		// 计算mark和memo
		calculateMemoAndMark();
		// 生成commonSeq
		generateCommonSeq(seqX.size() - 1, seqY.size() - 1);
	}

	/*
	 * need to be called by user
	 * get the common sequence
	 */
	const std::vector<T>& getCommonSeq() const
	{
		return commonSeq;
	}
};

