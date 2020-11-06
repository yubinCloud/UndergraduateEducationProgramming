#include "MCP.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	Undigraph graph(5);
	graph.addEdge(0, 1);
	graph.addEdge(0, 2);
	graph.addEdge(0, 3);
	graph.addEdge(0, 4);
	graph.addEdge(1, 3);
	graph.addEdge(2, 3);
	graph.addEdge(2, 4);
	graph.addEdge(3, 4);
	MCP mcp(graph);
	auto sol = mcp.getSolution();
	for (auto n : sol)
		std::cout << n << std::endl;
}