
#include <iostream>
using namespace std;

#include "linkList.h"
#include "linkList.cpp"


int main()
{
	linkList<char> l;
	l.insert(0, 'A');
	l.insert(1, 'B');
	cout<<l.visit(0);
	cout<<l.visit(1)<<endl;
	cout<<l.search('A');
	l.remove(0);
	l.traverse();
	cout << l.visit(0);
	l.clear();
	l.traverse();

}

