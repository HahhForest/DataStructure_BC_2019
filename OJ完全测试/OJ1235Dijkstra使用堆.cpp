#include <iostream>
using namespace std;
#include <queue>

//堆声明
template <class T>
class priorityQueue
{
private:
	int currentSize;
	T* array;
	int maxSize;

	void doubleSpace();
	void buildHeap();
	void percolateDown(int hole);

public:
	priorityQueue(int capacity = 100000000)
	{
		array = new T[capacity];
		maxSize = capacity;
		currentSize = 0;
	}
	priorityQueue(const T data[], int size);
	~priorityQueue() { delete[]array; }
	bool isEmpty() const { return currentSize == 0; }
	void enQueue(const T& x);
	T deQueue();
	T getHead() { return array[1]; }
	int find(T prio, int num);
	void decrease(int prio, int dec);
};

//堆定义
template<class T>
void priorityQueue<T>::doubleSpace()
{
	maxSize *= 2;
	T* tmp = new T[maxSize];
	for (int i = 1; i <= currentSize; i++)
		tmp[i] = array[i];
	array = tmp;
	delete tmp;
}

template<class T>
void priorityQueue<T>::enQueue(const T& x)
{
	if (currentSize == maxSize - 1) doubleSpace();
	//向上过滤
	int hole = ++currentSize;
	for (; hole > 1 && x < array[hole / 2]; hole /= 2)
		array[hole] = array[hole / 2];
	array[hole] = x;
}

template <class T>
T priorityQueue<T>::deQueue()
{
	T minItem;
	minItem = array[1];
	array[1] = array[currentSize--];
	percolateDown(1);
	return minItem;
}

template <class T>
void priorityQueue<T>::percolateDown(int hole)
{
	int child;
	T tmp = array[hole];

	for (; hole * 2 <= currentSize; hole = child) {
		child = hole * 2;
		if (child != currentSize && array[child + 1] < array[child])
			child++;
		if (array[child] < tmp) array[hole] = array[child];
		else
			break;
	}
	array[hole] = tmp;
}

template<class T>
void priorityQueue<T>::buildHeap()
{
	for (int i = currentSize / 2; i > 0; i--)
		percolateDown(i);
}

template <class T>
priorityQueue<T>::priorityQueue(const T data[], int size) :maxSize(size + 10), currentSize(size)
{
	array = new T[maxSize];
	for (int i = 0; i < size; i++)
		array[i + 1] = data[i];
	buildHeap();
}

template<class T>
int priorityQueue<T>::find(T prio, int num)
{
	int i = 1;
	for (i = 1; i <= num; i += 1) {
		if (array[i] > prio) break;
	}
	return i;
}

