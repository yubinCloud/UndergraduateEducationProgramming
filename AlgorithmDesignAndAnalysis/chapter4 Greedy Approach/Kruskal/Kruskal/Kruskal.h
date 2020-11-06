#pragma once
#include "Graph.h"

namespace yubin
{
	class Kruskal
	{
		Graph			graph;  // ����ͼ
		Graph			sol;  // ������ͼ
	public:
		Kruskal(Graph&);  // constructor
		Graph			getSol() const noexcept;  // ��ȡ������
	private:
		void			kruskal();  // ����Kruskal�㷨
	};
}
