#pragma once

#include <memory>

template <typename T>
class BiTree
{
	T data;
	std::shared_ptr<BiTree<T>> leftChild;
	std::shared_ptr<BiTree<T>> rightChild;
	std::weak_ptr<BiTree<T>> parent;

public:
	explicit BiTree(T data)
		:
	data(data)
	{}

	BiTree() = default;

	void setParent(std::weak_ptr<BiTree<T>> p)
	{
		parent = p;
	}
	
	void setData(T data)
	{
		this->data = data;
	}

	T getData() const
	{
		return data;
	}
	
	void setLeftChild(std::shared_ptr<BiTree<T>> lc)
	{
		leftChild = lc;
		lc->setParent(this);
	}

	BiTree& getLeftChild() const
	{
		return *leftChild;
	}
	
	void setRightChild(std::shared_ptr<BiTree<T>> rc)
	{
		rightChild = rc;
		lc->setParent(this);
	}

	BiTree& getRightChild() const
	{
		return *rightChild;
	}

	bool operator<(BiTree& rhs) const
	{
		return this->getData() < rhs.getData();
	}
};