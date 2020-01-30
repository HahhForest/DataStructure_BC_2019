#include "adjListGraph.h"
//�ڽӱ�洢ͼ��ʵ��

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
	int u = find(x), v = find(y);
	verList[u].head = new edgeNode(v, w, verList[u].head);
	++Edges;
}

//ɾ������������
template<class Ver, class Edge>
void adjListGraph<Ver, Edge>::remove(Ver x, Ver y)
{
	int u = find(x), v =  find(y);
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

//����������������а�װ������
template<class Ver, class Edge>
void adjListGraph<Ver, Edge>::dfs() const
{
	bool* visited = new bool[Vers];
	for (int i = 0; i <= Vers - 1; ++i)
		visited[i] = false;

	cout << "�������������" << '\n';

	for (int i = 0; i <= Vers - 1; ++i) {
		if (visited[i] == true)
			continue;
		dfs(i, visited);
		cout << '\n';
	}
}

//�������������˽��ʵ�֣��ݹ飩
template<class Ver, class Edge>
void adjListGraph<Ver, Edge>::dfs(int start, bool visited[]) const
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

//ֻdfs����һ���ڵ�Ĺ��к���
template<class Ver, class Edge>
bool* adjListGraph<Ver, Edge>::dfs(Ver start)
{
	bool* result = new bool[Vers];
	bool* visited = new bool[Vers];
	for (int i = 0; i <= Vers - 1; ++i) {
		visited[i] = false;
		result[i] = false;
	}

	int i = find(start);
	dfs(i, visited, result);
	 
	return result;
}

//ֻdfs����һ���ڵ��˽�к���
template<class Ver, class Edge>
void adjListGraph<Ver, Edge>::dfs(int start, bool* visited, bool*& yes)
{
	edgeNode* p = verList[start].head;
	yes[start] = 1;
	visited[start] = true;

	while (p) {
		if (visited[p->end] == false)
			dfs(p->end, visited, yes);
		p = p->next;
	}
}

//���ݽڵ����ݷ����ڽڵ���е�λ�õ�find����
template<class Ver, class Edge>
inline int adjListGraph<Ver, Edge>::find(Ver v) const {
	for (int i = 0; i <= Vers - 1; ++i)
		if (verList[i].ver == v)
			return i;
}

//�����������������ʵ�֣�ʹ�ö��У�
template<class Ver, class Edge>
void adjListGraph<Ver, Edge>::bfs() const
{
	int test;
	bool* visited = new bool[Vers];
	int currentNode;
	linkQueue<int> q;
	edgeNode* p;
	for (int i = 0; i <= Vers - 1; ++i)
		visited[i] = false;

	cout << "�������������" << '\n';

	for (int i = 0; i <= Vers - 1; ++i) {
		if (visited[i] == true)
			continue;
		q.enQueue(i);

		while (!q.isEmpty()) {
			currentNode = q.deQueue();
			if (visited[currentNode] == true)
				continue;
			cout << verList[currentNode].ver << '\t';
			visited[currentNode] = true;
			p = verList[currentNode].head;
			while (p != NULL) {
				if (visited[p->end] == false) 
					q.enQueue(p->end);
				p = p->next;
				cout << (p == NULL);
			}
		}
		cout << '\n';
	}
}

//����find����
template<class Ver, class Edge>
int adjListGraph<Ver, Edge>::find(Ver start, int m)
{
	int result = 0, num = 0;

	bool* visited = new bool[Vers];
	int* stack = new int[m + 1], top = 0;	//stack:�洢·����Ϣ

	int i;
	for (i = 0; i <= Vers - 1; ++i)
		visited[i] = false;
	for (i = 0; i <= Vers - 1; ++i)
		if (verList[i].ver == start)	break;

	if (i == Vers) {
		cout << "��㲻����" << endl;
		return 0;
	}

	result = find(i, m, top, visited, stack, num);
	result = num;
	return result;
}

//˽��find�������ݹ飩
template<class Ver, class Edge>
int adjListGraph<Ver, Edge>::find(int start, int m, int& top, bool visited[], int st[], int &total) const
{
	int i, num = 0;
	edgeNode* p = verList[start].head;
	visited[start] = true;
	st[top++] = start;

	if (top == m + 1) {
		total += 1;
		cout << endl;
		for (i = 0; i <= top-1; ++i) 
			cout << verList[st[i]].ver << '\t';
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

//����ŷ����·����
template<class Ver, class Edge>
void adjListGraph<Ver, Edge>::EulerCircuit(Ver start)
{
	EulerNode* beg, * end, * p, * q, * tobegin, * toend;
	int numOfDegree;
	edgeNode* r;
	verNode* tmp;
	int i;

	//����Ƿ����ŷ����·
	for (i = 0; i <= Vers - 1; ++i) {
		numOfDegree = 0;
		r = verList[i].head;
		while (r != NULL) {
			++numOfDegree;
			r = r->next;
		}
		//��飺�������еĶȶ���ż����ͼ��ͨ���Ŵ���ŷ����·
		if (numOfDegree == 0 || numOfDegree % 2) {
			cout << "������ŷ����·" << endl;
			return;
		}
	}
	i = find(start);
	tmp = clone();

	//Ѱ�Ҵ�i������·��������յ�ֱ���beg��end
	beg = EulerCircuit(i, end);
	while (true) {
		p = beg;
		while (p->next != NULL)
			if (verList[p->next->NodeNum].head != NULL)
				break;
			else
				p = p->next;
		if (p->next == NULL)	//ȫ���߶��Ѿ����ʹ���
			break;
		q = p->next;
		tobegin = EulerCircuit(q->NodeNum, toend);
		toend->next = q->next;
		p->next = tobegin;
		delete q;
	}
	//������ϣ��ָ�ԭͼ
	delete[]verList;
	verList = tmp;
	
	//��ʾŷ����·
	cout << "ŷ����·��" << endl;
	while (beg != NULL) {
		cout << verList[beg->NodeNum].ver << '\t';
		p = beg;
		beg = beg->next;
		delete p;
	}
	cout << endl;
}

//clone����������һ��һ����verList
template<class Ver, class Edge>
typename adjListGraph<Ver, Edge>::verNode* adjListGraph<Ver, Edge>::clone() const
{
	verNode* tmp = new verNode[Vers];
	edgeNode* p;

	for (int i = 0; i <= Vers - 1; ++i) {
		tmp[i].ver = verList[i].ver;
		p = verList[i].head;
		while (p != NULL) {
			tmp[i].head = new edgeNode(p->end, p->weight, tmp[i].head);
			p = p->next;
		}
	}
	return tmp;
}

//˽�е�ŷ����·����
template<class Ver, class Edge>
typename adjListGraph<Ver , Edge>::EulerNode* adjListGraph<Ver, Edge>::EulerCircuit(int start, EulerNode*& end)
{
	EulerNode* beg;
	int nextNode;
	beg = end = new EulerNode(start);
	while (verList[start].head != NULL) {
		nextNode = verList[start].head->end;

		//ɾ���ߣ���֤�����ظ����ʣ�������clone�ָ�
		remove(start, nextNode);
		remove(nextNode, start);

		start = nextNode;
		end->next = new EulerNode(start);
		end = end->next;
	}
	return beg;
}

//��������
//��������ͼ�����б�A->B����A������B֮ǰ
//ʹ�ö��������ƣ�ÿ���һ���ڵ㣬��ָ��Ľڵ���ȼ�һ
//���Ϊ0�Ľڵ����
template<class Ver, class Edge>
void adjListGraph<Ver, Edge>::topSort() const
{
	int i;
	linkQueue<int> q;
	edgeNode* p;
	int current, * inDegree = new int[Vers];	//���ÿ���ڵ�����

	//��ʼ����ȱ�
	for ( i = 0; i <= Vers - 1; ++i)
		inDegree[i] = 0;
	for ( i = 0; i <= Vers - 1; ++i)
		for (p = verList[i].head; p != NULL; p = p->next)
			++inDegree[p->end];
	
	//���Ϊ0�Ľڵ�����ǰ��
	for ( i = 0; i <= Vers - 1; ++i)
		if (inDegree[i] == 0)
			q.enQueue(i);

	cout << "��������" << endl;
	while (!q.isEmpty()) {
		current = q.deQueue();
		cout << verList[current].ver << '\t';
		for (p = verList[current].head; p != NULL; p = p->next)
			if (--inDegree[p->end] == 0)
				q.enQueue(p->end);
	}
	cout << endl;
}

template <class Ver, class Edge>
int* adjListGraph<Ver, Edge>::topSort2() const
{
	int i;
	int* inDegree = new int[Vers], * top = new int[Vers];
	linkQueue<int> q;
	edgeNode* p;

	//�������
	for (i = 0; i <= Vers - 1; ++i) {
		inDegree[i] = 0;
		for (p = verList[i].head; p != NULL; p = p->next)
			++inDegree[p->end];
	}

	//���Ϊ0�Ľڵ����
	for (i = 0; i <= Vers - 1; ++i)
		if (inDegree[i] == 0)
			q.enQueue(i);

	//���������������
	//ÿ���ڵ����ʱ,����һ�ڵ���ȼ�һ.��Ϊ0,���
	i = 0;
	while (!q.isEmpty()) {
		top[i] = q.deQueue();
		for (p = verList[top[i]].head; p != NULL; p = p->next)
			if (--inDegree[p->end] == 0)
				q.enQueue(p->end);
		++i;
	}
	delete[]inDegree;
	return top;
}

template<class Ver, class Edge>
void adjListGraph<Ver, Edge>::criticalPath() const
{
	//���緢��ʱ�䣺��������������д�ͷ��β�õ�
	//��ٷ���ʱ�䣺��������������д�β��ͷ�õ�
	//����ʱ����ȶ�����ǹؼ�·���ϵĶ���

	//�ֱ�Ϊ���緢��ʱ�䡢������ʱ�䡢����������ȵ�����
	Edge* ee = new Edge[Vers];
	Edge* le = new Edge[Vers];
	int* top;
	int* inDegree = new int[Vers];

	linkQueue<int> q;
	int i;
	edgeNode* p;

	//�ҳ��������У���������top
	top = topSort2();

	//�ҳ����緢��ʱ��
	for (i = 0; i <= Vers - 1; ++i)
		ee[i] = 0;
	for (i = 0; i <= Vers - 1; ++i) {
		for (p = verList[top[i]].head; p != NULL; p = p->next)
			if (ee[p->end] < ee[top[i]] + p->weight)
				ee[p->end] = ee[top[i]] + p->weight;
	}

	//�ҳ�������ʱ��
	for (i = 0; i <= Vers - 1; ++i)
		le[i] = ee[Vers - 1];	//�ȳ�ʼ��Ϊ�����ڵ��������ʱ��
	for (i = Vers - 1; i >= 0; --i)
		for (p = verList[top[i]].head; p != NULL; p = p->next)
			if (le[p->end] - p->weight < le[top[i]])
				le[top[i]] = le[p->end] - p->weight;

	//�ҳ��ؼ�·�����Ƚ�������������ͬ����
	for (i = 0; i <= Vers - 1; ++i)
		if (le[top[i]] == ee[top[i]])
			cout << "(" << verList[top[i]].ver << "," << ee[top[i]] << ")";
}

//��С��������kruskal�㷨
//ÿ�ο��ǻ�·��Ȩֵ��С�ıߣ�ʹ�����ȼ����У���С���ѣ�
//�����벻�ᵼ�»�·������룻��������һ����ʹ�ò��鼯�ж�
//ֱ�����ж���Ϊͬһ��ͨ����
template<class Ver, class Edge>
void adjListGraph<Ver, Edge>::kruskal() const
{
	int edgesAccepted = 0;
	int u, v;
	edgeNode* p;
	edge e;
	DisjointSet ds(Vers);
	priorityQueue<edge> pq;

	//�������ȼ�����
	for (int i = 0; i <= Vers - 1; ++i) {
		for(p = verList[i].head; p != NULL; p = p->next)
			if (i < p->end) {	//����ͼ����֤ÿ����ֻ���һ�ζ����ظ����
				e.beg = i;
				e.end = p->end;
				e.w = p->weight;
				pq.enQueue(e);
			}
	}

	//��ʼ�鲢
	while (edgesAccepted < Vers - 1) {
		e = pq.deQueue();
		u = ds.Find(e.beg);
		v = ds.Find(e.end);
		//cout << u << '\t' << v << endl;
		if (u != v) {
			edgesAccepted++;
			ds.Union(u, v);
			cout << '(' << verList[e.beg].ver << ',' << verList[e.end].ver << ")\t";
		}
	}
}

//��С��������prim�㷨
//�Ӷ����������ʼʱ���㼯Ϊ�գ�������붥��ֱ���������ж���
//ÿ��ѡ�����Ӷ��㼯�����д�����С�ı�
//�����ӵı߼����������ı߼��������ӵĵ���붥�㼯
template<class Ver, class Edge>
void adjListGraph<Ver, Edge>::prim(Edge noEdge) const
{
	bool* flag = new bool[Vers];	//�洢��Щ���ڶ��㼯�У���Щ����
	Edge* lowCost = new Edge[Vers];	//�洢���㼯�еĵ㵽�±�Ԫ�ص���СȨֵ�ıߵ�Ȩֵ
	int* startNode = new int[Vers];	//�洢���±�Ԫ�رߵ�ȨֵΪlowCost�ıߵ�Ȩֵ
	edgeNode* p;
	Edge min;
	int start, i, j;

	//���ݼ���ʼ��
	for (i = 0; i <= Vers - 1; ++i) {	
		flag[i] = false;	//�տ�ʼ�����ڶ��㼯��
		lowCost[i] = noEdge;	//
	}

	start = 0;
	for (i = 1; i <= Vers - 1; ++i) {	//���ƴ���������n-1�Σ��ҳ�n-1����
		for (p = verList[start].head; p != NULL; p = p->next)
			if (!flag[p->end] && lowCost[p->end] > p->weight) {
				lowCost[p->end] = p->weight;
				startNode[p->end] = start;
			}
		flag[start] = true;
		min = noEdge;
		for(j = 0; j <= Vers-1; ++j)
			if (lowCost[j] < min) {
				min = lowCost[j]; 
				start = j;
			}
		cout << '(' << verList[startNode[start]].ver << ',' << verList[start].ver << ")\t";
		lowCost[start] = noEdge;
	}
	delete[]flag;
	delete[]startNode;
	delete[]lowCost;
}

//���·�����Ǽ�Ȩͼ
//ʹ�ö��д洢�¼���Ľڵ㣬�������Ч��
//ʱ�临�Ӷȣ�O(|V|+|E|)
template<class Ver, class Edge>
void adjListGraph<Ver, Edge>::unweightedShortDistance(Ver start, Edge noEdge) const
{
	linkQueue<int> q;
	Edge* distance = new Edge[Vers];	//�洢ÿ���ڵ���start�����·��(�����)
	int* prev = new int[Vers];	//�洢��һ�ڵ�
	int u, sNo;
	edgeNode* p;
	int i;

	//��ʼ��
	for (i = 0; i <= Vers - 1; ++i)
		distance[i] = noEdge;
	sNo = find(start);

	//Ѱ�����·��
	distance[sNo] = 0;
	prev[sNo] = sNo;
	q.enQueue(sNo);
	while (!q.isEmpty()) {
		u = q.deQueue();
		for(p = verList[u].head; p != NULL; p = p->next)
			if (distance[p->end] == noEdge) {	//��δ��������
				distance[p->end] = distance[u] + 1;
				prev[p->end] = u;
				q.enQueue(p->end);
			}
	}

	//������·��
	for (i = 0; i <= Vers - 1; ++i) {
		cout << "�� " << start << " �� " << verList[i].ver << " ��·��Ϊ��" << endl;
		printPath(sNo, i, prev);
		cout << endl;
	}
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
	cout << "-->" << verList[end].ver;
}

//���·������Դ��Ȩ���·����dijkstra�㷨
//������С��������prim�㷨��ÿ�����¼��붥�㼯�Ľڵ������֮�����ķǶ��㼯�еĽڵ�����·��
//Ȼ�󽫶��㼯��Ƕ��㼯�����·����Ӧ�Ķ�����붥�㼯���ظ�
//ʱ�临�Ӷȣ�O(|V|^2+|E|) = O(|V|^2)
template<class Ver, class Edge>
void adjListGraph<Ver, Edge>::dijkstra(Ver start, Edge noEdge) const
{
	Edge* distance = new Edge[Vers];	//�洢��Ӧ�����·��
	int* prev = new int[Vers];	//�洢·���ϵ���һ�ڵ�
	bool* known = new bool[Vers];	//�洢�Ƿ��ڶ��㼯��
	int u, sNo, i, j;
	edgeNode* p;
	Edge min;

	//��ʼ��
	for (i = 0; i <= Vers - 1; ++i) {
		known[i] = false;
		distance[i] = noEdge;
	}
	sNo = find(start);
	distance[sNo] = 0;
	prev[sNo] = sNo;

	//n-1��ѭ����ÿ�μ���һ����
	for (i = 1; i <= Vers - 1; ++i) {	//iֻ�ǿ��ƴ������޾��庬��
		min = noEdge;

		//��û���붥�㼯�Ķ�����Ѱ����̱�
		for(j = 0; j <=Vers-1; ++j)
			if (!known[j] && distance[j] < min) {	//��֤�ڷǶ��㼯��
				min = distance[j];
				u = j;
			}
		known[u] = true;	//�����±���붥�㼯

		//���·��붥�㼯�Ķ��㣬����������֮�����ĵ��distance
		for(p = verList[u].head; p != NULL; p = p->next)
			if (!known[p->end] && distance[p->end] > min + p->weight) {
				distance[p->end] = min + p->weight;
				prev[p->end] = u;
			}
	}

	//���·��
	for (i = 0; i <= Vers - 1; ++i) {
		cout << "�� " << start << " �� " << verList[i].ver << " ��·��Ϊ��" << endl;
		printPath(sNo, i, prev);
		cout << "\t����Ϊ��" << distance[i] << endl;
	}
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
	int sNo,eNo, i;
	edgeNode* p;
	priorityQueue<queueNode> q;
	queueNode min, succ;

	//��ʼ��
	for (i = 0; i <= Vers-1; ++i) {
		known[i] = false;
		distance[i] = noEdge;
	}
	for (sNo = 0; sNo <= Vers - 1; ++sNo)
		if (verList[sNo].ver == start)
			break;
	if (sNo == Vers) {
		cout << "��ʼ�ڵ㲻���ڣ�" << endl;
		return;
	}
	distance[sNo] = 0;
	prev[sNo] = sNo;
	min.dist = 0;
	min.node = sNo;
	q.enQueue(min);

	//Ѱ�����·��
	while (!q.isEmpty()) {
		min = q.deQueue();
		if (known[min.node] == true)
			continue;

		//�����±���붥�㼯
		known[min.node] = true;

		//���·��붥�㼯�Ķ��㣬����������֮�����ĵ��distance
		for(p = verList[min.node].head; p != NULL; p = p->next)
			if (!known[p->end] && (distance[p->end] > min.dist + p->weight)) {
				succ.dist = distance[p->end] = min.dist + p->weight;
				prev[p->end] = min.node;
				succ.node = p->end;
				q.enQueue(succ);
			}
	}

	//���
	eNo = find(enD);
	
	cout << "�� " << start << " ��" << enD << " ��·��Ϊ��" << endl;
	printPath(sNo, eNo, prev);
	cout << "\t����Ϊ��" << distance[eNo] << endl;
	
}

//���·������Դ��Ȩ���޻�ͼ���·�����Ľ�dijkstra�㷨
//������С��������prim�㷨��ÿ�����¼��붥�㼯�Ľڵ������֮�����ķǶ��㼯�еĽڵ�����·��
//Ȼ�󽫶��㼯��Ƕ��㼯�����·����Ӧ�Ķ�����붥�㼯���ظ�
//�Ľ���ʹ����������Ĵ���ѡ��ڵ�
//ʱ�临�Ӷȣ�O(|V|^2)�Ľ���O(|V|+|E|)

//���ڻ��Ǵ���ģ�������������
template<class Ver, class Edge>
void adjListGraph<Ver, Edge>::dijkstraOfnonecircle(Ver start, Edge noEdge)
{
	Edge* distance = new Edge[Vers];	//�洢��Ӧ�����·��
	int* prev = new int[Vers];	//�洢·���ϵ���һ�ڵ�
	bool* known = new bool[Vers];	//�洢�Ƿ��ڶ��㼯��
	int u, sNo, i, j, k = 0, set = 0;
	edgeNode* p;
	Edge min;

	//��ʼ��
	for (i = 0; i <= Vers - 1; ++i) {
		known[i] = false;
		distance[i] = noEdge;
	}
	sNo = find(start);
	distance[sNo] = 0;
	prev[sNo] = sNo;

	//n-1��ѭ����ÿ�μ���һ����
	for (i = 1; i <= Vers - 1; ++i) {	//iֻ�ǿ��ƴ������޾��庬��
		min = noEdge;

		//��û���붥�㼯�Ķ�����Ѱ����̱�
		for (j = 0; j <= set + k ; ++j)
			if (!known[j] && distance[j] < min) {	//��֤�ڷǶ��㼯��
				min = distance[j];
				u = j;
			}
		known[u] = true;	//�����±���붥�㼯

		k = 0;
		//���·��붥�㼯�Ķ��㣬����������֮�����ĵ��distance
		for (p = verList[u].head; p != NULL; p = p->next) {
			if (!known[p->end] && distance[p->end] > min + p->weight) {
				distance[p->end] = min + p->weight;
				prev[p->end] = u;
			}
			k += 1;
		}
		set += 1;
	}

	//���·��
	for (i = 0; i <= Vers - 1; ++i) {
		cout << "�� " << start << " �� " << verList[i].ver << " ��·��Ϊ��" << endl;
		printPath(sNo, i, prev);
		cout << "\t����Ϊ��" << distance[i] << endl;
	}
}

//���·��������Ȩ
//��Ҫ����̽ڵ㣬����һ������
//���ڳ��ӵĽڵ�v�����������ڽӵ�w����start����v��w�ľ���С��ֱ�ӵ�w�ģ������w�ľ��룬����w���
template<class Ver, class Edge>
void adjListGraph<Ver, Edge>::minusShortDistance(Ver start, Ver end, Edge noEdge)
{
	Edge* distance = new Edge[Vers];
	int* prev = new int[Vers];
	int u, sNo, eNo, i;
	edgeNode* p;
	linkQueue<int> q;

	//��ʼ��
	sNo = find(start);
	eNo = find(end);

	for (i = 0; i <= Vers - 1; ++i)
		distance[i] = noEdge;
	distance[sNo] = 0;
	prev[sNo] = sNo;
	q.enQueue(sNo);

	//��ʼ
	while (!q.isEmpty()) {
		u = q.deQueue();
		for(p = verList[u].head; p != NULL; p = p->next)
			if (distance[p->end] > distance[u] + p->weight) {
				distance[p->end] = distance[u] + p->weight;
				prev[p->end] = u;
				q.enQueue(p->end);
			}
	}

	//���
	cout << "�� " << start << " ��" << end << " ��·��Ϊ��" << endl;
	printPath(sNo, eNo, prev);
	cout << "\t����Ϊ��" << distance[eNo] << endl;
}

/*
template<class Ver, class Edge>
void adjListGraph<Ver, Edge>::dfsOj1233(Ver start) const
{
	int startnum, j = 0, total = 0;
	for(int i = 0; i <= Vers-1; ++i)
		if (verList[i] == start) {
			startnum = i;
			break;
		}

	bool* visited = new bool[Vers];
	int currentNode;
	linkStack<int> s;
	edgeNode* p;

	for (int i = 0; i <= Vers - 1; ++i)
		visited[i] = false;
	s.push(startnum);
	while (!s.isEmpty()) {
		currentNode = s.pop();
		if (visited[currentNode] == true)
			continue;
		if (j == 2) {
			j = 0;
			total += 1;
			break;
		}
		cout << verList[currentNode] << '\t';
		visited[currentNode] = true;
	}


}
*/