#include "Edge.h"

Edge::Edge(const unsigned vexRank, double weight)
	: vexRank(vexRank), weight(weight), next(nullptr)
{}

unsigned Edge::getVexRank() const noexcept
{
	return vexRank;
}

double Edge::getWeight() const noexcept
{
	return weight;
}

std::shared_ptr<Edge> Edge::getNext() const noexcept
{
	return next;
}

bool Edge::hasNext() const noexcept
{
	return next != nullptr;
}

bool Edge::addNext(const unsigned vexRank, double weight) noexcept
{
	if (hasNext())
		return false;
	next = std::make_shared<Edge>(vexRank, weight);
	return true;
}

Edge::Edge(const Edge& edge)
	:vexRank(edge.vexRank),
	weight(edge.weight),
	next(nullptr)  // ²»¿½±´next
{}

Edge& Edge::operator=(const Edge& rhs)
{
	if (this != &rhs)
	{
		vexRank = rhs.vexRank;
		weight = rhs.weight;
		next = nullptr;
	}
	return *this;
}

void Edge::unsafe_setNext(std::shared_ptr<Edge> ptr)
{
	next = std::move(ptr);
}

