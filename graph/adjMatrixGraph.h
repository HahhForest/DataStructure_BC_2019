#pragma once
#include <iostream>
using namespace std;
//邻接矩阵存储图的类定义

template <class Ver, class Edge>
class adjMatrixGraph
{
public:
	void show() {
		cout << noEdge << '\n';
		int i, j;
		for (i = 0; i <= Vers - 1; ++i)
			for (j = 0; j <= Vers - 1; ++j)
				cout << edge[i][j] << '\n';
	}
	adjMatrixGraph(int vSize, const Ver d[], const Edge noEdgeFlag);
	void insert(Ver x, Ver y, Edge w);
	void remove(Ver x, Ver y);
	bool exist(Ver x, Ver y) const;
	~adjMatrixGraph();
	//Floyd算法：求任意两点之间的最短路径
	void floyd() const;

	int numofVer() const { return Vers; }
	int numofEdge() const { return Edges;}

private:
	int Vers;
	int Edges;

	Edge** edge;	//存储邻接矩阵
	Ver* ver;	//存储节点数据
	Edge noEdge;	//表示矩阵中的空值
	int find(Ver v) const {
		for (int i = 0; i <= Vers-1; ++i)	
			if (ver[i] == v) return i;
	}
};