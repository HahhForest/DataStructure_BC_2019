#include "linkQueue.h"

template <class T>
linkQueue<T>::~linkQueue()
{
	node* tmp;
	while (front)
	{
		tmp = front;
		front = front->next;
		delete tmp;
	}
}

template <class T>
void linkQueue<T>::enQueue(const T& x)
{
	if (rear == NULL)
		front = rear = new node(x);
	else
	{
		rear->next = new node(x);
		rear = rear->next;
	}
}

template <class T>
T linkQueue<T>::deQueue()
{
	node* tmp = front;
	T value = front->data;
	front = front->next;
	if (front == NULL)  //如果出队的是最后一个节点，出队后队为空
		rear = NULL;
	delete tmp;
	return value;
}
