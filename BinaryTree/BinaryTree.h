#pragma once
#include <iostream>
using namespace std;
#include "linkQueue.h"
#include "linkQueue.cpp"
#include "linkStack.h"
#include "linkStack.cpp"
//height���������ڵ�

template <class T>
class BinaryTree
{
private:
	struct node {
		node* left;
		node* right;
		T data;
		node() :left(NULL), right(NULL) {};
		node(T item, node* L = NULL, node* R = NULL) :data(item), left(L), right(R) {};
		~node() {};
	};

	struct stnode	//���򼰺���������Ҫ��¼�ǵڼ��γ�ջ
	{
		node* Node;
		int popTimes;
		stnode(node* n = NULL) :Node(n), popTimes(0) {};
		~stnode() {};
	};

	node* root;
	void clear(node* t);
	int height(node* t) const;
	int size(node* t) const;
	void preOrder(node* t) const;
	void postOrder(node* t) const;
	void midOrder(node* t) const;

public:


	BinaryTree() :root(NULL) {}	//����һ�ÿն�����
	BinaryTree(const T &value) { root = new node(value); }
	BinaryTree(node* p) { root = p; }
	~BinaryTree() { clear(); }
	T getRoot() const { return root->data; }
	T getLeft() const { return root->left->data; }
	T getRight() const { return root->right->data; }
	void makeTree(const T &x, BinaryTree &lt, BinaryTree &rt)
	{
		root = new node(x, lt.root, rt.root);
		lt.root = NULL; rt.root = NULL;
	}
	void delLeft()
	{
		BinaryTree tmp = root->left;
		root->left = NULL;
		tmp.clear();
	}
	void delRight()
	{
		BinaryTree tmp = root->right;
		root->right = NULL;
		tmp.clear();
	}
	bool isEmpty() const { return root == NULL; }
	void clear(){ if (root) clear(root); root = NULL; }
	int size()const { return size(root); }
	int height() const { return height(root); }
	void preOrder() const
	{
		if (root) {
			cout << "\nǰ�������"; preOrder(root);
		}
	}
	void postOrder() const
	{
		if (root) {
			cout << "\n���������"; postOrder(root);
		}
	}
	void midOrder() const
	{
		if (root) {
			cout << "\n���������"; midOrder(root);
		}
	}
	void createTree(T flag);

	//����Ϊ����ջʵ�ֵķǵݹ��㷨
	void preOrder2() const;

	void midOrder2() const;

	void postOrder2() const;

	//���ö���ʵ���ɲ�α������齨����
	//
	void buildTreefromlevel(T levelList[], int n);
	//��ǰ�������������齨��
	node* buildTreefrompreandmid(T pre[], int pl, int pr, T mid[], int ml, int mr)
	{
		if (pl > pr) return NULL;
		node* p; p = new node(pre[pl]);
		int pos, i = pl;

		for (i = pl; i <= pr; i++)
			if (mid[i] == pre[pl]) break;

		pos = i;
		p->left = buildTreefrompreandmid(pre, pl + 1, pl + pos - ml, mid, ml, pos - 1);
		p->right = buildTreefrompreandmid(pre, pl + pos - ml + 1, pr, mid, pos + 1, mr);

		return p;
	}
};

