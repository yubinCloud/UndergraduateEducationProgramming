#include "Graph.h"

#include <iostream>

using namespace yubin;

Graph::Graph()
	: vertexes({}), edgeNum(0)
{}


/*
 * param vexNum: ��ʼͼ�Ķ������
 */
Graph::Graph(const unsigned vexNum, Vertex::InfoType info)
	: edgeNum(0)
{
	for(unsigned i = 0; i != vexNum; i++)
	{
		vertexes.emplace_back(i, info);
	}
}

void Graph::copyVertexes(const std::vector<Vertex>& rhs)
{
	for (unsigned i = 0; i != rhs.size(); i++)
	{
		vertexes.emplace_back(i, rhs[i].info);
		auto iter2 = rhs[i].getFirstEdge();  // other���ױ�
		if (iter2 == nullptr) continue;
		vertexes[i].firstEdge = std::make_shared<Edge>(*iter2);
		auto iter1 = vertexes[i].firstEdge;
		while (iter2->hasNext())
		{
			iter2 = iter2->getNext();
			iter1->addNext(iter2->getVexRank(), iter2->getWeight());
			iter1 = iter1->getNext();
		}
	}
}

/*
 * copy constructor
 */
Graph::Graph(const Graph& rhs)
	: edgeNum(rhs.edgeSize())
{
	copyVertexes(rhs.vertexes);
}

/*
 * move constructor
 */
Graph::Graph(Graph&& rhs) noexcept
	: vertexes(std::move(rhs.vertexes)), edgeNum(rhs.edgeSize())
{}


Graph& Graph::operator=(const Graph& rhs)
{
	if (this == &rhs)
		return *this;
	edgeNum = rhs.edgeNum;
	vertexes.clear();
	copyVertexes(rhs.vertexes);
	return *this;
}

Graph& Graph::operator=(Graph&& rhs) noexcept
{
	if (this == &rhs)
		return *this;
	edgeNum = rhs.edgeNum;
	vertexes = std::move(rhs.vertexes);
	return *this;
}


/*
 * param info: �����Ӷ���Ķ�����Ϣ
 */
bool Graph::addVertex(const Vertex::InfoType& info)
{
	vertexes.emplace_back(vertexes.size(), info);
	return true;
}

/*
 * param rank: ��Ҫ��ȡ�Ķ������
 */
Vertex& Graph::operator[](const unsigned rank)
{
	return vertexes[rank];
}

/*
 * param vexRank1, vexRank2: ��Ҫ���ӵıߵ����߶���
 */
bool Graph::addEdge(const unsigned vexRank1, const unsigned vexRank2, const double weight)
{
	vertexes[vexRank1].addEdge(vexRank2, weight);
	vertexes[vexRank2].addEdge(vexRank1, weight);
	++edgeNum;
	return true;
}

bool Graph::delEdge(const unsigned vexRank1, const unsigned vexRank2)
{
	auto& vex1 = vertexes[vexRank1];
	auto& vex2 = vertexes[vexRank2];
	return vex1.delEdge(vexRank2) && vex2.delEdge(vexRank1);
}


/*
 * param rank: ��Ҫ��ȡ�ĸ�����ĵ�һ����
 */
std::shared_ptr<Edge> Graph::getFirstEdge(const unsigned rank) const
{
	return vertexes[rank].firstEdge;
}


void Graph::printGraph() const
{
	for(auto& v: vertexes)
	{
		v.printEdges();
	}
}

unsigned Graph::vexSize() const noexcept
{
	return vertexes.size();
}

unsigned Graph::edgeSize() const noexcept
{
	return edgeNum;
}

bool Graph::empty() const noexcept
{
	for(auto& v:vertexes)
	{
		if (v.getInfo() == true)
			return false;
	}
	return true;
}

std::shared_ptr<Edge> Graph::minWeightEdge() const noexcept
{
	std::shared_ptr<Edge> minEdgePtr = nullptr;  // ��СȨ�ض�Ӧ�ߵ�ָ��
	auto minWeight = DBL_MAX;  // double���ֵ
	for(auto& v: vertexes)
	{
		if (v.getInfo() == false)
			continue;
		const auto edgePtr = v.getFirstEdge();
		if(edgePtr->getWeight() < minWeight)
		{
			minEdgePtr = edgePtr;
			minWeight = edgePtr->getWeight();
		}
	}
	return minEdgePtr;
}


