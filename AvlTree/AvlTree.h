#pragma once
#include <iostream>
using namespace std;

template <class KEY, class OTHER>
struct SET
{
	KEY key;
	OTHER other;
};

template <class KEY, class OTHER>
class AvlTree
{
	struct AvlNode
	{
		SET<KEY, OTHER> data;
		AvlNode* left;
		AvlNode* right;
		int height;		//���ĸ߶�

		AvlNode(const SET<KEY, OTHER>& element, AvlNode* lt, AvlNode* rt, int h = 1)
			:data(element), left(lt), right(rt), height(h) {}
	};
	AvlNode* root;

public:
	AvlTree() { root = NULL; }
	~AvlTree() { makeEmpty(root); }
	SET<KEY, OTHER>* find(const KEY& x) const;	//�ǵݹ�
	void insert(const SET<KEY, OTHER>& x);
	void remove(const KEY& x );

private:
	void insert(const SET<KEY, OTHER>& x, AvlTree*& t);	//���ñ�֤��ָ��ĸ�����
	bool remove(const KEY& x, AvlNode*& t);
	void makeEmpty(AvlNode* t);
	int height(AvlNode* t) const { return t == NULL ? 0 : t->height; }
	void LL(AvlNode*& t);
	void RR(AvlNode*& t);
	void LR(AvlNode*& t);
	void RL(AvlNode*& t);
	int max(int a, int b) { return (a > b) ? a : b; }
	//����false˵�������䰫�����򷵻�true
	//��һ��������Ҫ���Ľڵ��ַ���ڶ�����0Ϊ�������䰫��1Ϊ�������䰫
	bool adjust(AvlNode*& t, int subTree);	


};