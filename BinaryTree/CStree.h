#pragma once
#include <iostream>
using namespace std;

//º¢×ÓĞÖµÜÁ´±íÊ¾Ê÷

template<class T>
class CStree
{
private:
	struct csnode
	{
		T data;
		csnode* child;
		csnode* nextsibling;
		csnode() :child(NULL), nextsibling(NULL) {};
		csnode(T item, csnode* c = NULL, csnode* n = NULL) :
			data(item), child(c), nextsibling(n) {};
		~csnode() {};
	};

	csnode* root;
	
public:
	CStree() :root(NULL) {}
	CStree(const T& value) { root = new csnode(value); }
	CStree(csnode* p) { root = p; }
	~CStree() { clear(); }

	T getRoot() const { return root->data; }
	T getLeft() const { return root->left->data; }
	void clear();
};