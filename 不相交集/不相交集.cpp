#include <iostream>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include "DisjointSet.h"

void createPuzzle(int size) //size为迷宫的规模
{
	int num1, num2;
	DisjointSet ds(size * size);
	srand(time(0));
	while (ds.Find(0) != ds.Find(size * size - 1)) {
		while (true) { //选择两个相邻的不连通单元
			num1 = rand() * size * size / (RAND_MAX + 1);
			num2 = num1 - size;  //检查上方的单元
			if (num2 >= 0) if (ds.Find(num1) != ds.Find(num2)) break;
			num2 = num1 - 1;    //检查左边的单元
			if (num1 % size != 0)   if (ds.Find(num1) != ds.Find(num2)) break;
			num2 = num1 + size;    //检查下方的单元
			if (num2 < size * size)   if (ds.Find(num1) != ds.Find(num2)) break;
			num2 = num1 + 1;  //检查右边的单元
			if (num2 % size != 0) if (ds.Find(num1) != ds.Find(num2)) break;
		}
		ds.Union(ds.Find(num1), ds.Find(num2));
		cout << '<' << num1 << ',' << num2 << ">, ";
	}
}



int main()
{
	//createPuzzle(10);
    cout << "Hello World!\n";
}
