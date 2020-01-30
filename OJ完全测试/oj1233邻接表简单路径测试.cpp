#pragma once
#include <iostream>
using namespace std;

//graph.h
template <class Ver, class Edge>
class graph
{
public:
	graph(int vSize, const Ver d[]);
	~graph();
	void insert(Ver x, Ver y, Edge weight);
	void remove(Ver x, Ver y);
	bool exist(Ver x, Ver y) const;
	void dfs() const;

	int find(Ver start, int m);

	int numofVer() const { return Vers; }
	int numofEdge() const { return Edges; }

private:
	int Vers;
	int Edges;

	//邻接表中存储边的节点类
	struct edgeNode {
		int end;	//另一个端点的编号
		Edge weight;
		edgeNode* next;
		edgeNode(int e, Edge weight, edgeNode* n = NULL) {
			end = e; weight = weight; next = n;
		}
	};
	//节点表中存储的数据类型
	struct verNode {
		Ver ver;
		edgeNode* head;
		verNode(edgeNode* h = NULL) {
			head = h;
		}
	};

	verNode* verList;
	void dfs(int start, bool visited[]) const;

	int find1(Ver verticle) const {
		for (int i = 0; i <= Vers - 1; ++i)
			if (verList[i].ver == verticle)
				return i;
	}
	//find的私有函数（采用递归）
	int find(int start, int m, int& top, bool visited[], int st[], int& total) const;

};

//graph.cpp
//构造函数
template<class Ver, class Edge>
graph<Ver, Edge>::graph(int vSize, const Ver d[])
{
	Vers = vSize; Edges = 0;

	verList = new verNode[vSize];
	for (int i = 0; i <= Vers - 1; ++i)
		verList[i].ver = d[i];
}

//析构函数
template<class Ver, class Edge>
graph<Ver, Edge>::~graph()
{
	int i;
	edgeNode* p;
	for (i = 0; i <= Vers - 1; ++i) {
		while ((p = verList[i].head) != NULL) {
			verList[i].head = p->next;
			delete p;
		}
	}
	delete[]verList;
}

//插入函数：两点一边
template<class Ver, class Edge>
void graph<Ver, Edge>::insert(Ver x, Ver y, Edge weight)
{
	int u = find1(x), verticle = find1(y);
	verList[u].head = new edgeNode(verticle, weight, verList[u].head);
	++Edges;
}

//删除函数：两点
template<class Ver, class Edge>
void graph<Ver, Edge>::remove(Ver x, Ver y)
{
	int u = find1(x), verticle = find1(y);
	edgeNode* p = verList[u].head;
	edgeNode* q;

	if (p == NULL) return;
	if (p->end == verticle) {
		verList[u].head = p->next;
		delete p;
		--Edges;
		return;
	}
	while ((p->next != NULL) && (p->next->end != verticle))
		p = p->next;
	if (p->next != NULL) {
		q = p->next;
		p->next = q->next;
		delete q;
		--Edges;
	}
}

//判断是否存在：两点
template<class Ver, class Edge>
bool graph<Ver, Edge>::exist(Ver x, Ver y) const
{
	int u = find(x), verticle = find(y);
	edgeNode* p = verList[u].head;

	while (p && p->end != verticle)
		p = p->next;

	if (p = NULL) return false;
	else
		return true;
}

//深度优先搜索（公有包装函数）
template<class Ver, class Edge>
void graph<Ver, Edge>::dfs() const
{
	bool* visited = new bool[Vers];
	for (int i = 0; i <= Vers - 1; ++i)
		visited[i] = false;

	cout << "深度优先搜索：" << '\n';

	for (int i = 0; i <= Vers - 1; ++i) {
		if (visited[i] == true)
			continue;
		dfs(i, visited);
		cout << '\n';
	}
}

//深度优先搜索（私有实现，递归）
template<class Ver, class Edge>
void graph<Ver, Edge>::dfs(int start, bool visited[]) const
{
	edgeNode* p = verList[start].head;

	cout << verList[start].ver << '\t';
	visited[start] = true;

	while (p) {
		if (visited[p->end] == false)
			dfs(p->end, visited);
		p = p->next;
	}
}


//公有find函数
template<class Ver, class Edge>
int graph<Ver, Edge>::find(Ver start, int m)
{
	int result = 0, num = 0;

	bool* visited = new bool[Vers];
	int* stack = new int[m + 1], top = 0;	//stack:存储路径信息

	int i;
	for (i = 0; i <= Vers - 1; ++i)
		visited[i] = false;
	for (i = 0; i <= Vers - 1; ++i)
		if (verList[i].ver == start)	break;

	if (i == Vers) {
		cout << "起点不存在" << endl;
		return 0;
	}

	result = find(i, m, top, visited, stack, num);
	result = num;
	return result;
}

//私有find函数（递归）
template<class Ver, class Edge>
int graph<Ver, Edge>::find(int start, int m, int& top, bool visited[], int st[], int& total) const
{
	int i, num = 0;
	edgeNode* p = verList[start].head;
	visited[start] = true;
	st[top++] = start;

	if (top == m + 1) {
		total += 1;
		//cout << endl;
		//for (i = 0; i <= top - 1; ++i)
		//	cout << verList[st[i]].ver << '\t';
		visited[start] = false;
		--top;
		return total;
	}
	while (p != NULL) {
		if (!visited[p->end])
			find(p->end, m, top, visited, st, total);
		p = p->next;
	}
	visited[start] = false;
	--top;
}

int main3()
{
	int i, from, to;

	int n, m, start, M;
	cin >> n >> m >> start >> M;

	int* ver = new int[n];	//节点表初始化
	for (i = 0; i <= n - 1; ++i)
		ver[i] = i + 1;

	graph<int, int> graph(n, ver);

	for (i = 0; i <= m - 1; ++i) {
		cin >> from >> to;
		graph.insert(from, to, 1);
	}

	cout << graph.find(start, M);

	delete[]ver;
	return 0;
}
