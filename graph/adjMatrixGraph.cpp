#include <iostream>
#include "adjMatrixGraph.h"
//邻接矩阵存储图的类实现

//构造函数
template <class Ver, class Edge>
adjMatrixGraph<Ver, Edge>::adjMatrixGraph(int vSize, const Ver d[], Edge noEdgeflag)
{
	int i, j;
	Vers = vSize;
	Edges = 0;
	noEdge = noEdgeflag;

	//初始化存放节点的数组
	ver = new Ver[vSize];
	for (i = 0; i <= vSize - 1; ++i)
		ver[i] = d[i];

	//初始化邻接矩阵
	edge = new Edge * [vSize];
	for (i = 0; i <= vSize - 1; ++i) {
		edge[i] = new Edge[vSize];
		for (j = 0; j <= vSize - 1; ++j) {
			edge[i][j] = noEdge;
			cout << edge[i][j] << endl;
		}
	}
}

//析构函数
template<class Ver, class Edge>
adjMatrixGraph<Ver, Edge>::~adjMatrixGraph()
{
	delete[]ver;

	for (int i = 0; i <= Vers-1; ++i)
		delete[]edge[i];
	delete[]edge;
}


//插入函数:;两点一边
template<class Ver, class Edge>
void adjMatrixGraph<Ver, Edge>::insert(Ver x, Ver y, Edge w)
{
	int u = find(x), v = find(y);
	edge[u][v] = w;
	++Edges;
}

//删除函数:两点
template<class Ver, class Edge>
void adjMatrixGraph<Ver, Edge>::remove(Ver x, Ver y)
{
	int u = find(x), v = find(y);
	edge[u][v] = noEdge;
	--Edges;
}

//判断是否存在:两点
template <class Ver, class Edge>
bool adjMatrixGraph<Ver, Edge>::exist(Ver x, Ver y) const
{
	int u = find(x), v = find(y);
	if (edge[u][v] == noEdge)
		return false;
	else return true;
}

//最短路径：求任意两点间最短路径：Floyd算法
//依次将所有节点作为中间节点，看看从起始节点到终止节点的距离是否大于在中间节点中转的距离
//若中转更短，则替换
template<class Ver, class Edge>
void adjMatrixGraph<Ver, Edge>::floyd() const
{
	//初始化
	Edge** d = new Edge * [Vers];	//存储路径长度
	int** prev = new int* [Vers];	//存储中间节点的下标
	int i, j, k;
	for (i = 0; i <= Vers - 1; ++i) {
		d[i] = new Edge[Vers];
		prev[i] = new int[Vers];
		for (j = 0; j <= Vers - 1; ++j) {
			d[i][j] = edge[i][j];
			prev[i][j] = (edge[i][j] != noEdge) ? i: -1;
		}
	}

	//迭代过程
	for(k = 0; k <= Vers-1; ++k)
		for(i = 0; i <= Vers-1; ++i)
			for(j = 0; j <= Vers-1; ++j)
				if (d[i][k] + d[k][j] < d[i][j]) {
					d[i][j] = d[i][k] + d[k][j];
					prev[i][j] = prev[k][j];
				}

	//输出过程
	cout << "最短路径长度：" << endl;
	for (i = 0; i <= Vers - 1; ++i) {
		cout << endl;
		for (j = 0; j <= Vers - 1; ++j)
			cout << d[i][j] << '\t';
	}

	cout << "最短路径：" << endl;
	for (i = 0; i <= Vers - 1; ++i) {
		cout << endl;
		for (j = 0; j <= Vers - 1; ++j)
			cout << prev[i][j] << '\t';
	}
}