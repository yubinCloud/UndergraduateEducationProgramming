#pragma once

#include "Graph.h"

namespace yubin
{
	class Prim
	{
		Graph graph;  // 连通图
		Graph spanningTree;  // 最小生成树
	public:
		explicit Prim(Graph&) noexcept;  // 根据连通图graph构造出Prim算法
		Graph& getSpanningTree() noexcept;  // 获取最小生成树
	private:
		void prim() noexcept;
	};
}

