#pragma once
#include <iostream>
using namespace std;

template <class T>
class seqQueue
{
private:
	T* elem;
	int maxSize;
	int front;
	int rear;
	void doubleSpace();

public:
	seqQueue(int size = 10)
	{
		elem = new T[size];
		maxSize = size;
		front = rear = 0;
	};
	~seqQueue() { delete[]elem; };
	bool isEmpty() { return front == rear; };
	void enQueue(const T& x);
	T deQueue();
	T getHead() { return elem[(front + 1) % maxSize]; };
};