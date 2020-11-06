#pragma once

#include <string>
#include "Edge.h"


namespace yubin
{
	class Graph;
	/*
 * 顶点类
 */
	class Vertex
	{
		friend Graph;
		using InfoType = bool;

		const int				seqNum;  // 顶点序号
		InfoType				info;  // 顶点信息，若为0表示此点已经不存在
		std::shared_ptr<Edge>	firstEdge;  // 第一条边
	public:
		explicit Vertex(int seqNum);
		explicit Vertex(int seqNum, InfoType info);
		bool					operator==(const Vertex& rhs) const noexcept;
		int						getSeqNum() const noexcept;
		const InfoType&			getInfo() const noexcept;
		void					setInfo(InfoType newInfo);
		void					printEdges() const;
		std::shared_ptr<Edge>	getFirstEdge() const noexcept;
		void					addEdge(double weight = 0);
	private:
		bool					addEdge(unsigned vexRank, double weight = 0);
		bool					delEdge(unsigned vexRank);
	};


}
