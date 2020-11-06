#pragma once
#include "Graph.h"

namespace yubin
{
	class Kruskal
	{
		Graph			graph;  // 输入图
		Graph			sol;  // 计算结果图
	public:
		Kruskal(Graph&);  // constructor
		Graph			getSol() const noexcept;  // 获取运算结果
	private:
		void			kruskal();  // 运行Kruskal算法
	};
}
