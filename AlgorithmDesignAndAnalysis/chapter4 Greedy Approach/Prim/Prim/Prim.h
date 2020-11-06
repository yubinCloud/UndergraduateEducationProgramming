#pragma once

#include "Graph.h"

namespace yubin
{
	class Prim
	{
		Graph graph;  // ��ͨͼ
		Graph spanningTree;  // ��С������
	public:
		explicit Prim(Graph&) noexcept;  // ������ͨͼgraph�����Prim�㷨
		Graph& getSpanningTree() noexcept;  // ��ȡ��С������
	private:
		void prim() noexcept;
	};
}

