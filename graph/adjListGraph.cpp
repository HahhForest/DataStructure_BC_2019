#include "adjListGraph.h"
//邻接表存储图的实现

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

//深度优先搜索（公有包装函数）
template<class Ver, class Edge>
void adjListGraph<Ver, Edge>::dfs() const
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

//只dfs遍历一个节点的公有函数
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

//只dfs遍历一个节点的私有函数
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

//根据节点数据返回在节点表中的位置的find函数
template<class Ver, class Edge>
inline int adjListGraph<Ver, Edge>::find(Ver v) const {
	for (int i = 0; i <= Vers - 1; ++i)
		if (verList[i].ver == v)
			return i;
}

//广度优先搜索（公有实现，使用队列）
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

	cout << "广度优先搜索：" << '\n';

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

//公有find函数
template<class Ver, class Edge>
int adjListGraph<Ver, Edge>::find(Ver start, int m)
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

//公有欧拉回路函数
template<class Ver, class Edge>
void adjListGraph<Ver, Edge>::EulerCircuit(Ver start)
{
	EulerNode* beg, * end, * p, * q, * tobegin, * toend;
	int numOfDegree;
	edgeNode* r;
	verNode* tmp;
	int i;

	//检查是否存在欧拉回路
	for (i = 0; i <= Vers - 1; ++i) {
		numOfDegree = 0;
		r = verList[i].head;
		while (r != NULL) {
			++numOfDegree;
			r = r->next;
		}
		//检查：必须所有的度都是偶数且图连通，才存在欧拉回路
		if (numOfDegree == 0 || numOfDegree % 2) {
			cout << "不存在欧拉回路" << endl;
			return;
		}
	}
	i = find(start);
	tmp = clone();

	//寻找从i出发的路径，起点终点分别是beg，end
	beg = EulerCircuit(i, end);
	while (true) {
		p = beg;
		while (p->next != NULL)
			if (verList[p->next->NodeNum].head != NULL)
				break;
			else
				p = p->next;
		if (p->next == NULL)	//全部边都已经访问过了
			break;
		q = p->next;
		tobegin = EulerCircuit(q->NodeNum, toend);
		toend->next = q->next;
		p->next = tobegin;
		delete q;
	}
	//访问完毕，恢复原图
	delete[]verList;
	verList = tmp;
	
	//显示欧拉回路
	cout << "欧拉回路：" << endl;
	while (beg != NULL) {
		cout << verList[beg->NodeNum].ver << '\t';
		p = beg;
		beg = beg->next;
		delete p;
	}
	cout << endl;
}

//clone函数，返回一份一样的verList
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

//私有的欧拉回路函数
template<class Ver, class Edge>
typename adjListGraph<Ver , Edge>::EulerNode* adjListGraph<Ver, Edge>::EulerCircuit(int start, EulerNode*& end)
{
	EulerNode* beg;
	int nextNode;
	beg = end = new EulerNode(start);
	while (verList[start].head != NULL) {
		nextNode = verList[start].head->end;

		//删除边，保证不会重复访问，后面用clone恢复
		remove(start, nextNode);
		remove(nextNode, start);

		start = nextNode;
		end->next = new EulerNode(start);
		end = end->next;
	}
	return beg;
}

