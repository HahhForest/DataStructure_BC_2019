// seqStack.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;
#include "seqStack.h"
#include "seqStack.cpp"

int main()
{
	seqStack<char> s(5);
	s.push('A');
	s.push('B');

	cout << s.pop();
	cout << s.top();
	cout << s.pop();
	cout << s.isEmpty();

}


