#pragma once

#include <vector>
#include "Vertex.h"
#include "Edge.h"

namespace yubin
{
	/*
 * ����ͼ��
 */
	class Graph
	{
		std::vector<Vertex>		vertexes;  // ��������
		unsigned				edgeNum;  // �ߵ�����
	public:
		explicit Graph();  // constructor
		explicit Graph(unsigned vexNum, Vertex::InfoType info = true);  // constructor
		Graph(const Graph& rhs);	// copy constructor
		Graph(Graph&& rhs) noexcept;  // move constructor
		~Graph() noexcept = default;  // destructor
		Graph&					operator=(const Graph&);  // assignment operator
		Graph&					operator=(Graph&&) noexcept;  // move operator
		Vertex&					operator[](unsigned rank);  // �����±귵�ض�Ӧ�Ķ���
		std::shared_ptr<Edge>	getFirstEdge(unsigned rank) const;  // ��ȡĳ��ָ������ĵ�һ���ߵ�ָ��
		bool					addVertex(const Vertex::InfoType& info);  // ����һ������
		bool					addEdge(unsigned vexRank1, unsigned vexRank2, double weight = 0);  // ����һ����
		bool					delEdge(unsigned vexRank1, unsigned vexRank2); // ɾ��һ����
		void					printGraph() const;  // �ڱ�׼�����ӡ���ͼ
		unsigned				vexSize() const noexcept;  // ��ȡ��������
		unsigned				edgeSize() const noexcept;  // ��ȡ�ߵ�����
		bool					empty() const noexcept;
		std::shared_ptr<Edge>	minWeightEdge() const noexcept;
	private:
		void					copyVertexes(const std::vector<Vertex>& rhs);  // ����һ��ͼ�����ж��㿽������ͼ��
	};


}