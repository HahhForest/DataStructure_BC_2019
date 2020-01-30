#include "adjListGraph.cpp"


int main5()
{
	int n, m, i, j, biggest;
	int ver1, ver2;
	cin >> n >> m;
	bool* visited = new bool[n];

	//节点表
	int* ver = new int[n];
	for (i = 0; i <= n - 1; ++i)
		ver[i] = i + 1;

	//图初始化
	adjListGraph<int, int> graph(n, ver);
	for (i = 0; i <= m - 1; ++i) {
		cin >> ver1 >> ver2;
		graph.insert(ver1, ver2, 1);
	}

	for (i = 0; i <= n - 1; ++i) {
		visited = graph.dfs(i + 1);
		for(j = n-1; j >= 0;--j)
			if (visited[j] == true) {
				cout << j + 1 << '\t';
				break;
			}
	}

	return 0;
}