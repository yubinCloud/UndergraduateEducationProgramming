#include <iostream>
#include <vector>

#include "MatrixChain.h"

using std::vector;

int main()
{
	vector<int> P = { 30, 35, 15, 5, 10, 20 };

	MatrixChain matrixChain(P);

	matrixChain.printResult();

	return 0;
}