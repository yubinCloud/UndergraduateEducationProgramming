#include "Vertex.h"

#include <iostream>

using namespace yubin;

Vertex::Vertex(int seqNum)
	: seqNum(seqNum), info(false), firstEdge(nullptr)
{}


Vertex::Vertex(int seqNum, InfoType info)
	: seqNum(seqNum), info(info), firstEdge(nullptr)
{}

bool Vertex::operator==(const Vertex& rhs) const noexcept
{
	return this->getSeqNum() == rhs.getSeqNum();
}

const Vertex::InfoType& Vertex::getInfo() const noexcept
{
	return info;
}

void Vertex::setInfo(const InfoType newInfo)
{
	info = newInfo;
}



int Vertex::getSeqNum() const noexcept
{
	return seqNum;
}

bool Vertex::addEdge(const unsigned vexRank, const double weight)
{
	auto newEdgePtr = std::make_shared<Edge>(vexRank, weight);
	newEdgePtr->setNext(firstEdge);
	firstEdge = std::move(newEdgePtr);
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
	cur->setNext(next->getNext());
	next = nullptr;
	return true;
}


std::shared_ptr<Edge> Vertex::getFirstEdge() const noexcept
{
	return firstEdge;
}
