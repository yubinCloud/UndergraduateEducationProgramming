#pragma once

#include <vector>
#include "Vertex.h"
#include "Edge.h"

/*
 * ����ͼ��
 */
class Undigraph
{
	std::vector<Vertex>		vertexes;  // ��������
	unsigned				edgeNum;  // �ߵ�����
public:
	Undigraph();
	Undigraph(const unsigned vexNum);
	Undigraph(const Undigraph& other);
	Vertex&					operator[](const unsigned rank);  // �����±귵�ض�Ӧ�Ķ���
	std::shared_ptr<Edge>	getfirstEdge(const unsigned rank) const;  // ��ȡĳ��ָ������ĵ�һ���ߵ�ָ��
	bool					addVertex(const Vertex::InfoType& info);  // ����һ������
	bool					addEdge(const unsigned vexRank1, const unsigned vexRank2, const double weight = 0);  // ����һ����
	bool					delEdge(const unsigned vexRank1, const unsigned vexRank2); // ɾ��һ����
	void					printGraph() const;  // �ڱ�׼�����ӡ���ͼ
	unsigned				vexSize() const noexcept;  // ��ȡ��������
	unsigned				edgeSize() const noexcept;  // ��ȡ�ߵ�����
};

