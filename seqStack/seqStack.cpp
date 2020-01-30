#include "seqStack.h"

template <class T>
seqStack<T>::seqStack(int initSize)
{
	elem = new T[initSize];
	maxSize = initSize;
	Top = -1;
}

template<class T>
seqStack<T>::~seqStack()
{
	delete[]elem;
}

template <class T>
bool seqStack<T>::isEmpty() const
{
	return Top == -1;
}

template<class T>
T seqStack<T>::top() const
{
	return elem[Top];
}

template<class T>
T seqStack<T>::pop()
{
	T tmp = elem[Top];
	Top -= 1;
	return tmp;
}

template<class T>
void seqStack<T>::push(const T& x)
{
	if (Top == maxSize - 1) doubleSpace();
	Top += 1;
	elem[Top] = x;
}

template <class T>
void seqStack<T>::doubleSpace()
{
	int i = 0;
	T* tmp = elem;
	elem = new T[2 * maxSize];
	for (i = 0; i <= maxSize - 1; i += 1)
		elem[i] = tmp[i];
	maxSize *= 2;
	delete[]tmp;
}

