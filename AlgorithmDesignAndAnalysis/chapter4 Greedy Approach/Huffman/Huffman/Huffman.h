#pragma once
#include "BiTree.h"
#include <queue>
#include <vector>
#include <utility>
#include <iostream>
#include <string>

template <typename T>
class Huffman
{
	std::vector<T> chars;  // �ַ���
	std::vector<double> possibilities;  // ���ʼ�
	std::shared_ptr<BiTree<T>> huffmanTree;

public:
	Huffman(std::vector<T>& chars, std::vector<double>& possibilities)
		:chars(std::move(chars)), possibilities(std::move(possibilities))
	{
		generateHuffmanTree();
	}

private:
	void generateHuffmanTree()
	{
		std::priority_queue<std::pair<double, std::shared_ptr<BiTree<T>>>> Q;  // �����������ȼ�����

		// ȫ��Ԫ�ؽ���
		for(int i = 0; i < static_cast<int>(chars.size()); i++)
		{
			std::pair<double, std::shared_ptr<BiTree<T>>> tempPair(possibilities[i], new BiTree<T>(chars[i]));
			Q.push(tempPair);
		}

		// ���������ϲ��������������
		const int count = chars.size();
		for(int i = 1; i < count; i++)
		{
			auto curTree = std::make_shared<BiTree<T>>();
			double curPossible = 0;
			auto tempPair = Q.top();
			curPossible += tempPair.first;
			curTree->setLeftChild(tempPair.second);
			Q.pop();
			tempPair = Q.top();
			curPossible += tempPair.first;
			curTree->setRightChild(tempPair.second);
			Q.pop();

			Q.push({curPossible, curTree});
		}

		huffmanTree = Q.top().second;
		std::cout << Q.top().first << std::endl;
	}
	
};