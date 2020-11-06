#pragma once

#include "Undigraph.h"
#include "SearchTree.h"
#include <vector>

using std::vector;

/*
 * ���������
 */
class MCP
{
    Undigraph                   graph; // ����ͼ
    bool                        hasSolved;  // ��־�����Ƿ��Ѿ����
    vector<unsigned>            sol;  // �����������ţ����㼯�ϣ�
    vector<unsigned>            curClique;  // ��ǰ��
    int                         curCliqueSize;
    int                         bound;  // ��
    std::shared_ptr<SearchTree> topTree;
public:
	MCP(const Undigraph&);
    vector<unsigned>            getSolution();
    
private:
    int                         costFunc(int curLayer) const;  // ���ۺ���
    int                         boundFunc() const;  // �纯��
    bool                        isConnected(unsigned curVexRank) const; // ��鵱ǰ�����Ƿ��뵱ǰ���ŵ����ж�������
    bool                        canExpand(const SearchTree&) const;
    std::shared_ptr<SearchTree> backtrack(std::shared_ptr<SearchTree> tree);
    void                        expand(std::shared_ptr<SearchTree> tree);
};