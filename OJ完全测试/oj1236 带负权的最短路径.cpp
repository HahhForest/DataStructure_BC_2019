#include <iostream>
using namespace std;

//linkQueue
template <class T>
class linkQueue
{
private:
	struct node {
		T data;
		node* next;
		node(const T& x, node* N = NULL) { data = x; next = N; };
		node() :next(NULL) {};
		~node() {}
	};
	node* front;
	node* rear;

public:
	linkQueue() { front = rear = NULL; };
	~linkQueue();
	bool isEmpty() { return front == NULL; };
	void enQueue(const T& x);
	T deQueue();
	T getHead() { return front->data; };

};

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

//图声明
template <class Ver, class Edge>
class adjListGraph
{

public:
	adjListGraph(int vSize, const Ver d[]);
	~adjListGraph();
	void insert(Ver x, Ver y, Edge w);
	void remove(Ver x, Ver y);
	bool exist(Ver x, Ver y) const;
	//最短路径：带负权
	void minusShortDistance(Ver start, Ver end, Edge noEdge);

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
		edgeNode(int e, Edge w, edgeNode* n = NULL) {
			end = e; weight = w; next = n;
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

	//根据节点数据返回在节点表中的位置的find函数
	int find(Ver v) const;

	//最短路径中输出路径：递归函数
	void printPath(int start, int end, int prev[])const;
};



//图定义
//构造函数
template<class Ver, class Edge>
adjListGraph<Ver, Edge>::adjListGraph(int vSize, const Ver d[])
{
	Vers = vSize; Edges = 0;

	verList = new verNode[vSize];
	for (int i = 0; i <= Vers - 1; ++i)
		verList[i].ver = d[i];
}

//析构函数
template<class Ver, class Edge>
adjListGraph<Ver, Edge>::~adjListGraph()
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
void adjListGraph<Ver, Edge>::insert(Ver x, Ver y, Edge w)
{
	int u = find(x), v = find(y);
	verList[u].head = new edgeNode(v, w, verList[u].head);
	++Edges;
}

//删除函数：两点
template<class Ver, class Edge>
void adjListGraph<Ver, Edge>::remove(Ver x, Ver y)
{
	int u = find(x), v = find(y);
	edgeNode* p = verList[u].head;
	edgeNode* q;

	if (p == NULL) return;
	if (p->end == v) {
		verList[u].head = p->next;
		delete p;
		--Edges;
		return;
	}
	while ((p->next != NULL) && (p->next->end != v))
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
bool adjListGraph<Ver, Edge>::exist(Ver x, Ver y) const
{
	int u = find(x), v = find(y);
	edgeNode* p = verList[u].head;

	while (p && p->end != v)
		p = p->next;

	if (p = NULL) return false;
	else
		return true;
}

//根据节点数据返回在节点表中的位置的find函数
template<class Ver, class Edge>
inline int adjListGraph<Ver, Edge>::find(Ver v) const {
	for (int i = 0; i <= Vers - 1; ++i)
		if (verList[i].ver == v)
			return i;
}

//最短路径输出：递归调用
//路径的存储是逆向的，即每个节点只知其上一节点
//因此使用递归较为方便
template<class Ver, class Edge>
void adjListGraph<Ver, Edge>::printPath(int start, int end, int prev[]) const
{
	//递归终止条件
	if (start == end) {
		cout << verList[start].ver;
		return;
	}
	//对自己的上一级调用输出在自己之前的路径
	//然后输出自己
	printPath(start, prev[end], prev);
	cout << " " << verList[end].ver;
}

//最短路径：带负权
//需要检查后继节点，利用一个队列
//对于出队的节点v，对其所有邻接点w，若start经过v到w的距离小于直接到w的，则更新w的距离，并将w入队
template<class Ver, class Edge>
void adjListGraph<Ver, Edge>::minusShortDistance(Ver start, Ver end, Edge noEdge)
{
	Edge* distance = new Edge[Vers];
	int* prev = new int[Vers];
	int u, sNo, eNo, i;
	edgeNode* p;
	linkQueue<int> q;

	//初始化
	for (i = 0; i <= Vers - 1; ++i)
		if (verList[i].ver = start)
			break;
	if (i == Vers)
		return;
	sNo = i;
	for (i = 0; i <= Vers - 1; ++i)
		if (verList[i].ver = end)
			break;
	if (i == Vers)
		return;
	eNo = i;

	for (i = 0; i <= Vers - 1; ++i)
		distance[i] = noEdge;
	distance[sNo] = 0;
	prev[sNo] = sNo;
	q.enQueue(sNo);

	//开始
	while (!q.isEmpty()) {
		u = q.deQueue();
		for (p = verList[u].head; p != NULL; p = p->next)
			if (distance[p->end] > distance[u] + p->weight) {
				distance[p->end] = distance[u] + p->weight;
				prev[p->end] = u;
				q.enQueue(p->end);
			}
	}

	//输出
	cout<< distance[eNo] << endl;
}

int main10()
{
	int i, j;
	int n, m, start, end;
	int v1, v2, weight;
	cin >> n >> m >> start >> end;
	int* v = new int[n];
	for (i = 0; i <= n - 1; ++i)
		v[i] = i + 1;
	adjListGraph<int, int> g(n, v);
	for (i = 0; i <= m - 1; ++i) {
		cin >> v1 >> v2 >> weight;
		g.insert(v1, v2, weight);
	}

	g.minusShortDistance(start, end, 99999999999);

	delete[]v;
	return 0;
}