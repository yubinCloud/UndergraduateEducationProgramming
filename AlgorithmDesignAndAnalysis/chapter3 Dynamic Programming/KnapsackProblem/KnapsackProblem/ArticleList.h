#pragma once

#include "Article.h"
#include <vector>

class ArticleList
{
private:
	const std::vector<Article> articleList_;
public:
	ArticleList(std::vector<Article>&);  // 构造函数
	ArticleList(ArticleList&&) noexcept;  // 移动构造函数
	~ArticleList() = default;  // 使用默认析构函数
	const Article& operator[](int) const;  // 重载下标运算符

	int getArticleCount() const;  // 返回物品数量
};

