#include <iostream>
#include <vector>
#include "Sequence.h"


using std::vector;


int main()
{
	vector<int> seq = { 2,-5,8,11,-3,4,6 };
	Sequence<int> sequence(seq);

	sequence.printResult();

	return 0;
}