#include <iostream>
using namespace std;
#include "adjListGraph.cpp"

int main1()
{
	int i, from, to;

	int n, m, start, M;
	cin >> n >> m >> start >> M;

	int* ver = new int[n];	//节点表初始化
	for ( i = 0; i <= n - 1; ++i)
		ver[i] = i + 1;

	adjListGraph<int, int> graph(n, ver);

	for (i = 0; i <= m - 1; ++i) {
		cin >> from >> to;
		graph.insert(from, to, 1);
	}

	cout << graph.numofEdge() << graph.numofVer() << endl;
	cout<<graph.find(start, M);

	delete[]ver;
	return 0;
}