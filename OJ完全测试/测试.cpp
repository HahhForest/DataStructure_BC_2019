#include <iostream>
using namespace std;

int main8()
{
	int *p = new int[2], i = 0;
	while (i <= 10) {
		p[0] = i;
		cout << p[0] << endl;
		delete p;
		i += 1;
	}

	return 0;
}