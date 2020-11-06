#pragma once

#include <vector>

using Gray = int;  // Gray��ʾ�Ҷ�ֵ

class Picture
{
private:
	std::vector<Gray> grays;  // �Ҷ�ֵ����
	std::vector<int> S;  // S[i]��ʾ����Ϊgrays[0:i]�����ŷֶδ洢��ʹ�õĵĶ�����λ��
	std::vector<int> lastSegmentCount;  // ��ʾ�ﵽ����λ��ʱ���һ�εĻҶ�ֵ����
	std::vector<int> bytes;  // bytes[i]��ʾgrays[i]���صĶ�����λ��

	int bestBytesBefore(int i) const;  // ��ȡ��i��Ԫ��֮ǰ��������i��Ԫ�أ������ŷֶδ洢��ʹ�õĶ�����λ��
	std::vector<std::vector<Gray>> trackback() const;  // ��ȡ������
public:
	Picture(std::vector<Gray>& grays);  // ���캯��
	void compress();  // ����ͼƬѹ��
	void printSegments() const;  // ��ӡ������
};

