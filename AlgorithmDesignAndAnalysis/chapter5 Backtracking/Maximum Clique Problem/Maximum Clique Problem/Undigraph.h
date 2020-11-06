#pragma once

#include <vector>
#include "Vertex.h"
#include "Edge.h"

/*
 * 无向图类
 */
class Undigraph
{
	std::vector<Vertex>		vertexes;  // 顶点向量
	unsigned				edgeNum;  // 边的数量
public:
	Undigraph();
	Undigraph(const unsigned vexNum);
	Undigraph(const Undigraph& other);
	Vertex&					operator[](const unsigned rank);  // 根据下标返回对应的顶点
	std::shared_ptr<Edge>	getfirstEdge(const unsigned rank) const;  // 获取某个指定顶点的第一条边的指针
	bool					addVertex(const Vertex::InfoType& info);  // 增加一个顶点
	bool					addEdge(const unsigned vexRank1, const unsigned vexRank2, const double weight = 0);  // 增加一条边
	bool					delEdge(const unsigned vexRank1, const unsigned vexRank2); // 删除一条边
	void					printGraph() const;  // 在标准输出打印这个图
	unsigned				vexSize() const noexcept;  // 获取顶点数量
	unsigned				edgeSize() const noexcept;  // 获取边的数量
};

