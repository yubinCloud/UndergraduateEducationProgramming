#include "ArticleList.h"

ArticleList::ArticleList(std::vector<Article>& list):
	articleList_(std::move(list))
	{}

ArticleList::ArticleList(ArticleList&& rhs) noexcept
	: articleList_(rhs.articleList_)
{}


const Article& ArticleList::operator[](int k) const
{
	// ���ص�k����Ʒ
	return articleList_[k - 1];
}



int ArticleList::getArticleCount() const
{
	return articleList_.size();
}
