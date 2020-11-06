#include "MCP.h"
#include <unordered_set>

using namespace std;

MCP::MCP(const Undigraph& graph)
	:graph(graph), hasSolved(false), sol(graph.vexSize()),
	curClique(graph.vexSize()), curCliqueSize(0), bound(0), topTree(make_shared<SearchTree>())
{}

int MCP::boundFunc() const
{
	return bound;
}

int MCP::costFunc(int curLayer) const
{
	return static_cast<int>(curClique.size()) + graph.vexSize() - curLayer;
}

bool MCP::isConnected(unsigned curVexRank) const
{
	unordered_set<unsigned> hashTable;
	auto ptr = graph.getfirstEdge(curVexRank);
	while(ptr != nullptr)
	{
		hashTable.insert(ptr->getVexRank());
		ptr = ptr->getNext();
	}
	for(unsigned rank = 0; rank < curVexRank; rank++)
	{
		if (curClique[rank] == 0) continue;
		if (hashTable.find(rank) == hashTable.end())
			return false;
	}
	return true;
}


bool MCP::canExpand(const SearchTree& tree) const
{
	if (!tree.isFirstChild && tree.getInfo() == 0)
		return false;
	if (costFunc(tree.getLayer()) <= boundFunc())
		return false;
	if (!isConnected(tree.getRoot()))
		return false;
	return true;
}

shared_ptr<SearchTree> MCP::backtrack(shared_ptr<SearchTree> tree)
{
	while (tree->getInfo() != 1)
	{
		if (tree->getParent() != nullptr)
			tree = tree->getParent();
		else
			return topTree;
	}
	return tree;
}

void MCP::expand(shared_ptr<SearchTree> tree)
{
	// 当到达叶子节点时
	if (tree->getLayer() == static_cast<int>(graph.vexSize()))
	{
		bound = curCliqueSize;
		sol = curClique;
	}
	
	if (!canExpand(*tree)) // 判断是否可以扩展
	{
		if (tree == topTree)
			return;
		tree = backtrack(tree);  // 回溯到info == 1的节点
	}
	if(tree->isFirstChild == true)
	{
		tree->setInfo(1);
		if (tree->getParent() != nullptr)
			tree->childFactory(tree->getRoot() + 1, 1);
		else // 此时tree为topTree
			tree->childFactory(1, 1, topTree);
		tree->isFirstChild = false;
		curCliqueSize++;
	}
	else  // tree->info == 1
	{
		tree->setInfo(0);
		if (tree->getParent() != nullptr)
			tree->childFactory(tree->getRoot() + 1, 1);
		else // 此时tree为topTree
			tree->childFactory(1, 1, topTree);
		curCliqueSize--;
	}
	curClique[tree->getRoot()] = tree->getInfo();
	tree = tree->getChild();
	expand(tree);
}



vector<unsigned> MCP::getSolution()
{
	// 如果已经求解过:
	if (!hasSolved)
	{
		expand(topTree);
		hasSolved = true;
	}
	return sol;
}


