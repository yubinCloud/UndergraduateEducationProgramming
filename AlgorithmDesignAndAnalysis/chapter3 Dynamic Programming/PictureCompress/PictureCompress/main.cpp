#include "Picture.h"
#include <iostream>
#include <vector>

using std::vector;

int main()
{
	vector<Gray> grays = { 10,12,15,255,1,2 };
	
	Picture picture(grays);  // ���ݻҶ�ֵ����ͼƬ����
	picture.compress();  // ѹ��ͼ��
	picture.printSegments();  // ��ӡ�Ҷȷ�����
	
	return 0;
}