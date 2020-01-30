#include <iostream>
using namespace std;
#include "BinarySearchTree.h"
#include "BinarySearchTree.cpp"

int main()
{
	char a[] = "aaa", b[] = "bbb";
	SET<int, char*> c[] = { {10,a},{8,b} };
	cout << "!!!";
	BinarySearchTree<int, char*> tree;
	SET<int, char*> x;
	SET<int, char*>* p;

	for (int i = 0; i <= 1; i++) tree.insert(c[i]);
	cout << (tree.find(10))->other;
	return 0;
}

