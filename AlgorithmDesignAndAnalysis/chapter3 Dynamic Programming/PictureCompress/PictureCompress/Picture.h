#pragma once

#include <vector>

using Gray = int;  // Gray表示灰度值

class Picture
{
private:
	std::vector<Gray> grays;  // 灰度值序列
	std::vector<int> S;  // S[i]表示输入为grays[0:i]的最优分段存储所使用的的二进制位数
	std::vector<int> lastSegmentCount;  // 表示达到最少位数时最后一段的灰度值个数
	std::vector<int> bytes;  // bytes[i]表示grays[i]像素的二进制位数

	int bestBytesBefore(int i) const;  // 获取第i个元素之前（包含第i个元素）的最优分段存储所使用的二进制位数
	std::vector<std::vector<Gray>> trackback() const;  // 获取分组结果
public:
	Picture(std::vector<Gray>& grays);  // 构造函数
	void compress();  // 进行图片压缩
	void printSegments() const;  // 打印分组结果
};

