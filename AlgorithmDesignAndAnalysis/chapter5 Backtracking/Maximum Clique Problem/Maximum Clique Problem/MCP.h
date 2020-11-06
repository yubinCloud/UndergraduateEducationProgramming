#pragma once

#include "Undigraph.h"
#include "SearchTree.h"
#include <vector>

using std::vector;

/*
 * 最大团问题
 */
class MCP
{
    Undigraph                   graph; // 无向图
    bool                        hasSolved;  // 标志问题是否已经解决
    vector<unsigned>            sol;  // 计算出的最大团（顶点集合）
    vector<unsigned>            curClique;  // 当前团
    int                         curCliqueSize;
    int                         bound;  // 界
    std::shared_ptr<SearchTree> topTree;
public:
	MCP(const Undigraph&);
    vector<unsigned>            getSolution();
    
private:
    int                         costFunc(int curLayer) const;  // 代价函数
    int                         boundFunc() const;  // 界函数
    bool                        isConnected(unsigned curVexRank) const; // 检查当前顶点是否与当前的团的所有顶点相连
    bool                        canExpand(const SearchTree&) const;
    std::shared_ptr<SearchTree> backtrack(std::shared_ptr<SearchTree> tree);
    void                        expand(std::shared_ptr<SearchTree> tree);
};