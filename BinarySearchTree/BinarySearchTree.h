#pragma once
#include <iostream>
using namespace std;

//公有的成员函数通过调用私有的递归函数完成相应的功能

template <class KEY, class OTHER>
struct SET
{
	KEY key;
	OTHER other;
};

template <class KEY, class OTHER>
class BinarySearchTree
{
private:
	struct BinaryNode {
		SET<KEY, OTHER> data;
		BinaryNode* left;
		BinaryNode* right;

		BinaryNode(const SET<KEY, OTHER>& thedata, BinaryNode* lt = NULL, BinaryNode* rt = NULL)
			:data(thedata), left(lt), right(rt) {}
	};
	BinaryNode* root;

	void insert(const SET<KEY, OTHER>& x, BinaryNode*& t);
	void insert2(const SET<KEY, OTHER>& x, BinaryNode*& t);
	void remove(const KEY& x, BinaryNode*& t);
	SET<KEY, OTHER>* find(const KEY& x, BinaryNode* t) const;
	void makeEmpty(BinaryNode* t);

public:
	BinarySearchTree() :root(NULL) {};
	BinarySearchTree(BinaryNode* p) { root = p; }
	BinarySearchTree(const SET<KEY, OTHER>& set) { root = new BinaryNode(set); }
	~BinarySearchTree() {};
	SET<KEY, OTHER>* find(const KEY& x) const { return find(x, root); };
	void insert(const SET<KEY, OTHER>& x) { insert(x, root); };
	//insert2使用非递归算法
	void insert2(const SET<KEY, OTHER>& x) { insert2(x, root); };
	void remove(const KEY& x) { remove(x, root); };
};