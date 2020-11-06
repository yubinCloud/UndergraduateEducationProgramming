#pragma once

#include <memory>


/*
 * ������
 */
class Edge
{	
	unsigned				vexRank;  // �����ӵĶ������
	double					weight;  // Ȩ��
	std::shared_ptr<Edge>	next;  // ��һ���ߵ�ָ��

public:
	Edge(const unsigned vexRank, double weight = 0);  // constructor
	Edge(const Edge& edge);  // copy constructor
	~Edge() = default;
	Edge&					operator=(const Edge& rhs);
	unsigned				getVexRank() const noexcept;  // ��ȡ�����������ӵĶ�����ͼ�Ķ��������е���
	double					getWeight() const noexcept;  // ��ȡ�����ߵ�Ȩ��
	std::shared_ptr<Edge>	getNext() const noexcept;  // ��ȡ��һ���ߵ�ָ��
	bool					hasNext() const noexcept;  // �ж��Ƿ�����һ����
	bool					addNext(const unsigned vexRank, double weight = 0) noexcept;  // ����һ���ߣ�����Ϊ�����ӵĶ�����Ⱥͱߵ�Ȩ��
	void					unsafe_setNext(std::shared_ptr<Edge>);  // �޸�next��Σ�գ�����ʹ��
};

