#include "linkList.h"

template <class elemType>
linkList<elemType>::linkList()
{
	head = new node();
}

template <class elemType>
int linkList<elemType>::length() const
{
	int len = 0;
	node* p = head->next;
	while (p != NULL)
	{
		len += 1;
		p = p->next;
	}
	return len;
}

template<class elemType>
int linkList<elemType>::search(const elemType& x) const
{
	int num = -1;
	node* p = head->next;
	while (p != NULL)
	{
		num += 1;
		if (x == p->data)return num;
	}
	if (p == NULL) num = -1;
	return num;
}

template<class elemType>
void linkList<elemType>::insert(int i, const elemType& x)
{
	if (i < 0) return;
	node* tmp;
	node* p = head;
	for (int j = 0; p && j < i; j += 1) p = p->next;
	if (!p) return;
	tmp = new node(x, p -> next);
	p->next = tmp;
}

template<class elemType>
void linkList<elemType>::remove(int i)
{
	if (i < 0) return;
	node* tmp, * p = head;
	for (int j = 0; p && j < i; ++j) 
		p = p->next;
	if (!p || !p->next) return;
	tmp = p->next;
	p->next = tmp->next;
	delete tmp;
}

template <class elemType>
void linkList<elemType>::clear()
{
	node* p = head->next;
	node* q;
	while (p != NULL)
	{
		q = p;
		p = p->next;
		delete q;
	}
	head->next = NULL;
}

template <class elemType>
elemType linkList<elemType>::visit(int i) const
{
	node* p = head;
	int j = 0;
	for (j = 0; j <= i; j += 1)
		p = p->next;

	return p->data;
}

template <class elemType>
void linkList<elemType>::reverse()
{
	node* p, * q;
	p = head->next;
	head->next = NULL;

	while (p)
	{
		q = p->next;
		p->next = head->next;
		head->next = p;
		p = q;
	}
}

template <class elemType>
void linkList<elemType>::traverse() const
{
	node* p = head->next;
	cout << endl;
	while (p)
	{
		cout << p->data << "    ";
		p = p->next;
	}
	cout << endl;
}
