#pragma once
#include <iostream>
using namespace std;

template <class T>
class linkQueue
{
private:
	struct node {
		T data;
		node* next;
		node(const T& x, node* N = NULL) { data = x; next = N; };
		node() :next(NULL) {};
		~node() {}
	};
	node* front;
	node* rear;

public:
	linkQueue() { front = rear = NULL; };
	~linkQueue();
	bool isEmpty() { return front == NULL; };
	void enQueue(const T& x);
	T deQueue();
	T getHead() { return front->data; };

};