//拓扑排序
//对于有向图，若有边A->B，则A必须在B之前
//使用队列来控制，每输出一个节点，它指向的节点入度减一
//入度为0的节点进队
template<class Ver, class Edge>
void adjListGraph<Ver, Edge>::topSort() const
{
	int i;
	linkQueue<int> q;
	edgeNode* p;
	int current, * inDegree = new int[Vers];	//存放每个节点的入度

	//初始化入度表
	for ( i = 0; i <= Vers - 1; ++i)
		inDegree[i] = 0;
	for ( i = 0; i <= Vers - 1; ++i)
		for (p = verList[i].head; p != NULL; p = p->next)
			++inDegree[p->end];
	
	//入度为0的节点在最前面
	for ( i = 0; i <= Vers - 1; ++i)
		if (inDegree[i] == 0)
			q.enQueue(i);

	cout << "拓扑排序：" << endl;
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

	//计算入度
	for (i = 0; i <= Vers - 1; ++i) {
		inDegree[i] = 0;
		for (p = verList[i].head; p != NULL; p = p->next)
			++inDegree[p->end];
	}

	//入度为0的节点入队
	for (i = 0; i <= Vers - 1; ++i)
		if (inDegree[i] == 0)
			q.enQueue(i);

	//填充拓扑排序数组
	//每个节点出队时,其下一节点入度减一.若为0,入队
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
	//最早发生时间：由拓扑排序的序列从头到尾得到
	//最迟发生时间：由拓扑排序的序列从尾到头得到
	//两个时间相等顶点就是关键路径上的顶点

	//分别为最早发生时间、最晚发生时间、拓扑排序、入度的数组
	Edge* ee = new Edge[Vers];
	Edge* le = new Edge[Vers];
	int* top;
	int* inDegree = new int[Vers];

	linkQueue<int> q;
	int i;
	edgeNode* p;

	//找出拓扑序列，放入数组top
	top = topSort2();

	//找出最早发生时间
	for (i = 0; i <= Vers - 1; ++i)
		ee[i] = 0;
	for (i = 0; i <= Vers - 1; ++i) {
		for (p = verList[top[i]].head; p != NULL; p = p->next)
			if (ee[p->end] < ee[top[i]] + p->weight)
				ee[p->end] = ee[top[i]] + p->weight;
	}

	//找出最晚发生时间
	for (i = 0; i <= Vers - 1; ++i)
		le[i] = ee[Vers - 1];	//先初始化为结束节点的最晚发生时间
	for (i = Vers - 1; i >= 0; --i)
		for (p = verList[top[i]].head; p != NULL; p = p->next)
			if (le[p->end] - p->weight < le[top[i]])
				le[top[i]] = le[p->end] - p->weight;

	//找出关键路径：比较最晚与最早相同即可
	for (i = 0; i <= Vers - 1; ++i)
		if (le[top[i]] == ee[top[i]])
			cout << "(" << verList[top[i]].ver << "," << ee[top[i]] << ")";
}

