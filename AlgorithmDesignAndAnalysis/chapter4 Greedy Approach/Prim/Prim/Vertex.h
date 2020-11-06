#pragma once

#include <string>
#include "Edge.h"


namespace yubin
{
	class Graph;
	/*
 * ������
 */
	class Vertex
	{
		friend Graph;
		using InfoType = bool;

		const int				seqNum;  // �������
		InfoType				info;  // ������Ϣ����Ϊ0��ʾ�˵��Ѿ�������
		std::shared_ptr<Edge>	firstEdge;  // ��һ����
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
