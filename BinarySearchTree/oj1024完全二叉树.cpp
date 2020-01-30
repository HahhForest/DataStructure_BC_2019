#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int height1 = 1, height2 = 1, n;

struct Tree
{
	int ltree;
	int rtree;
};
Tree a[1000000];
void deftree()
{
	for (int i = 0; i <= 99999; i++)
	{
		a[i].ltree = 0;
		a[i].rtree = 0;
	}
}
int  findl(int x)//因为左结点序号小于右结点
{
	for (int i = x; i < a[0].rtree; i++)
	{
		if (a[i].ltree != 0 || a[i].rtree != 0)
			height1 += 1;
	}
	return height1 + 1;
}
int findr(int y)
{
	for (int i = y; i < n; i++)
	{
		if (a[i].ltree != 0 || a[i].rtree != 0)
			height2 += 1;
	}
	return height2 + 1;
}
int cmp(int a, int b)
{
	int c = 0;
	c = (a >= b) ? a : b;
	return c;
}
int mai1n()
{
	deftree();
	int m, num = 1, cnt = 0;
	cin >> n;
	for (int i = 0; i < n - 1; i++)
	{
		cin >> m;
		if (a[m].ltree != 0) a[m].rtree = num++;
		else a[m].ltree = num++;
	}
	int k = log10(n) / log10(2) + 1;

	int maxheight = cmp(findl(a[0].ltree), findr(a[0].rtree));

	for (int i = 0; i < n; i++)
		if (a[i].ltree == 0 && a[i].rtree == 0) cnt += 1;

	
	if (cnt == (n + 1 - pow(2, k - 1)) && maxheight - 1 == k) cout <<"true";
	else cout <<"false";

	return 0;
}