//最小生成树：kruskal算法
//每次考虑回路中权值最小的边：使用优先级队列（最小化堆）
//若加入不会导致回路，则加入；否则考虑下一条：使用并查集判断
//直到所有顶点为同一连通分量
template<class Ver, class Edge>
void adjListGraph<Ver, Edge>::kruskal() const
{
	int edgesAccepted = 0;
	int u, v;
	edgeNode* p;
	edge e;
	DisjointSet ds(Vers);
	priorityQueue<edge> pq;

	//生成优先级队列
	for (int i = 0; i <= Vers - 1; ++i) {
		for(p = verList[i].head; p != NULL; p = p->next)
			if (i < p->end) {	//无向图，保证每条边只添加一次而不重复添加
				e.beg = i;
				e.end = p->end;
				e.w = p->weight;
				pq.enQueue(e);
			}
	}

	//开始归并
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

//最小生成树：prim算法
//从顶点出发，初始时顶点集为空，逐个加入顶点直至包含所有顶点
//每次选择连接顶点集与其差集中代价最小的边
//将连接的边加入生成树的边集，新连接的点加入顶点集
template<class Ver, class Edge>
void adjListGraph<Ver, Edge>::prim(Edge noEdge) const
{
	bool* flag = new bool[Vers];	//存储哪些点在顶点集中，哪些不在
	Edge* lowCost = new Edge[Vers];	//存储顶点集中的点到下标元素的最小权值的边的权值
	int* startNode = new int[Vers];	//存储至下标元素边的权值为lowCost的边的权值
	edgeNode* p;
	Edge min;
	int start, i, j;

	//数据集初始化
	for (i = 0; i <= Vers - 1; ++i) {	
		flag[i] = false;	//刚开始都不在顶点集中
		lowCost[i] = noEdge;	//
	}

	start = 0;
	for (i = 1; i <= Vers - 1; ++i) {	//控制次数，进行n-1次，找出n-1条边
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

//最短路径：非加权图
//使用队列存储新加入的节点，可以提高效率
//时间复杂度：O(|V|+|E|)
template<class Ver, class Edge>
void adjListGraph<Ver, Edge>::unweightedShortDistance(Ver start, Edge noEdge) const
{
	linkQueue<int> q;
	Edge* distance = new Edge[Vers];	//存储每个节点至start的最短路径(即层次)
	int* prev = new int[Vers];	//存储上一节点
	int u, sNo;
	edgeNode* p;
	int i;

	//初始化
	for (i = 0; i <= Vers - 1; ++i)
		distance[i] = noEdge;
	sNo = find(start);

	//寻找最短路径
	distance[sNo] = 0;
	prev[sNo] = sNo;
	q.enQueue(sNo);
	while (!q.isEmpty()) {
		u = q.deQueue();
		for(p = verList[u].head; p != NULL; p = p->next)
			if (distance[p->end] == noEdge) {	//还未被遍历过
				distance[p->end] = distance[u] + 1;
				prev[p->end] = u;
				q.enQueue(p->end);
			}
	}

	//输出最短路径
	for (i = 0; i <= Vers - 1; ++i) {
		cout << "从 " << start << " 到 " << verList[i].ver << " 的路径为：" << endl;
		printPath(sNo, i, prev);
		cout << endl;
	}
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
	cout << "-->" << verList[end].ver;
}

//最短路径：单源加权最短路径：dijkstra算法
//类似最小生成树的prim算法，每次用新加入顶点集的节点更新与之相连的非顶点集中的节点的最短路径
//然后将顶点集与非顶点集间最短路径对应的顶点加入顶点集，重复
//时间复杂度：O(|V|^2+|E|) = O(|V|^2)
template<class Ver, class Edge>
void adjListGraph<Ver, Edge>::dijkstra(Ver start, Edge noEdge) const
{
	Edge* distance = new Edge[Vers];	//存储对应的最短路径
	int* prev = new int[Vers];	//存储路径上的上一节点
	bool* known = new bool[Vers];	//存储是否在顶点集中
	int u, sNo, i, j;
	edgeNode* p;
	Edge min;

	//初始化
	for (i = 0; i <= Vers - 1; ++i) {
		known[i] = false;
		distance[i] = noEdge;
	}
	sNo = find(start);
	distance[sNo] = 0;
	prev[sNo] = sNo;

	//n-1次循环，每次加入一条边
	for (i = 1; i <= Vers - 1; ++i) {	//i只是控制次数，无具体含义
		min = noEdge;

		//在没加入顶点集的定点中寻找最短边
		for(j = 0; j <=Vers-1; ++j)
			if (!known[j] && distance[j] < min) {	//保证在非顶点集中
				min = distance[j];
				u = j;
			}
		known[u] = true;	//将此下标放入顶点集

		//对新放入顶点集的顶点，更新所有与之相连的点的distance
		for(p = verList[u].head; p != NULL; p = p->next)
			if (!known[p->end] && distance[p->end] > min + p->weight) {
				distance[p->end] = min + p->weight;
				prev[p->end] = u;
			}
	}

	//输出路径
	for (i = 0; i <= Vers - 1; ++i) {
		cout << "从 " << start << " 到 " << verList[i].ver << " 的路径为：" << endl;
		printPath(sNo, i, prev);
		cout << "\t长度为：" << distance[i] << endl;
	}
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
	int sNo,eNo, i;
	edgeNode* p;
	priorityQueue<queueNode> q;
	queueNode min, succ;

	//初始化
	for (i = 0; i <= Vers-1; ++i) {
		known[i] = false;
		distance[i] = noEdge;
	}
	for (sNo = 0; sNo <= Vers - 1; ++sNo)
		if (verList[sNo].ver == start)
			break;
	if (sNo == Vers) {
		cout << "起始节点不存在！" << endl;
		return;
	}
	distance[sNo] = 0;
	prev[sNo] = sNo;
	min.dist = 0;
	min.node = sNo;
	q.enQueue(min);

	//寻找最短路径
	while (!q.isEmpty()) {
		min = q.deQueue();
		if (known[min.node] == true)
			continue;

		//将此下标放入顶点集
		known[min.node] = true;

		//对新放入顶点集的顶点，更新所有与之相连的点的distance
		for(p = verList[min.node].head; p != NULL; p = p->next)
			if (!known[p->end] && (distance[p->end] > min.dist + p->weight)) {
				succ.dist = distance[p->end] = min.dist + p->weight;
				prev[p->end] = min.node;
				succ.node = p->end;
				q.enQueue(succ);
			}
	}

	//输出
	eNo = find(enD);
	
	cout << "从 " << start << " 到" << enD << " 的路径为：" << endl;
	printPath(sNo, eNo, prev);
	cout << "\t长度为：" << distance[eNo] << endl;
	
}

//最短路径：单源加权，无环图最短路径：改进dijkstra算法
//类似最小生成树的prim算法，每次用新加入顶点集的节点更新与之相连的非顶点集中的节点的最短路径
//然后将顶点集与非顶点集间最短路径对应的顶点加入顶点集，重复
//改进：使用拓扑排序的次序选择节点
//时间复杂度：O(|V|^2)改进至O(|V|+|E|)

//现在还是错误的，待修正！！！
template<class Ver, class Edge>
void adjListGraph<Ver, Edge>::dijkstraOfnonecircle(Ver start, Edge noEdge)
{
	Edge* distance = new Edge[Vers];	//存储对应的最短路径
	int* prev = new int[Vers];	//存储路径上的上一节点
	bool* known = new bool[Vers];	//存储是否在顶点集中
	int u, sNo, i, j, k = 0, set = 0;
	edgeNode* p;
	Edge min;

	//初始化
	for (i = 0; i <= Vers - 1; ++i) {
		known[i] = false;
		distance[i] = noEdge;
	}
	sNo = find(start);
	distance[sNo] = 0;
	prev[sNo] = sNo;

	//n-1次循环，每次加入一条边
	for (i = 1; i <= Vers - 1; ++i) {	//i只是控制次数，无具体含义
		min = noEdge;

		//在没加入顶点集的定点中寻找最短边
		for (j = 0; j <= set + k ; ++j)
			if (!known[j] && distance[j] < min) {	//保证在非顶点集中
				min = distance[j];
				u = j;
			}
		known[u] = true;	//将此下标放入顶点集

		k = 0;
		//对新放入顶点集的顶点，更新所有与之相连的点的distance
		for (p = verList[u].head; p != NULL; p = p->next) {
			if (!known[p->end] && distance[p->end] > min + p->weight) {
				distance[p->end] = min + p->weight;
				prev[p->end] = u;
			}
			k += 1;
		}
		set += 1;
	}

	//输出路径
	for (i = 0; i <= Vers - 1; ++i) {
		cout << "从 " << start << " 到 " << verList[i].ver << " 的路径为：" << endl;
		printPath(sNo, i, prev);
		cout << "\t长度为：" << distance[i] << endl;
	}
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
	sNo = find(start);
	eNo = find(end);

	for (i = 0; i <= Vers - 1; ++i)
		distance[i] = noEdge;
	distance[sNo] = 0;
	prev[sNo] = sNo;
	q.enQueue(sNo);

	//开始
	while (!q.isEmpty()) {
		u = q.deQueue();
		for(p = verList[u].head; p != NULL; p = p->next)
			if (distance[p->end] > distance[u] + p->weight) {
				distance[p->end] = distance[u] + p->weight;
				prev[p->end] = u;
				q.enQueue(p->end);
			}
	}

	//输出
	cout << "从 " << start << " 到" << end << " 的路径为：" << endl;
	printPath(sNo, eNo, prev);
	cout << "\t长度为：" << distance[eNo] << endl;
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