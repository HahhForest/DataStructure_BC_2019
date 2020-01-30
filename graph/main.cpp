#include <iostream>
using namespace std;
#include "adjMatrixGraph.cpp"
#include "adjListGraph.cpp"

void testM()
{
	char ver[5] = { 'A','B','C','D','E' };
	adjMatrixGraph<char, int> testgraph(5, ver, 999);
	//testgraph.show();
	testgraph.insert('A', 'B', 1);
	testgraph.insert('A', 'C', 1);
	testgraph.insert('A', 'D', 1);
	testgraph.insert('A', 'E', 1);
	testgraph.insert('D', 'B', 1);
	testgraph.insert('E', 'C', 1);
	cout << testgraph.exist('E', 'A');
	testgraph.show();

	testgraph.remove('C', 'A');
	cout << testgraph.exist('A', 'C');
}

void testL()
{
	char ver[7] = { 'A','B','C','D','E','F','G' };
	adjListGraph<char, int> testgraph(7, ver);
	testgraph.insert('E', 'F', 1);
	testgraph.insert('E', 'G', 1);
	testgraph.insert('G', 'F', 1);
	testgraph.insert('F', 'B', 1);
	testgraph.insert('G', 'D', 1);
	testgraph.insert('B', 'D', 1);
	testgraph.insert('B', 'C', 1);
	testgraph.insert('D', 'A', 1);
	testgraph.insert('A', 'B', 1);
	testgraph.insert('D', 'C', 1);
	testgraph.insert('C', 'A', 1);
	//cout << testgraph.numofEdge();
	//cout << testgraph.numofVer()<<'\n';
	//testgraph.topSort();
	//testgraph.EulerCircuit('A');
	testgraph.criticalPath();
	cout << "!";
	//testgraph.bfs();

}

void testkruskal()
{
	int verticles[6] = { 1,2,3,4,5,6 };
	adjListGraph<int, int> graph(6, verticles);
	graph.insert(1, 2, 6);
	graph.insert(1, 3, 1);
	graph.insert(1, 4, 5);
	graph.insert(2, 3, 5);
	graph.insert(3, 4, 5);
	graph.insert(2, 5, 3);
	graph.insert(3, 5, 6);
	graph.insert(3, 6, 4);
	graph.insert(4, 6, 2);
	graph.insert(5, 6, 6);
	cout << "Vers = " << graph.numofVer() << "Edges = " << graph.numofEdge() << endl;
	graph.kruskal();
}

void testprim()
{
	int verticles[6] = { 1,2,3,4,5,6 };
	adjListGraph<int, int> graph(6, verticles);
	graph.insert(1, 2, 6);
	graph.insert(1, 3, 1);
	graph.insert(1, 4, 5);
	graph.insert(2, 3, 5);
	graph.insert(3, 4, 5);
	graph.insert(2, 5, 3);
	graph.insert(3, 5, 6);
	graph.insert(3, 6, 4);
	graph.insert(4, 6, 2);
	graph.insert(5, 6, 6);

	graph.insert(2, 1, 6);
	graph.insert(3, 1, 1);
	graph.insert(4, 1, 5);
	graph.insert(3, 2, 5);
	graph.insert(4, 3, 5);
	graph.insert(5, 2, 3);
	graph.insert(5, 3, 6);
	graph.insert(6, 3, 4);
	graph.insert(6, 4, 2);
	graph.insert(6, 5, 6);
	cout << "Vers = " << graph.numofVer() << "Edges = " << graph.numofEdge() << endl;
	graph.prim(100);
}

