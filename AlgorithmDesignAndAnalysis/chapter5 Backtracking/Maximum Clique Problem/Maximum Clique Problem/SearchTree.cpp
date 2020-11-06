#include "SearchTree.h"
#include "MCP.h"

SearchTree::SearchTree()
	:root(0), layer(0), info(), child(nullptr), parent(nullptr), isFirstChild(true)
{}



SearchTree::SearchTree(RootType root, int layer, InfoType info, std::shared_ptr<SearchTree> parent)
	:root(root), layer(layer), info(info), child(nullptr), parent(std::move(parent)), isFirstChild(true)
{}

SearchTree::SearchTree(RootType root, int layer, std::shared_ptr<SearchTree> parent)
	:root(root), layer(layer), info(), child(nullptr), parent(std::move(parent)), isFirstChild(true)
{}



void SearchTree::childFactory(RootType root, InfoType childInfo)
{
	child = std::make_shared<SearchTree>(root, layer + 1, childInfo, parent->child);
}

void SearchTree::childFactory(RootType root, InfoType childInfo, std::shared_ptr<SearchTree> selfPtr)
{
	child = std::make_shared<SearchTree>(root, layer + 1, childInfo, std::move(selfPtr));
}


std::shared_ptr<SearchTree> SearchTree::getChild() const noexcept
{
	return child;
}

SearchTree::InfoType SearchTree::getInfo() const noexcept
{
	return info;
}

void SearchTree::setInfo(InfoType info) noexcept
{
	this->info = info;
}


int SearchTree::getLayer() const noexcept
{
	return layer;
}

std::shared_ptr<SearchTree> SearchTree::getParent() const noexcept
{
	return parent;
}

SearchTree::RootType SearchTree::getRoot() const noexcept
{
	return root;
}




