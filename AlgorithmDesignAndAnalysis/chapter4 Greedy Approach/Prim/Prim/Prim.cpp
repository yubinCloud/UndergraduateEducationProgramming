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
	// ���Ƚ���һ�����������������
	spanningTree[0].setInfo(true);
	graph[0].setInfo(false);
	
	while(!graph.empty())  // ���graph���нڵ�
	{
		// �ҳ���СȨ�ر߽��������spanningTree��
		findMinEdgeAndAddToTree(graph, spanningTree);
	}
}


/*
 * ��graph���ҳ����Լ��뵽tree����СȨ�صıߣ�������Ӧ�ڵ�ͱ߼���tree��
 * ����һ��pair��pair.firstΪδ����Ľڵ��rank��pair.secondΪ��СȨ�صı�
 */
void findMinEdgeAndAddToTree(Graph& graph, Graph& tree)
{
	const auto size = graph.vexSize();
	unsigned resVex = 0;  // graph����СȨ�������Ķ���  
	shared_ptr<Edge> resEdge = nullptr;  // graph����СȨ�صı�ָ��
	for (unsigned i = 0; i < size; ++i)
	{
		if (graph[i].getInfo() == false)  // ����˵㲻����
			continue;
		for (auto e = graph.getFirstEdge(i); e != nullptr; e = e->getNext())  // �������б�
		{
			if (tree[e->getVexRank()].getInfo() == false)  // ��������������ĵ���tree�в�����
			{
				continue;
			}
			if (resEdge == nullptr || resEdge->getWeight() > e->getWeight())  // ����ePtr��vRank
			{
				resEdge = e;
				resVex = i;
			}
		}
	}
	graph[resVex].setInfo(false);  // ��graph��ȥ������
	tree[resVex].setInfo(true);  // ��spanningTree��ȥ������
	tree.addEdge(resVex, resEdge->getVexRank(), resEdge->getWeight());  // ���߼ӽ�ȥ
}
