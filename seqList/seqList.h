#pragma once
#include<iostream>
using namespace std;

class OutOfBound{};
class IllegalSize{};

template <class elemType>
//class seqList: public List<elemType>
class seqList
{
private:
	elemType* data;
	int currentLength;
	int maxSize;
	void doubleSpace();

public:
	seqList(int initSize = 10) {
		data = new elemType[initSize];
		if (!data) throw IllegalSize();
		maxSize = initSize;
		currentLength = 0;
	};
	~seqList() { delete[] data; };
	int length() const;
	int search(const elemType& x) const;
	//if exists return the index, otherwise return -1
	elemType visit(int i) const;	//以数组规则计算
	void insert(int i, const elemType& x);	//插入在以数组规则计算的第i个位置
	void remove(int i);	//以数组规则
	void clear();
	void traverse() const;
	void reverse();
};
