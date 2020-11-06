#include "Prim.h"

using namespace std;
using namespace yubin;
bool checkGraphEmpty(Graph& graph);
void findMinEdgeAndAddToTree(Graph& graph, Graph& tree);


Prim::Prim(Graph& graph) noexcept
	: graph(graph), spanningTree(this->graph.vexSize(), false)
{
	prim();
}


Graph& Prim::getSpanningTree() noexcept
{
	return spanningTree;
}

void Prim::prim() noexcept
{
	// 首先将第一个顶点放入生成树中
	spanningTree[0].setInfo(true);
	graph[0].setInfo(false);
	
	while(!graph.empty())  // 如果graph还有节点
	{
		// 找出最小权重边将其添加入spanningTree中
		findMinEdgeAndAddToTree(graph, spanningTree);
	}
}


/*
 * 从graph中找出可以加入到tree的最小权重的边，并将对应节点和边加入tree中
 * 返回一个pair，pair.first为未加入的节点的rank，pair.second为最小权重的边
 */
void findMinEdgeAndAddToTree(Graph& graph, Graph& tree)
{
	const auto size = graph.vexSize();
	unsigned resVex = 0;  // graph中最小权重所连的顶点  
	shared_ptr<Edge> resEdge = nullptr;  // graph中最小权重的边指针
	for (unsigned i = 0; i < size; ++i)
	{
		if (graph[i].getInfo() == false)  // 如果此点不存在
			continue;
		for (auto e = graph.getFirstEdge(i); e != nullptr; e = e->getNext())  // 遍历所有边
		{
			if (tree[e->getVexRank()].getInfo() == false)  // 如果这条边所连的点在tree中不存在
			{
				continue;
			}
			if (resEdge == nullptr || resEdge->getWeight() > e->getWeight())  // 更新ePtr和vRank
			{
				resEdge = e;
				resVex = i;
			}
		}
	}
	graph[resVex].setInfo(false);  // 在graph中去掉顶点
	tree[resVex].setInfo(true);  // 在spanningTree中去掉顶点
	tree.addEdge(resVex, resEdge->getVexRank(), resEdge->getWeight());  // 将边加进去
}
