#include <iostream>
using namespace std;
#include <queue>

//������
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

//�Ѷ���
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
	//���Ϲ���
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

//ͼ����
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
	//����dijkstra�㷨�з������ȼ����е�Ԫ������
	struct queueNode {
		Edge dist;
		int node;
		bool operator < (const queueNode rp) const {
			return dist < rp.dist;
		}
	};
	//�ڽӱ��д洢�ߵĽڵ���
	struct edgeNode {
		int end;	//��һ���˵�ı��
		Edge weight;
		edgeNode* next;
		edgeNode(int e, Edge w, edgeNode* n = NULL) {
			end = e; weight = w; next = n;
		}
	};
	//�ڵ���д洢����������
	struct verNode {
		Ver ver;
		edgeNode* head;
		verNode(edgeNode* h = NULL) {
			head = h;
		}
	};

	verNode* verList;

	//���ݽڵ����ݷ����ڽڵ���е�λ�õ�find����
	int find(Ver v) const;

	//���·�������·�����ݹ麯��
	void printPath(int start, int end, int prev[])const;
};

//���·������Դ��Ȩ���·����dijkstra�㷨
//������С��������prim�㷨��ÿ�����¼��붥�㼯�Ľڵ������֮�����ķǶ��㼯�еĽڵ�����·��
//Ȼ�󽫶��㼯��Ƕ��㼯�����·����Ӧ�Ķ�����붥�㼯���ظ�
//ʱ�临�Ӷȣ�O(|V|^2+|E|) = O(|V|^2)
template<class Ver, class Edge>
void adjListGraph<Ver, Edge>::dijkstra(Ver start, Ver enD, Edge noEdge)
{
	Edge* distance = new Edge[Vers];	//�洢��Ӧ�����·��
	int* prev = new int[Vers];	//�洢·���ϵ���һ�ڵ�
	bool* known = new bool[Vers];	//�洢�Ƿ��ڶ��㼯��
	int u, sNo, eNo, i, j;
	edgeNode* p;
	Edge min;

	//��ʼ��
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

	//n-1��ѭ����ÿ�μ���һ����
	for (i = 1; i <= Vers - 1; ++i) {	//iֻ�ǿ��ƴ������޾��庬��
		min = noEdge;

		//��û���붥�㼯�Ķ�����Ѱ����̱�
		for (j = 0; j <= Vers - 1; ++j)
			if (!known[j] && distance[j] < min) {	//��֤�ڷǶ��㼯��
				min = distance[j];
				u = j;
			}
		known[u] = true;	//�����±���붥�㼯

		//���·��붥�㼯�Ķ��㣬����������֮�����ĵ��distance
		for (p = verList[u].head; p != NULL; p = p->next)
			if (!known[p->end] && distance[p->end] > min + p->weight) {
				distance[p->end] = min + p->weight;
				prev[p->end] = u;
			}
	}

	//���·��

	cout  << distance[eNo] << endl;
	printPath(sNo, eNo, prev);
}

//ͼ����
//���캯��
template<class Ver, class Edge>
adjListGraph<Ver, Edge>::adjListGraph(int vSize, const Ver d[])
{
	Vers = vSize; Edges = 0;

	verList = new verNode[vSize];
	for (int i = 0; i <= Vers - 1; ++i)
		verList[i].ver = d[i];
}

//��������
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

//���뺯��������һ��
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

//ɾ������������
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

//�ж��Ƿ���ڣ�����
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

//�Ľ�dijkstra��ʹ�ö�
//��û���붥�㼯�ı���Ѱ����С��ʱ��ʹ�ö�����������
//��ʹʱ�临�Ӷ���O(|V|^2)���͵�O(|V|log|V|)
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

	//��ʼ��
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

	//Ѱ�����·��
	while (!q.empty()) {
		min = q.top();
		q.pop();
		if (known[min.node] == true)
			continue;

		//�����±���붥�㼯
		known[min.node] = true;

		//���·��붥�㼯�Ķ��㣬����������֮�����ĵ��distance
		for (p = verList[min.node].head; p != NULL; p = p->next)
			if (!known[p->end] && (distance[p->end] > min.dist + p->weight)) {
				succ.dist = distance[p->end] = min.dist + p->weight;
				prev[p->end] = min.node;
				succ.node = p->end;
				q.push(succ);
			}
	}

	//���

	cout << distance[eNo]<<'\n';
	printPath(sNo, eNo, prev);
}

//�Ľ�dijkstra��ʹ�ö�
//��û���붥�㼯�ı���Ѱ����С��ʱ��ʹ�ö�����������
//��ʹʱ�临�Ӷ���O(|V|^2)���͵�O(|V|log|V|)
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

	//��ʼ��
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

	//Ѱ�����·��
	while (!q.isEmpty()) {
		min = q.getHead();
		q.deQueue();
		if (known[min.node] == true)
			continue;

		//�����±���붥�㼯
		known[min.node] = true;

		//���·��붥�㼯�Ķ��㣬����������֮�����ĵ��distance
		for (p = verList[min.node].head; p != NULL; p = p->next)
			if (!known[p->end] && (distance[p->end] > min.dist + p->weight)) {
				succ.dist = distance[p->end] = min.dist + p->weight;
				prev[p->end] = min.node;
				succ.node = p->end;
				q.enQueue(succ);
			}
	}

	//���

	cout << distance[eNo] << '\n';
	printPath(sNo, eNo, prev);
}

//���ݽڵ����ݷ����ڽڵ���е�λ�õ�find����
template<class Ver, class Edge>
inline int adjListGraph<Ver, Edge>::find(Ver v) const {
	for (int i = 0; i <= Vers - 1; ++i)
		if (verList[i].ver == v)
			return i;
}

//���·��������ݹ����
//·���Ĵ洢������ģ���ÿ���ڵ�ֻ֪����һ�ڵ�
//���ʹ�õݹ��Ϊ����
template<class Ver, class Edge>
void adjListGraph<Ver, Edge>::printPath(int start, int end, int prev[]) const
{
	//�ݹ���ֹ����
	if (start == end) {
		cout << verList[start].ver;
		return;
	}
	//���Լ�����һ������������Լ�֮ǰ��·��
	//Ȼ������Լ�
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