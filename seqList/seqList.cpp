#include"seqList.h"

//template <class elemType>
//seqList<elemType>::seqList(int initSize)
////注意帽子与胡子


template<class elemType>
void seqList<elemType>::doubleSpace()
{
	elemType* tmp = data;
	data= new elemType[maxSize * 2];

	if (!data) throw IllegalSize();

	for (int j = 0; j < currentLength; ++j)
		data[j] = tmp[j];

	delete[]tmp;
	maxSize = maxSize * 2;
}

//length函数
template<class elemType>
int seqList<elemType>::length() const
{
	return currentLength;
}

//search函数
template<class elemType>
int seqList<elemType>::search(const elemType& x) const
{
	int i = 0;
	for (; i < currentLength; i++)
		if (data[i] == x) break;

	if (i == currentLength) return -1;
	else return i;
}

//visit函数
template<class elemType>
elemType seqList<elemType>::visit(int i) const
{
	return data[i];
}

template<class elemType>
void seqList<elemType>::insert(int i, const elemType& x)
{
	int j = 0;
	if ((currentLength < i) || (i < 0)) return;
	if (currentLength == maxSize)
		doubleSpace();
	for (j = currentLength; j > i; j -= 1)
		data[j] = data[j - 1];
	data[i] = x;
	currentLength++;
}

template<class elemType>
void seqList<elemType>::remove(int i)
{
	if ((i < 0) || (i > currentLength - 1)) throw OutOfBound();

	for (int j = i; j < currentLength; j++)
		data[j] = data[j + 1];

	currentLength -= 1;
}

template<class elemType>
void seqList<elemType>::clear()
{
	delete data;
	maxSize = 0;
	currentLength = 0;
}

template<class elemType>
void seqList<elemType>::reverse()
{
	int i, j;
	elemType* tmp = new elemType[maxSize];
	for (i = 0, j = maxSize - 1; i <= maxSize - 1; i += 1, j -= 1)
	{
		tmp[i] = data[j];
	}
	data = tmp;
}

template<class elemType>
void seqList<elemType>::traverse() const
{
	int i = 0;
	for (i = 0; i < currentLength; i += 1)cout << data[i] << ' ';
	cout << endl;
}
