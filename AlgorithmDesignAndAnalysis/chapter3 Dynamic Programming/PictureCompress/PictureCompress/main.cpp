#include "Picture.h"
#include <iostream>
#include <vector>

using std::vector;

int main()
{
	vector<Gray> grays = { 10,12,15,255,1,2 };
	
	Picture picture(grays);  // 根据灰度值创建图片对象
	picture.compress();  // 压缩图像
	picture.printSegments();  // 打印灰度分组结果
	
	return 0;
}