#pragma once
#include <iostream>
using namespace std;

//采用类似数组下标，0为head后的第一个

template <class elemType>
//class linkList: public List <elemType>
class linkList
{
private:
	struct node {//内嵌类
		elemType data;
		node* next;
		node(const elemType& x, node* p = NULL)
		{
			data = x; next = p;
		};
		node() :next(NULL) {};
		~node() {};//两个构造函数
	};
	node* head;

public:
	linkList();
	~linkList() { clear(); delete head; }
	int length() const;
	int search(const elemType& x) const;	//从首节点为0开始，以数组标准返回下标
	elemType visit(int i) const;	//从首节点开始，数组标准
	void insert(int i, const elemType& x);	//从首节点开始，数组标准
	void remove(int i);
	void clear();
	void traverse() const;
	void reverse();
};
