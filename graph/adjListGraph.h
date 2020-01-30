#pragma once
#include <iostream>
using namespace std;
#include "../linkQueue/linkQueue.cpp"
#include "../priorityQueue/priorityQueue.cpp"
#include "../不相交集/DisjointSet.h"

//邻接表存储图的定义
//邻接表是图的标准存储方式

template <class Ver, class Edge>
class adjListGraph
{

public:
	adjListGraph(int vSize, const Ver d[]);
	~adjListGraph();
	void insert(Ver x, Ver y, Edge w);
	void remove(Ver x, Ver y);
	bool exist(Ver x, Ver y) const;
	void dfs() const;
	void bfs() const;
//	void dfsOj1233(Ver start) const;
	//找出从start开始的长度为m的简单路径（公有函数）
	int find(Ver start, int m);
	//寻找欧拉回路公有函数，完成调度及拼接
	void EulerCircuit(Ver start);	
	//拓扑排序
	void topSort() const;
	//返回对一个节点dfs的结果
	bool* dfs(Ver start);
	//寻找关键路径
	void criticalPath() const;
	//返回一个拓扑排序的下标数组
	int* topSort2() const;
	//最小生成树：kruskal算法
	void kruskal() const;
	//最小生成树：prime算法
	void prim(Edge noEdge)const;
	//最短路径：非加权图单源最短路径
	void unweightedShortDistance(Ver start, Edge noEdge) const;
	//最短路径：加权图单源最短路径：Dijkstra算法
	void dijkstra(Ver start, Edge noEdge) const;
	//改进dijkstra：使用最小化堆降低时间复杂度
	void dj(Ver start, Ver enD, Edge noEdge);
	//最短路径：加权图，无环图，单源最短路径：改进Dijkstra算法
	void dijkstraOfnonecircle(Ver start, Edge noEdge);
	//最短路径：带负权
	void minusShortDistance(Ver start, Ver end, Edge noEdge);

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
	//最小生成树kruskal算法优先级队列中的元素类型
	struct edge {
		int beg;
		int end;
		Edge w;
		bool operator<(const edge& rp) const {	//重载：保证元素入优先级队列后可以进行比较操作
			return w < rp.w;
		}
	};
	//欧拉路径节点类：节点编号、下一节点指针
	struct EulerNode {
		int NodeNum;
		EulerNode* next;
		EulerNode(int ver) { NodeNum = ver, next = NULL; }
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

	//克隆函数：返回一个节点表
	verNode* clone() const;
	//全部dfs的私有函数
	void dfs(int start, bool visited[]) const;
	//只遍历一个节点的私有函数
	void dfs(int start, bool* visited, bool*& yes);
	//根据节点数据返回在节点表中的位置的find函数
	int find(Ver v) const;
	//寻找简单路径find的私有函数（采用递归）
	int find(int start, int m, int& top, bool visited[], int st[], int &total) const;
	//寻找欧拉回路的私有函数
	EulerNode* EulerCircuit(int start, EulerNode*& end);
	//最短路径中输出路径：递归函数
	void printPath(int start, int end, int prev[])const;
	};
