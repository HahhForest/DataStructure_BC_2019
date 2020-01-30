#include <iostream>
using namespace std;

int a[2000000], b[2000000], weight[2000000], parent[2000000];
int a1[2000000], b1[2000000], w1[2000000], parent1[2000000];

void uni_test(int left, int right)
{
	if (left == right)
		return;
	if (parent[left] < parent[right])
	{
		parent[left] += parent[right];
		parent[right] = left;
	}
	else {
		parent[right] += parent[left];
		parent[left] = right;
	}
}
int findit(int x)
{
	if (parent[x] < 0)
		return  x;
	else
		return findit(parent[x]);
}
void swap_swap(int& x, int& y)
{
	int t = x; x = y; y = t;
}
void sort(int l, int r, int weight[], int a[], int b[])
{
	if (l >= r) return;
	int i = l; int j = r;
	int mid = weight[(i + j) / 2];
	while (i <= j)
	{
		while (weight[i] < mid) ++i;
		while (weight[j] > mid) --j;
		if (i <= j)
		{
			swap_swap(weight[i], weight[j]); swap_swap(a[i], a[j]); swap_swap(b[i], b[j]);
			++i; --j;
		}

	}
	sort(l, j, weight, a, b);
	sort(i, r, weight, a, b);
}

int main1()
{

	int n, m, num=0; 
	cin >> n >> m;

	for (int i = 1; i <= m; ++i)
	{
		cin >> a[i] >> b[i] >> weight[i];
	}
	sort(1, m, weight, a, b);

	for (int i = 1; i <= n; ++i) parent[i] = -1;

	int cnt = 0, u, verticle, i = 1, vers = 0;

	while (vers != n - 1)
	{
		u = findit(a[i]);
		verticle = findit(b[i]);
		if (u != verticle)
		{
			uni_test(u, verticle);
			vers++;
			cnt += weight[i];
		}
		++i;
	}
	for (int x = 0; x <= 7; ++x) {
		for (int k = 0; k <= 10000; ++k) {
			a1[k] = num+1;
			for (int j = 0; j <= 10000; ++j) {
				num += 1;

			}
		}
	}
	cout << cnt;
	return 0;
}
