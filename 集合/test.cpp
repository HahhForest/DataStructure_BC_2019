#include<iostream>
using namespace std;

int* test(int a)
{
	int* t = new int[a];
	for (int i = 0; i <= a - 1; ++i)
		t[i] = i;
	delete[]t;
	return t;
}
int main()
{
	int* b = new int[5];
	b = test(5);
	for(int i = 0; i <= 4; ++i)
	cout << b[i];
	return 0;
}

