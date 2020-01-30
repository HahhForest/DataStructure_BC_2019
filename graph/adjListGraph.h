#pragma once
#include <iostream>
using namespace std;
#include "../linkQueue/linkQueue.cpp"
#include "../priorityQueue/priorityQueue.cpp"
#include "../���ཻ��/DisjointSet.h"

//�ڽӱ�洢ͼ�Ķ���
//�ڽӱ���ͼ�ı�׼�洢��ʽ

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
	//�ҳ���start��ʼ�ĳ���Ϊm�ļ�·�������к�����
	int find(Ver start, int m);
	//Ѱ��ŷ����·���к�������ɵ��ȼ�ƴ��
	void EulerCircuit(Ver start);	
	//��������
	void topSort() const;
	//���ض�һ���ڵ�dfs�Ľ��
	bool* dfs(Ver start);
	//Ѱ�ҹؼ�·��
	void criticalPath() const;
	//����һ������������±�����
	int* topSort2() const;
	//��С��������kruskal�㷨
	void kruskal() const;
	//��С��������prime�㷨
	void prim(Edge noEdge)const;
	//���·�����Ǽ�Ȩͼ��Դ���·��
	void unweightedShortDistance(Ver start, Edge noEdge) const;
	//���·������Ȩͼ��Դ���·����Dijkstra�㷨
	void dijkstra(Ver start, Edge noEdge) const;
	//�Ľ�dijkstra��ʹ����С���ѽ���ʱ�临�Ӷ�
	void dj(Ver start, Ver enD, Edge noEdge);
	//���·������Ȩͼ���޻�ͼ����Դ���·�����Ľ�Dijkstra�㷨
	void dijkstraOfnonecircle(Ver start, Edge noEdge);
	//���·��������Ȩ
	void minusShortDistance(Ver start, Ver end, Edge noEdge);

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
	//��С������kruskal�㷨���ȼ������е�Ԫ������
	struct edge {
		int beg;
		int end;
		Edge w;
		bool operator<(const edge& rp) const {	//���أ���֤Ԫ�������ȼ����к���Խ��бȽϲ���
			return w < rp.w;
		}
	};
	//ŷ��·���ڵ��ࣺ�ڵ��š���һ�ڵ�ָ��
	struct EulerNode {
		int NodeNum;
		EulerNode* next;
		EulerNode(int ver) { NodeNum = ver, next = NULL; }
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

	//��¡����������һ���ڵ��
	verNode* clone() const;
	//ȫ��dfs��˽�к���
	void dfs(int start, bool visited[]) const;
	//ֻ����һ���ڵ��˽�к���
	void dfs(int start, bool* visited, bool*& yes);
	//���ݽڵ����ݷ����ڽڵ���е�λ�õ�find����
	int find(Ver v) const;
	//Ѱ�Ҽ�·��find��˽�к��������õݹ飩
	int find(int start, int m, int& top, bool visited[], int st[], int &total) const;
	//Ѱ��ŷ����·��˽�к���
	EulerNode* EulerCircuit(int start, EulerNode*& end);
	//���·�������·�����ݹ麯��
	void printPath(int start, int end, int prev[])const;
	};
