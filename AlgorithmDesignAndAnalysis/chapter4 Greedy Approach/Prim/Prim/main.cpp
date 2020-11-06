#include "Graph.h"
#include "Prim.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace yubin;

int main()
{
	// �����ݴ��ı��ж��벢����graph
	ifstream in("graph_data.txt");
	unsigned vexNum;  // ��������
	in >> vexNum;
	Graph graph(vexNum);  // ��ʼ��graph
	unsigned rank1, rank2; // һ���ߵ���������
	double weight;  // �ߵ�Ȩ��
	while(true)
	{
		in >> rank1;
		if (rank1 >= vexNum) break;
		in >> rank2 >> weight;
		graph.addEdge(rank1, rank2, weight);
	}
	// ��ӡԭʼͼ
	cout << "original graph:" << endl;
	graph.printGraph();
	// ʹ��prim�㷨
	Prim prim(graph);
	const auto tree = prim.getSpanningTree();
	cout << "spanning tree:" << endl;
	tree.printGraph();

	return 0;
}