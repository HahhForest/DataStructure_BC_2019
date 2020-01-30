#include <iostream>
using namespace std;

int main1()
{
	char op;
	int opnum;
	int num[10];

	cin >> op >> opnum;
	cout << op << ' ' << opnum;

	for (int i = 0; i <= opnum - 1; ++i)
		cin >> num[i];

	for (int i = 0; i <= opnum - 1; ++i)
		cout << num[i]<<' ';
	return 0;
}

