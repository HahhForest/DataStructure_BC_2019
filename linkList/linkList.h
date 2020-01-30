#pragma once
#include <iostream>
using namespace std;

//�������������±꣬0Ϊhead��ĵ�һ��

template <class elemType>
//class linkList: public List <elemType>
class linkList
{
private:
	struct node {//��Ƕ��
		elemType data;
		node* next;
		node(const elemType& x, node* p = NULL)
		{
			data = x; next = p;
		};
		node() :next(NULL) {};
		~node() {};//�������캯��
	};
	node* head;

public:
	linkList();
	~linkList() { clear(); delete head; }
	int length() const;
	int search(const elemType& x) const;	//���׽ڵ�Ϊ0��ʼ���������׼�����±�
	elemType visit(int i) const;	//���׽ڵ㿪ʼ�������׼
	void insert(int i, const elemType& x);	//���׽ڵ㿪ʼ�������׼
	void remove(int i);
	void clear();
	void traverse() const;
	void reverse();
};
