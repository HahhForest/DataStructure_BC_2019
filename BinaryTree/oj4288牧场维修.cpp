#include<iostream>
using namespace std;

void insert(int* t, int x, int len)
{
	if (len == 0) { t[0] = x; return; }
	int i = 0;
	int j = 0;

	while (t[i] < x && i < len) i += 1;
	if (i == len) { t[i] = x; }
	else {
		for (j = len; j > i; j -= 1) {
			t[j] = t[j - 1];
		}
		t[i] = x;
	}
	//cout << "insert suc" << endl;
}



int cut(int* tree, int l,int r,int sum)
{
	if (l == r)
		return 0;

	int subsum = 0;
	int tocut = l;
	while (subsum <= sum / 2) {
		subsum += tree[tocut];
		tocut += 1;
	}

	tocut -= 1;
	int tmp2 = subsum;
	int tmp1 = subsum - tree[tocut];
	tocut = ((sum / 2 - tmp1) > (tmp2 - sum / 2)) ? tocut : tocut-1;

	
	int i = l;
	int sum1 = 0; int sum2 = 0;
	for (i; i <= tocut; i += 1) 
	{ sum1 += tree[i]; }
	for (i; i <= r; i += 1) {sum2 += tree[i]; }

	return cut(tree,l, tocut, sum1) + cut(tree,tocut+1,r, sum2) + sum;
}

int main()
{
	int number = 0;
	int tree[20000];
	cin >> number;

	int len = 0;
	int x = 0;
	int sum = 0;
	while (len <= number-1)
	{
		cin >> x;
		sum += x;
		insert(tree, x, len);
		len += 1;
	}
	cout<<cut(tree, 0,len-1, sum);
	return 0;
}


