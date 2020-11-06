#include "Picture.h"
#include <algorithm>
#include <iostream>

using std::vector;

Picture::Picture(std::vector<Gray>& grays)
	: grays(std::move(grays)), S(this->grays.size()), lastSegmentCount(this->grays.size()), 
	bytes(this->grays.size())
{
	// ��ʼ��bites
	for(int i = 0; i != this->grays.size(); i++)
	{
		bytes[i] = static_cast<int>(log2(this->grays[i])) + 1;  // ����grays[i]�Ҷ�ֵ�Ķ�����λ��
	}
}


void Picture::compress()
{
	const int segmentMaxLen = 256;  // ÿ�ε���󳤶�
	const int headLen = 11;  // ÿ�ζ�ͷ����

	for(int rear = 0; rear != grays.size(); rear++)  // ��߽�rear��0��ʼ�����μ���grays[0:rear]�����Ŵ洢λ��
	{
		// ��gray[rear]��Ϊ���һ�ε����
		lastSegmentCount[rear] = 1;
		int byteMax = bytes[rear];  // byteMax: �洢���һ��ÿ�����صĶ�����λ��
		S[rear] = bestBytesBefore(rear - 1) + byteMax;

		// �����һ�εĳ��� lastSegLen = 2 ��ʼ�������ӳ��� min(rear + 1, segmentMaxLen)
		for(int lastSegLen = 2; lastSegLen <= std::min(rear + 1, segmentMaxLen); lastSegLen++)
		{
			// ����byteMax��ͨ���ж��¼����Ԫ��
			byteMax = byteMax < bytes[rear - lastSegLen + 1] ? bytes[rear - lastSegLen + 1] : byteMax;

			if (bestBytesBefore(rear - lastSegLen) + lastSegLen * byteMax < bestBytesBefore(rear))
			{
				S[rear] = bestBytesBefore(rear - lastSegLen) + lastSegLen * byteMax;
				lastSegmentCount[rear] = lastSegLen;
			}
		}

		S[rear] += headLen;  // �洢λ���������һ�εĶ�ͷ��ռ��λ��
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

	// ����
	if (grays.empty())  return result;
	
	int rear = grays.size() - 1;  // ��β����ʼ׷��
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
