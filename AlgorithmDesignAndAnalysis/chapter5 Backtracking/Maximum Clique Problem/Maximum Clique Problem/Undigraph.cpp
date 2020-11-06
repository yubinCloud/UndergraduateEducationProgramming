#include "Undigraph.h"

#include <iostream>

Undigraph::Undigraph()
	: vertexes({}), edgeNum(0)
{}

/*
 * param vexNum: ��ʼͼ�Ķ������
 */
Undigraph::Undigraph(const unsigned vexNum)
	: edgeNum(0)
{
	for(unsigned i = 0; i != vexNum; i++)
	{
		vertexes.emplace_back(i);
	}
}


Undigraph::Undigraph(const Undigraph& other)
	: edgeNum(other.edgeSize())
{
	for (unsigned i = 0; i != other.vexSize(); i++)
	{
		vertexes.emplace_back(i, other.vertexes[i].info);
		auto iter2 = other.getfirstEdge(i);  // other���ױ�
		if (iter2 == nullptr) continue;
		vertexes[i].firstEdge = std::make_shared<Edge>(*iter2);
		auto iter1 = vertexes[i].firstEdge;
		while(iter2->hasNext())
		{
			iter2 = iter2->getNext();
			iter1->addNext(iter2->getVexRank(), iter2->getWeight());
			iter1 = iter1->getNext();
		}
	}
}


/*
 * param info: �����Ӷ���Ķ�����Ϣ
 */
bool Undigraph::addVertex(const Vertex::InfoType& info)
{
	vertexes.emplace_back(vertexes.size(), info);
	return true;
}

/*
 * param rank: ��Ҫ��ȡ�Ķ������
 */
Vertex& Undigraph::operator[](const unsigned rank)
{
	return vertexes[rank];
}

/*
 * param vexRank1, vexRank2: ��Ҫ���ӵıߵ����߶���
 */
bool Undigraph::addEdge(const unsigned vexRank1, const unsigned vexRank2, const double weight)
{
	vertexes[vexRank1].addEdge(vexRank2, weight);
	vertexes[vexRank2].addEdge(vexRank1, weight);
	++edgeNum;
	return true;
}

bool Undigraph::delEdge(const unsigned vexRank1, const unsigned vexRank2)
{
	auto& vex1 = vertexes[vexRank1];
	auto& vex2 = vertexes[vexRank2];
	return vex1.delEdge(vexRank2) && vex2.delEdge(vexRank1);
}


/*
 * param rank: ��Ҫ��ȡ�ĸ�����ĵ�һ����
 */
std::shared_ptr<Edge> Undigraph::getfirstEdge(const unsigned rank) const
{
	return vertexes[rank].firstEdge;
}


void Undigraph::printGraph() const
{
	for(auto& v: vertexes)
	{
		v.printEdges();
	}
}

unsigned Undigraph::vexSize() const noexcept
{
	return vertexes.size();
}

unsigned Undigraph::edgeSize() const noexcept
{
	return edgeNum;
}

