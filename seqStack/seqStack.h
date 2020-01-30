#pragma once
#include <iostream>
using namespace std;

//数组的后端表示栈顶
template <class T>
//class seqStack: public stack <T>
class seqStack
{
private:
	T* elem;
	int Top;
	int maxSize;
	void doubleSpace();

public:
	seqStack(int initSize = 10);
	~seqStack();

	bool isEmpty() const;
	T top() const;
	T pop();
	void push(const T& x);
};