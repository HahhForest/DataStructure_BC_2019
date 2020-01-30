#include <iostream>
using namespace std;
#include "BinaryTree.h"
#include "BinaryTree.cpp"

int main2()
{
	
	/*BinaryTree<char> tree, tree1('M'), tree2;
	tree.createTree('@');

	cout << "高度为：" << tree.height() << endl;
	cout << "规模为：" << tree.size() << endl;
	tree.preOrder2();
	tree.midOrder();
	tree.postOrder();
	cout << endl;

	tree2.makeTree('Y', tree, tree1);
	cout << endl;
	cout << "高度为：" << tree2.height() << endl;
	cout << "规模为：" << tree2.size() << endl;
	tree2.preOrder2();
	tree2.midOrder2();
	tree2.postOrder2();
	return 0;
	*/

	//由层次遍历数组建树
	BinaryTree<char> tree3;
	char levelLst[15] = { '#','Y', 'A', 'M', 'L', 'C', 'W', 'X', 'B', 'E','\0' };
	tree3.buildTreefromlevel(levelLst, 9);
	tree3.preOrder2();
	return 0;
}

