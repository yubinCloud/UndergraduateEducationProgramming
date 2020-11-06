#include "Kruskal.h"
using namespace yubin;

Kruskal::Kruskal(Graph& graph)
	: graph(graph), sol(graph.vexSize())
{
	kruskal();
}

Graph Kruskal::getSol() const noexcept
{
	return sol;
}

void Kruskal::kruskal()
{
	
}
