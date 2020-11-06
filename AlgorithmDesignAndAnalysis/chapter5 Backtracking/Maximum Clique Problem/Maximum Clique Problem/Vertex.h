#pragma once

#include <string>
#include "Edge.h"

class Undigraph;

/*
 * ������
 */
class Vertex
{
	friend Undigraph; 
	using InfoType = std::string;
	
	const int				seqNum;  // �������
	InfoType				info;  // ������Ϣ
	std::shared_ptr<Edge>	firstEdge;  // ��һ����
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

