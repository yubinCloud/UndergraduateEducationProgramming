#pragma once

#include <memory>
#include <stdexcept>
#include <vector>


class SearchTree
{	
	using RootType = unsigned;  // ������
	using InfoType = int;
	
	RootType						root;  // ���ڵ�
	int								layer;  // ��������ڵĲ���
	InfoType						info;  // �ýڵ����Ϣ
	std::shared_ptr<SearchTree>		child;  // ���ӵ�ָ��
	std::shared_ptr<SearchTree>		parent; // ���ڵ��ָ��
public:
	SearchTree();
	SearchTree(RootType root, int layer, std::shared_ptr<SearchTree> parent);
	SearchTree(RootType root, int layer, InfoType info, std::shared_ptr<SearchTree> parent);
	RootType						getRoot() const noexcept;
	int								getLayer() const noexcept;
	InfoType						getInfo() const noexcept;
	void							setInfo(InfoType info) noexcept;
	std::shared_ptr<SearchTree>		getChild() const noexcept;
	std::shared_ptr<SearchTree>		getParent() const noexcept;
	void							childFactory(RootType root, InfoType childInfo);  // ����һ������
	void							childFactory(RootType root, InfoType childInfo, std::shared_ptr<SearchTree> selfPtr);  // ����һ������
	bool							isFirstChild;
private:
};

