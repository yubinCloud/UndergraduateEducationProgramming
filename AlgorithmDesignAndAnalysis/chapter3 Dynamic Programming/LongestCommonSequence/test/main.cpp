#include "LCS.h"
#include <iostream>
#include <vector>

using std::vector;

int main()
{
	vector<char> seqX = { 'A', 'B', 'C', 'B', 'D', 'A', 'B' };
	vector<char> seqY = { 'B','D','C','A','B','A' };

	LCS<char> lcs(seqX, seqY);

	lcs.calculate();
	auto commonSeq = lcs.getCommonSeq();

	for (auto i : commonSeq)
		std::cout << i << ", ";
	std::cout << std::endl;

	return 0;
}