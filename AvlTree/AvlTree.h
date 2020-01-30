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
		int height;		//结点的高度

		AvlNode(const SET<KEY, OTHER>& element, AvlNode* lt, AvlNode* rt, int h = 1)
			:data(element), left(lt), right(rt), height(h) {}
	};
	AvlNode* root;

public:
	AvlTree() { root = NULL; }
	~AvlTree() { makeEmpty(root); }
	SET<KEY, OTHER>* find(const KEY& x) const;	//非递归
	void insert(const SET<KEY, OTHER>& x);
	void remove(const KEY& x );

private:
	void insert(const SET<KEY, OTHER>& x, AvlTree*& t);	//引用保证了指针的跟随性
	bool remove(const KEY& x, AvlNode*& t);
	void makeEmpty(AvlNode* t);
	int height(AvlNode* t) const { return t == NULL ? 0 : t->height; }
	void LL(AvlNode*& t);
	void RR(AvlNode*& t);
	void LR(AvlNode*& t);
	void RL(AvlNode*& t);
	int max(int a, int b) { return (a > b) ? a : b; }
	//返回false说明子树变矮，否则返回true
	//第一个参数是要检查的节点地址，第二个是0为左子树变矮，1为右子树变矮
	bool adjust(AvlNode*& t, int subTree);	


};