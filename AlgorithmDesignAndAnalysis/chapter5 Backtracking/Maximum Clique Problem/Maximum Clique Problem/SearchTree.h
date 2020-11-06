#pragma once

#include <memory>
#include <stdexcept>
#include <vector>


class SearchTree
{	
	using RootType = unsigned;  // 根类型
	using InfoType = int;
	
	RootType						root;  // 根节点
	int								layer;  // 这棵树所在的层数
	InfoType						info;  // 该节点的信息
	std::shared_ptr<SearchTree>		child;  // 孩子的指针
	std::shared_ptr<SearchTree>		parent; // 父节点的指针
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
	void							childFactory(RootType root, InfoType childInfo);  // 生成一个孩子
	void							childFactory(RootType root, InfoType childInfo, std::shared_ptr<SearchTree> selfPtr);  // 生成一个孩子
	bool							isFirstChild;
private:
};

