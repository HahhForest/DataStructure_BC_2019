#include "seqQueue.h"

template <class T>
void seqQueue<T>::doubleSpace()
{
	int i;

	T* tmp = elem;
	elem = new T[2 * maxSize];
	for (i = 1; i < maxSize; ++i)
		elem[i] = tmp[(front + i) % maxSize];

	front = 0;
	rear = maxSize - 1;
	maxSize *= 2;
	delete tmp;
}

template <class T>
void seqQueue<T>::enQueue(const T& x)
{
	if ((rear + 1) % maxSize == front)
		doubleSpace();
	rear = (rear + 1) % maxSize;
	elem[rear] = x;
}

template <class T>
T seqQueue<T>::deQueue()
{
	front = (front + 1) % maxSize;
	return elem[front];
}
