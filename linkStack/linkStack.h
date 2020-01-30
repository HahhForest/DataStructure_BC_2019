#pragma once
#include <iostream>
using namespace std;

template <class T>
//class linkStack: public Stack<T>
class linkStack
{
private:
	struct node {
		T data;
		node* next;
		node(const T& x, node* N = NULL) { data = x; next = N; }
		node() :next(NULL) {};
		~node() {};
	};

	node* Top;

public:
	linkStack();
	~linkStack();

	bool isEmpty() const;
	T top() const;
	T pop();
	void push(const T& x);
};
