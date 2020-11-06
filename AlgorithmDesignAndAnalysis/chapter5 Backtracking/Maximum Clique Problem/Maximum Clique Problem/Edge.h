#pragma once

#include <memory>


/*
 * 边类型
 */
class Edge
{	
	unsigned				vexRank;  // 所连接的顶点的秩
	double					weight;  // 权重
	std::shared_ptr<Edge>	next;  // 下一条边的指针

public:
	Edge(const unsigned vexRank, double weight = 0);  // constructor
	Edge(const Edge& edge);  // copy constructor
	~Edge() = default;
	Edge&					operator=(const Edge& rhs);
	unsigned				getVexRank() const noexcept;  // 获取这条边所连接的顶点在图的顶点向量中的秩
	double					getWeight() const noexcept;  // 获取这条边的权重
	std::shared_ptr<Edge>	getNext() const noexcept;  // 获取下一条边的指针
	bool					hasNext() const noexcept;  // 判断是否有下一条边
	bool					addNext(const unsigned vexRank, double weight = 0) noexcept;  // 增加一条边，参数为所连接的顶点的秩和边的权重
	void					unsafe_setNext(std::shared_ptr<Edge>);  // 修改next，危险，谨慎使用
};

