#include "linkStack.h"

template <class T>
linkStack<T>::linkStack()
{
	Top = NULL;
}

template<class T>
linkStack<T>::~linkStack()
{
	node* p;
	while (Top) {
		p = Top;
		Top = Top->next;
		delete p;
	}
}

template <class T>
void linkStack <T>::push(const T& x)
{
	node* p = new node(x, Top);

	p->next = Top;
	Top = p;
}

template <class T>
T linkStack <T>::pop()
{
	node* p = Top;
	T totop = p->data;
	Top = Top->next;
	delete p;
	return totop;
}

template <class T>
T linkStack<T>::top() const
{
	return Top->data;
}

template <class T>
bool linkStack<T>::isEmpty() const
{
	return (Top == NULL);
}
