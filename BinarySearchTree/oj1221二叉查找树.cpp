#include<iostream>
#include <string.h>

using namespace std;

void insert(int* t, int x,int len)
{
	if (len == 0) { t[0] = x; return; }
	int i = 0;
	int j = 0;
	
	while (t[i] < x && i< len) i += 1;
	if (i == len) { t[i] = x; }
	else {
		for (j = len ; j > i; j -= 1) {
			t[j] = t[j - 1];
		}
		t[i] = x;
	}
	//cout << "insert suc" << endl;
}

int del(int* t, int x, int len)
{
	int i = 0;

	while (t[i] < x && i <= len - 1) i += 1;

	if ( i == len) return len;
	if (t[i] != x) return len;
	else {
		if (i == len - 1) { t[i] = 9999; return len-1; }
		else {
			for (; i <= len - 2; i += 1) {
				t[i] = t[i + 1];
			}
			t[len - 1] = 9999;
			return len - 1;
		}
	}

}

int delles(int* t, int x, int len)
{
	int i = 0;
	int j = 0;
	for (; i <= len - 1; i += 1) {
		if (t[i] >= x) break;
	}
	if (i == 0) return len;
	else if (i == len) {
		for (int k = 0; k <= len - 1; k += 1) t[k] = 9999;
		return 0;
	}
	else {
		for (; j <= len - 1 - i; j += 1) {
			t[j] = t[j + i];
		}
		for (j; j <= len - 1; j += 1) {
			t[j] = 9999;
		}
	}
	return len - i;
}

int delgreater(int* t, int x, int len)
{

	int i = 0;
	while (t[i] <= x) {
		i += 1;
	}
	if (i == len) return len;
	int tmp = i;
	for (; i <= len-1; i += 1) {
		t[i] = 9999;
	}
	return tmp;
}

int delinteral(int* t, int a, int b, int len)
{
	if (a >= b) return len;

	int i = 0;
	int j = len - 1;
	int k = 0;
	for (i= 0; i <= len - 1; i += 1) {
		if (t[i] > a) break;
	}
	for (j = len-1; j >= 0; j -= 1) {
		if (t[j] < b) break;
	}

	if (i > j) return len;
	else {
		for (k = 0; k <= len - 2 - j; k += 1) {
			t[i + k] = t[j + 1 + k];
		}
		int tmp = len - j + i - 1;
		for (i = i+k; i <= len - 1; i += 1) {
			t[i] = 9999;
		}
		return tmp;
	}
}

int find1(int* t, int x,int len)
{
	int i = 0;
	while (i <= len - 1) {
		if (t[i] == x) return 1;
		i += 1;
	}

	return 0;
}

int find_ith(int* t, int a, int len)
{
	if (a > len)
		return 9999;
	else return t[a - 1];
}

int main2()
{
	int tree[5000];
	int len = 0;
	int opnum=0;
	int i = 0;
	int x = 0;
	int f = 0;

	char op[20] = "###################";
	//cout << "input opnum: ";
	cin >> opnum;
	while (i < opnum) {
		//cout << "input op: ";

		char tmpop[20] = "###################";
		strcpy_s(op, tmpop);
		cin >> op;
		//cout << "op: " << op[5]<<endl;

		if (op[0] == 'i') {
			cin >> x;
			insert(tree, x, len);
			len += 1;
			//cout << "len: " << len;
		}

		else if (op[0] == 'd' && op[7] == '#') {
			cin >> x;
			len = del(tree, x, len);

			//for (int j = 0; j <= len - 1; j += 1)cout << tree[j] << ' ';
		}

		else if (op[0] == 'd' && op[7] == 'l') {
			cin >> x;
			len = delles(tree, x, len);
		}

		else if (op[0] == 'd' && op[7] == 'g') {
			cin >> x;
			len = delgreater(tree, x, len);
		}

		else if (op[0] == 'd' && op[7] == 'i') {
			int a = 0, b = 0;
			cin >> a >> b;
			len = delinteral(tree, a, b, len);
			//cout << "len: " <<len<< endl;
		}
		
		else if (op[0] == 'f' && op[5] == '#') {
			cin >> x;

			f = find1(tree, x, len);
			if (f) cout << 'Y'<<'\n';
			else cout << 'N'<<'\n';
		}

		else if (op[0] == 'f' && op[5] == 'i') {
			cin >> x;
			f = find_ith(tree, x, len);
			if (f == 9999) cout << 'N'<<'\n';
			else cout << f<<'\n';
		}

		i += 1;
	}


	return 0;
}