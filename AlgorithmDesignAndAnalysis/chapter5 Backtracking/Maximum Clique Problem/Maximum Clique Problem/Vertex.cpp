#include "Vertex.h"

#include <iostream>

Vertex::Vertex(int seqNum)
	: seqNum(seqNum), info(""), firstEdge(nullptr)
{}


Vertex::Vertex(int seqNum, InfoType info)
	: seqNum(seqNum), info(std::move(info)), firstEdge(nullptr)
{}

bool Vertex::operator==(const Vertex& rhs) const noexcept
{
	return this->getSeqNum() == rhs.getSeqNum();
}

const Vertex::InfoType& Vertex::getInfo() const noexcept
{
	return info;
}

int Vertex::getSeqNum() const noexcept
{
	return seqNum;
}

bool Vertex::addEdge(const unsigned vexRank, const double weight)
{
	if (firstEdge == nullptr)
	{
		firstEdge = std::make_shared<Edge>(vexRank, weight);
		return true;
	}
	auto iter = firstEdge;
	while (iter->hasNext())
		iter = iter->getNext();
	iter->addNext(vexRank, weight);
	return true;
}

void Vertex::printEdges() const
{
	std::cout << getSeqNum() << ":";
	auto ptr = firstEdge;
	while (ptr != nullptr)
	{
		std::cout << " -> " << ptr->getVexRank();
		ptr = ptr->getNext();
	}
	std::cout << std::endl;
}

bool Vertex::delEdge(const unsigned vexRank)
{
	if (firstEdge == nullptr) return false;
	if (firstEdge->getVexRank() == vexRank)
	{
		firstEdge = firstEdge->getNext();
		return true;
	}
	// firstEdge->getVexRank() != vexRank
	auto cur = firstEdge;
	auto next = firstEdge->getNext();
	while (next != nullptr && next->getVexRank() != vexRank)
	{
		cur = next;
		next = cur->getNext();
	}
	if (next == nullptr) return false;
	// next->getVexRank() == vexRank
	cur->unsafe_setNext(next->getNext());
	next = nullptr;
	return true;
}
