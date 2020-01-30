#include <iostream>
using namespace std;

#include "linkStack.h"
#include "linkStack.cpp"

int main()
{
	linkStack<char> s1;
	s1.push('A');
	s1.push('B');
	cout<<s1.pop();
	cout<<s1.top();
	cout<<s1.pop();
	cout << s1.isEmpty();
}

