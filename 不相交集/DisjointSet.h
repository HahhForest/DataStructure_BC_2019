#pragma once
#include <iostream>
using namespace std;
//��.h�ж��庯��һ��Ҫ����inline����������ʱ������ض�������

//����ģ������·��ѹ��
class DisjointSet
{
private:
	int size;
	int* parent;
public:
	DisjointSet(int s);
	~DisjointSet() { delete[]parent; };
	void Union(int root1, int root2);
	int Find(int x);
};

inline DisjointSet::DisjointSet(int s)
{
	size = s;
	parent = new int[size];
	for (int i = 0; i <= size - 1; ++i)
		parent[i] = -1;
}

//�ڲ��ҹ����иı�ڵ�ĸ��ڵ�
inline int DisjointSet::Find(int x)
{
	if (parent[x] < 0) return x;

	parent[x] = Find(parent[x]);
	return parent[x];
}

//����Ը��ڵ����
//����Find�ҵ����ڵ㣬����ʵ��Union
inline void DisjointSet::Union(int root1, int root2)
{
	if (root1 == root2)
		return;
	if (parent[root1] > parent[root2]) {
		parent[root2] += parent[root1];
		parent[root1] = root2;
	}
	else {
		parent[root1] += parent[root2];
		parent[root2] = root1;
	}
}