template<class T>
void priorityQueue<T>::decrease(int prio, int dec)
{
	array[prio] -= dec;
	buildHeap();
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

	void dj(Ver start, Ver enD, Edge noEdge);
	void dj2(Ver start, Ver enD, Edge noEdge);
	void dijkstra(Ver start, Ver enD, Edge noEdge);

	int numofVer() const { return Vers; }
	int numofEdge() const { return Edges; }

private:
	int Vers;
	int Edges;
	//改良dijkstra算法中放入优先级队列的元素类型
	struct queueNode {
		Edge dist;
		int node;
		bool operator < (const queueNode rp) const {
			return dist < rp.dist;
		}
	};
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

//最短路径：单源加权最短路径：dijkstra算法
//类似最小生成树的prim算法，每次用新加入顶点集的节点更新与之相连的非顶点集中的节点的最短路径
//然后将顶点集与非顶点集间最短路径对应的顶点加入顶点集，重复
//时间复杂度：O(|V|^2+|E|) = O(|V|^2)
template<class Ver, class Edge>
void adjListGraph<Ver, Edge>::dijkstra(Ver start, Ver enD, Edge noEdge)
{
	Edge* distance = new Edge[Vers];	//存储对应的最短路径
	int* prev = new int[Vers];	//存储路径上的上一节点
	bool* known = new bool[Vers];	//存储是否在顶点集中
	int u, sNo, eNo, i, j;
	edgeNode* p;
	Edge min;

	//初始化
	for (i = 0; i <= Vers - 1; ++i) {
		known[i] = false;
		distance[i] = noEdge;
	}
	for (i = 0; i <= Vers - 1; ++i)
		if (verList[i].ver == start)
			break;
	if (i == Vers)
		return;
	sNo = i;

	for (i = 0; i <= Vers - 1; ++i)
		if (verList[i].ver == enD)
			break;
	if (i == Vers)
		return;
	eNo = i;

	distance[sNo] = 0;
	prev[sNo] = sNo;

	//n-1次循环，每次加入一条边
	for (i = 1; i <= Vers - 1; ++i) {	//i只是控制次数，无具体含义
		min = noEdge;

		//在没加入顶点集的定点中寻找最短边
		for (j = 0; j <= Vers - 1; ++j)
			if (!known[j] && distance[j] < min) {	//保证在非顶点集中
				min = distance[j];
				u = j;
			}
		known[u] = true;	//将此下标放入顶点集

		//对新放入顶点集的顶点，更新所有与之相连的点的distance
		for (p = verList[u].head; p != NULL; p = p->next)
			if (!known[p->end] && distance[p->end] > min + p->weight) {
				distance[p->end] = min + p->weight;
				prev[p->end] = u;
			}
	}

	//输出路径

	cout  << distance[eNo] << endl;
	printPath(sNo, eNo, prev);
}

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
	int i, j, u, v;
	for (i = 0; i <= Vers - 1; ++i)
		if (verList[i].ver == x)
			break;
	for (j = 0; j <= Vers - 1; ++j)
		if (verList[j].ver == y)
			break;
	if (i == Vers || j == Vers)
		return;
	u = i;
	v = j;
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

//改进dijkstra：使用堆
//在没加入顶点集的边中寻找最小边时，使用堆排序代替遍历
//可使时间复杂度由O(|V|^2)降低到O(|V|log|V|)
template<class Ver, class Edge>
void adjListGraph<Ver, Edge>::dj(Ver start, Ver enD, Edge noEdge)
{
	Edge* distance = new Edge[Vers];
	int* prev = new int[Vers];
	bool* known = new bool[Vers];
	int sNo, eNo, i;
	edgeNode* p;
	priority_queue<queueNode> q;
	queueNode min, succ;

	//初始化
	for (i = 0; i <= Vers - 1; ++i) {
		known[i] = false;
		distance[i] = noEdge;
	}

	for (sNo = 0; sNo <= Vers - 1; ++sNo)
		if (verList[sNo].ver == start)
			break;
	if (sNo == Vers) 
		return;
	for (eNo = 0; eNo <= Vers - 1; ++eNo)
		if (verList[eNo].ver == enD)
			break;
	if (eNo == Vers)
		return;
	
	distance[sNo] = 0;
	prev[sNo] = sNo;
	min.dist = 0;
	min.node = sNo;
	q.push(min);

	//寻找最短路径
	while (!q.empty()) {
		min = q.top();
		q.pop();
		if (known[min.node] == true)
			continue;

		//将此下标放入顶点集
		known[min.node] = true;

		//对新放入顶点集的顶点，更新所有与之相连的点的distance
		for (p = verList[min.node].head; p != NULL; p = p->next)
			if (!known[p->end] && (distance[p->end] > min.dist + p->weight)) {
				succ.dist = distance[p->end] = min.dist + p->weight;
				prev[p->end] = min.node;
				succ.node = p->end;
				q.push(succ);
			}
	}

	//输出

	cout << distance[eNo]<<'\n';
	printPath(sNo, eNo, prev);
}

//改进dijkstra：使用堆
//在没加入顶点集的边中寻找最小边时，使用堆排序代替遍历
//可使时间复杂度由O(|V|^2)降低到O(|V|log|V|)
template<class Ver, class Edge>
void adjListGraph<Ver, Edge>::dj2(Ver start, Ver enD, Edge noEdge)
{
	Edge* distance = new Edge[Vers];
	int* prev = new int[Vers];
	bool* known = new bool[Vers];
	int sNo, eNo, i;
	edgeNode* p;
	priorityQueue<queueNode> q;
	queueNode min, succ;

	//初始化
	for (i = 0; i <= Vers - 1; ++i) {
		known[i] = false;
		distance[i] = noEdge;
	}

	for (sNo = 0; sNo <= Vers - 1; ++sNo)
		if (verList[sNo].ver == start)
			break;
	if (sNo == Vers)
		return;
	for (eNo = 0; eNo <= Vers - 1; ++eNo)
		if (verList[eNo].ver == enD)
			break;
	if (eNo == Vers)
		return;

	distance[sNo] = 0;
	prev[sNo] = sNo;
	min.dist = 0;
	min.node = sNo;
	q.enQueue(min);

	//寻找最短路径
	while (!q.isEmpty()) {
		min = q.getHead();
		q.deQueue();
		if (known[min.node] == true)
			continue;

		//将此下标放入顶点集
		known[min.node] = true;

		//对新放入顶点集的顶点，更新所有与之相连的点的distance
		for (p = verList[min.node].head; p != NULL; p = p->next)
			if (!known[p->end] && (distance[p->end] > min.dist + p->weight)) {
				succ.dist = distance[p->end] = min.dist + p->weight;
				prev[p->end] = min.node;
				succ.node = p->end;
				q.enQueue(succ);
			}
	}

	//输出

	cout << distance[eNo] << '\n';
	printPath(sNo, eNo, prev);
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

int main11()
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

	g.dj2(start, end, 20191221);

	delete[]v;
	return 0;
}