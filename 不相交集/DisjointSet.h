#pragma once
#include <iostream>
using namespace std;
//在.h中定义函数一定要加上inline，否则引用时会出现重定义问题

//按规模并，按路径压缩
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

//在查找过程中改变节点的父节点
inline int DisjointSet::Find(int x)
{
	if (parent[x] < 0) return x;

	parent[x] = Find(parent[x]);
	return parent[x];
}

//必须对根节点进行
//先用Find找到根节点，才能实行Union
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
