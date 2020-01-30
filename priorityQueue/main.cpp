#include <iostream>
using namespace std;
#include "priorityQueue.cpp"

int main()
{
	priorityQueue<int> q;
	int opnum;
	int num1, num2;
	int insertnum = 0;
	char op[10];

	cin >> opnum;

	while (opnum >= 1) {
		cin >> op;

		if (op[0] == 'i') {
			cin >> num1;
			q.enQueue(num1);
			insertnum += 1;
		}
		
		else if (op[0] == 'f') {
			cin >> num1;
			cout << q.find(num1, insertnum) << '\n';
		}

		else if (op[0] == 'd') {
			cin >> num1 >> num2;
			q.decrease(num1, num2);
		}

		opnum -= 1;
	}
	return 2;
}

