#pragma once

#include <string>
#include "Edge.h"

class Undigraph;

/*
 * 顶点类
 */
class Vertex
{
	friend Undigraph; 
	using InfoType = std::string;
	
	const int				seqNum;  // 顶点序号
	InfoType				info;  // 顶点信息
	std::shared_ptr<Edge>	firstEdge;  // 第一条边
public:
	Vertex(int seqNum);
	Vertex(int seqNum, InfoType info);
	bool					operator==(const Vertex& rhs) const noexcept;
	int						getSeqNum() const noexcept;
	const InfoType&			getInfo() const noexcept;
	void					printEdges() const;
private:
	bool					addEdge(const unsigned vexRank, const double weight = 0);
	bool					delEdge(const unsigned vexRank);
};

