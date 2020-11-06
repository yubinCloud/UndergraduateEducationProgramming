#include "Picture.h"
#include <algorithm>
#include <iostream>

using std::vector;

Picture::Picture(std::vector<Gray>& grays)
	: grays(std::move(grays)), S(this->grays.size()), lastSegmentCount(this->grays.size()), 
	bytes(this->grays.size())
{
	// 初始化bites
	for(int i = 0; i != this->grays.size(); i++)
	{
		bytes[i] = static_cast<int>(log2(this->grays[i])) + 1;  // 计算grays[i]灰度值的二进制位数
	}
}


void Picture::compress()
{
	const int segmentMaxLen = 256;  // 每段的最大长度
	const int headLen = 11;  // 每段端头长度

	for(int rear = 0; rear != grays.size(); rear++)  // 后边界rear从0开始，依次计算grays[0:rear]的最优存储位数
	{
		// 将gray[rear]作为最后一段的情况
		lastSegmentCount[rear] = 1;
		int byteMax = bytes[rear];  // byteMax: 存储最后一段每个像素的二进制位数
		S[rear] = bestBytesBefore(rear - 1) + byteMax;

		// 从最后一段的长度 lastSegLen = 2 开始，依次延长到 min(rear + 1, segmentMaxLen)
		for(int lastSegLen = 2; lastSegLen <= std::min(rear + 1, segmentMaxLen); lastSegLen++)
		{
			// 更新byteMax：通过判断新加入的元素
			byteMax = byteMax < bytes[rear - lastSegLen + 1] ? bytes[rear - lastSegLen + 1] : byteMax;

			if (bestBytesBefore(rear - lastSegLen) + lastSegLen * byteMax < bestBytesBefore(rear))
			{
				S[rear] = bestBytesBefore(rear - lastSegLen) + lastSegLen * byteMax;
				lastSegmentCount[rear] = lastSegLen;
			}
		}

		S[rear] += headLen;  // 存储位数加上最后一段的段头所占的位数
	}
}


int Picture::bestBytesBefore(const int i) const
{
	if (i < 0)
		return 0;
	else
		return S[i];
}


std::vector<std::vector<Gray>> Picture::trackback() const
{
	vector<vector<Gray>> result;

	// 特判
	if (grays.empty())  return result;
	
	int rear = grays.size() - 1;  // 从尾部开始追踪
	while(rear >= 0)
	{
		const int segLen = lastSegmentCount[rear];
		vector<Gray> segment;
		for(int i = segLen ; i != 0; i--)
		{
			segment.push_back(grays[rear - i + 1]);
		}
		result.push_back(std::move(segment));

		rear -= segLen;
	}
	std::reverse(result.begin(), result.end());

	return result;
}


void Picture::printSegments() const
{
	auto segments = std::move(trackback());

	for(auto &v: segments)
	{
		std::cout << "< ";
		for(auto gray: v)
		{
			std::cout << gray << " ";
		}
		std::cout << ">" << std::endl;
	}
}
