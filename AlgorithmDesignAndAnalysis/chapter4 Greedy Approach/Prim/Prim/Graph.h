#pragma once

#include <vector>
#include "Vertex.h"
#include "Edge.h"

namespace yubin
{
	/*
 * 无向图类
 */
	class Graph
	{
		std::vector<Vertex>		vertexes;  // 顶点向量
		unsigned				edgeNum;  // 边的数量
	public:
		explicit Graph();  // constructor
		explicit Graph(unsigned vexNum, Vertex::InfoType info = true);  // constructor
		Graph(const Graph& rhs);	// copy constructor
		Graph(Graph&& rhs) noexcept;  // move constructor
		~Graph() noexcept = default;  // destructor
		Graph&					operator=(const Graph&);  // assignment operator
		Graph&					operator=(Graph&&) noexcept;  // move operator
		Vertex&					operator[](unsigned rank);  // 根据下标返回对应的顶点
		std::shared_ptr<Edge>	getFirstEdge(unsigned rank) const;  // 获取某个指定顶点的第一条边的指针
		bool					addVertex(const Vertex::InfoType& info);  // 增加一个顶点
		bool					addEdge(unsigned vexRank1, unsigned vexRank2, double weight = 0);  // 增加一条边
		bool					delEdge(unsigned vexRank1, unsigned vexRank2); // 删除一条边
		void					printGraph() const;  // 在标准输出打印这个图
		unsigned				vexSize() const noexcept;  // 获取顶点数量
		unsigned				edgeSize() const noexcept;  // 获取边的数量
		bool					empty() const noexcept;
		std::shared_ptr<Edge>	minWeightEdge() const noexcept;
	private:
		void					copyVertexes(const std::vector<Vertex>& rhs);  // 将另一个图的所有顶点拷贝到本图中
	};


}