#include "priorityQueue.h"

template<class T>
void priorityQueue<T>::doubleSpace()
{
	maxSize *= 2;
	T *tmp = new T[maxSize];
	for (int i = 1; i <= currentSize; i++)
		tmp[i] = array[i];
	array = tmp;
	delete tmp;
}

template<class T>
void priorityQueue<T>::enQueue(const T& x)
{
	if (currentSize == maxSize - 1) doubleSpace();
	//ÏòÉÏ¹ýÂË
	int hole = ++currentSize;
	for (; hole > 1 && x < array[hole / 2]; hole /= 2)
		array[hole] = array[hole / 2];
	array[hole] = x;
}

template <class T>
T priorityQueue<T>::deQueue()
{
	T minItem;
	minItem = array[1];
	array[1] = array[currentSize--];
	percolateDown(1);
	return minItem;
}

template <class T>
void priorityQueue<T>::percolateDown(int hole)
{
	int child;
	T tmp = array[hole];

	for (; hole*2 <= currentSize; hole = child) {
		child = hole * 2;
		if (child != currentSize && array[child + 1] < array[child]) 
			child++;
		if (array[child] < tmp) array[hole] = array[child];
		else
			break;
	}
	array[hole] = tmp;
}

template<class T>
void priorityQueue<T>::buildHeap()
{
	for (int i = currentSize / 2; i > 0; i--)
		percolateDown(i);
}

template <class T>
priorityQueue<T>::priorityQueue(const T data[], int size):maxSize(size+10),currentSize(size)
{
	array = new T[maxSize];
	for (int i = 0; i < size; i++)
		array[i + 1] = data[i];
	buildHeap();
}

template<class T>
int priorityQueue<T>::find(T prio,int num)
{
	int i = 1;
	for (i = 1; i <= num; i += 1) {
		if (array[i] > prio) break;
	}
	return i;
}

template<class T>
void priorityQueue<T>::decrease(int prio, int dec)
{
	array[prio] -= dec;
	buildHeap();
}