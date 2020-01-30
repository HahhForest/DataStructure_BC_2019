#include <iostream>
using namespace std;
#include "../linkQueue/linkQueue.cpp"

//方向
static const int direcX[4] = { 0, -1, 0, 1 }, direcY[4] = { 1, 0, -1, 0 };

//节点类，存储坐标
struct Node {
	int X, Y;
};

bool canConnect(int x, int y, bool**visited, int **graph, int h, int weight)
{
	if (x < 0 || y < 0 || x >= h || y >= weight)
		return false;

	if (visited[x][y] != false || graph[x][y] == -1)
		return false;

	return true;
}

//广度遍历：将对应坐标可以连通的节点都标记为已访问
void bfs(int x, int y, bool** visited, int **graph, int height, int width)
{
	Node n, top, toEnque;
	n.X = x; n.Y = y;
	linkQueue<Node> q;
	int newX, newY;

	visited[x][y] = true;
	q.enQueue(n);

	while (!q.isEmpty()) {
		top = q.deQueue();
		//visited[top.X][top.Y] = true;
		for (int i = 0; i <= 3; ++i) {
			newX = top.X + direcX[i], newY = top.Y + direcY[i];
			if (canConnect(newX, newY, visited, graph, height, width)) {
				toEnque.X = newX, toEnque.Y = newY;
				q.enQueue(toEnque);
				visited[newX][newY] = true;
			}
		}
	}
}

int main7()
{
	int i, j, cnt = 0;
	int n, m;
	linkQueue<Node> q;

	cin >> n >> m;

	//存储图、存储已访问
	int** graph = new int*[n];
	bool** visited = new bool* [n];

	for (i = 0; i <= n - 1; ++i) {
		graph[i] = new int[m];
		visited[i] = new bool[m];
	}

	//输入图
	for (i = 0; i <= n - 1; ++i)
		for (j = 0; j <= m - 1; ++j)
			cin >> graph[i][j];

	//访问矩阵初始化
	for (i = 0; i <= n - 1; ++i)
		for (j = 0; j <= m - 1; ++j)
			visited[i][j] = false;

	for(i = 0; i <= n-1; ++i)
		for(j = 0; j <= m-1; ++j)
			if (graph[i][j] == 0 && visited[i][j] == false) {
				++cnt;
				bfs(i, j, visited, graph, n, m);
			}

	cout << cnt;
	return 0;
}