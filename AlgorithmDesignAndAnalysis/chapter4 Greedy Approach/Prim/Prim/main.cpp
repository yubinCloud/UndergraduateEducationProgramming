#include "Graph.h"
#include "Prim.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace yubin;

int main()
{
	// 将数据从文本中读入并建立graph
	ifstream in("graph_data.txt");
	unsigned vexNum;  // 顶点数量
	in >> vexNum;
	Graph graph(vexNum);  // 初始化graph
	unsigned rank1, rank2; // 一条边的两个顶点
	double weight;  // 边的权重
	while(true)
	{
		in >> rank1;
		if (rank1 >= vexNum) break;
		in >> rank2 >> weight;
		graph.addEdge(rank1, rank2, weight);
	}
	// 打印原始图
	cout << "original graph:" << endl;
	graph.printGraph();
	// 使用prim算法
	Prim prim(graph);
	const auto tree = prim.getSpanningTree();
	cout << "spanning tree:" << endl;
	tree.printGraph();

	return 0;
}