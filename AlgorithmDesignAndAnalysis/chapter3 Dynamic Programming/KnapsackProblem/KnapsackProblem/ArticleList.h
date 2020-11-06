#pragma once

#include "Article.h"
#include <vector>

class ArticleList
{
private:
	const std::vector<Article> articleList_;
public:
	ArticleList(std::vector<Article>&);  // ���캯��
	ArticleList(ArticleList&&) noexcept;  // �ƶ����캯��
	~ArticleList() = default;  // ʹ��Ĭ����������
	const Article& operator[](int) const;  // �����±������

	int getArticleCount() const;  // ������Ʒ����
};