void testunweighted()
{
	int verticles[7] = { 0,1,2,3,4,5,6 };
	adjListGraph<int, int> graph(7, verticles);
	graph.insert(2, 0, 1);
	graph.insert(2, 5, 1);
	graph.insert(3, 2, 1);
	graph.insert(0, 3, 1);
	graph.insert(3, 5, 1);
	graph.insert(0, 1, 1);
	graph.insert(6, 5, 1);
	graph.insert(1, 3, 1);
	graph.insert(3, 6, 1);
	graph.insert(3, 4, 1);
	graph.insert(1, 4, 1);
	graph.insert(4, 6, 1);
	cout << "Vers = " << graph.numofVer() << "Edges = " << graph.numofEdge() << endl;
	graph.unweightedShortDistance(2, 99);
}
void testdijkstra()
{
	int verticles[7] = { 0,1,2,3,4,5,6 };
	adjListGraph<int, int> graph(7, verticles);
	graph.insert(2, 0, 1);
	graph.insert(2, 5, 1);
	graph.insert(3, 2, 1);
	graph.insert(0, 3, 1);
	graph.insert(3, 5, 1);
	graph.insert(0, 1, 1);
	graph.insert(6, 5, 1);
	graph.insert(1, 3, 1);
	graph.insert(3, 6, 1);
	graph.insert(3, 4, 1);
	graph.insert(1, 4, 1);
	graph.insert(4, 6, 1);
	cout << "Vers = " << graph.numofVer() << "Edges = " << graph.numofEdge() << endl;
	graph.dijkstra(2, 99);
}

void testdij2()
{
	int verticles[7] = { 0,1,2,3,4,5,6 };
	adjListGraph<int, int> graph(7, verticles);
	graph.insert(2, 0, 4);
	graph.insert(2, 5, 3);
	graph.insert(5, 6, 1);
	graph.insert(0, 1, 2);
	graph.insert(0, 3, 1);
	graph.insert(1, 3, 3);
	graph.insert(1, 4, 10);
	graph.insert(3, 6, 4);
	graph.insert(4, 6, 6);
	graph.insert(3, 4, 2);
	cout << "Vers = " << graph.numofVer() << "Edges = " << graph.numofEdge() << endl;
	graph.topSort();
	graph.dijkstraOfnonecircle(2, 99);
}

void testfloyd()
{
	int v[3] = { 0, 1, 2};
	adjMatrixGraph<int, int> graph(3, v, 999);
	graph.insert(0, 1, 8);
	graph.insert(1, 0, 4);
	graph.insert(0, 2, 5);
	graph.insert(2, 1, 2);
	cout << graph.numofVer() << '\t' << graph.numofEdge() << endl;
	graph.floyd();
}

void testdji2()
{
	int v[7] = { 1,2,3,4,5,6,7 };
	adjListGraph<int, int> graph(7, v);
	graph.insert(1, 2, 2);
	graph.insert(3, 1, 4);
	graph.insert(1,4,1);
	graph.insert(2, 4, 3);
	graph.insert(4,5,2);
	graph.insert(2, 5, 10);
	graph.insert(3, 6, 5);
	graph.insert(4, 6, 8);
	graph.insert(4, 7, 4);
	graph.insert(5, 7, 6);
	graph.insert(7, 6, 1);
	graph.insert(4, 3, 2);
	cout << graph.numofVer() << '\t' << graph.numofEdge() << endl;
	graph.dj(4, 6, 20180820);
}

void testminus()
{
	int v[7] = { 1,2,3,4,5,6,7 };
	adjListGraph<int, int> graph(7, v);
	graph.insert(1, 2, 2);
	graph.insert(3, 1, 4);
	graph.insert(1, 4, 1);
	graph.insert(2, 4, 3);
	graph.insert(4, 5, 2);
	graph.insert(2, 5, 10);
	graph.insert(3, 6, 3);
	graph.insert(4, 6, -8);
	graph.insert(4, 7, 4);
	graph.insert(5, 7, 6);
	graph.insert(7, 6, 1);
	graph.insert(1, 3, 5);
	cout << graph.numofVer() << '\t' << graph.numofEdge() << endl;
	graph.minusShortDistance(3, 6, 20180820);
}

int main()
{
	testminus();
	return 0;
}