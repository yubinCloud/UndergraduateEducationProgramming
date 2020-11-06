#include "Huffman.h"

using namespace  std;

int main()
{
	vector<char> chars = { '0', '1', '2', '3', '4', '5', '6', '7' };
	vector<double> possiblities = { 5,5,10,15,25,10,10,20 };

	Huffman<char> huffman(chars, possiblities);

	return 0;
}