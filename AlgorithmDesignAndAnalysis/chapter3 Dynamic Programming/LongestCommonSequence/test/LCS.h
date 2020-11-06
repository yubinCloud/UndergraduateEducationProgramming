#pragma once
#include <vector>

enum class Status { Y, NX, NY };  // ���״̬���ֱ��ʾ���������һ����ȡ�������X��������Y


template <typename T>
class LCS
{
private:
	std::vector<T> seqX;  // ��һ������
	std::vector<T> seqY;  // �ڶ�������
	std::vector<T> commonSeq;  // ��������

	std::vector<std::vector<int>> memo;  // ��¼����������еĳ���
	std::vector<std::vector<Status>> mark;  // ��¼�����������������ѡȡ��


	/*
	 * if xPos and yPos are nonnegative, return memo[xPos][yPos]
	 * if one of them is negative, return 0
	 */
	int getMemoValue(int xPos, int yPos) const
	{
		if (xPos >= 0 && yPos >= 0)
			return memo[xPos][yPos];
		else // ����һ��Ϊ0ʱ
			return 0;
	}

	/*
	 * calculate memo and mark
	 */
	void calculateMemoAndMark()  // ����memo��mark
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
	void generateCommonSeq(int xPos, int yPos)  // ����mark����commonSeq
	{
		// �ݹ�����
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
		// ����mark��memo
		calculateMemoAndMark();
		// ����commonSeq
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

