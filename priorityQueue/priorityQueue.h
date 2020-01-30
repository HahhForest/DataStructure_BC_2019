#pragma once
#include <iostream>
using namespace std;

template <class T>
class priorityQueue
{private:
	int currentSize;
	T* array;
	int maxSize;

	void doubleSpace();
	void buildHeap();
	void percolateDown(int hole);

public:
	priorityQueue(int capacity = 100)
	{
		array = new T[capacity];
		maxSize = capacity;
		currentSize = 0;
	}
	priorityQueue(const T data[], int size);
	~priorityQueue() { delete []array; }
	bool isEmpty() const { return currentSize == 0; }
	void enQueue(const T& x);
	T deQueue();
	T getHead() { return array[1]; }
	int find(T prio,int num);
	void decrease(int prio, int dec);
};