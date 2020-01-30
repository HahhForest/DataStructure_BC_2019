#include <iostream>
using namespace std;

#include "linkQueue.h"
#include "linkQueue.cpp"

int main()
{
	linkQueue<char> q;
	q.enQueue('A');
	q.enQueue('B');
	q.enQueue('C');
	cout << q.deQueue();
	cout << q.deQueue();
	cout << q.getHead();
	cout << q.deQueue();
	cout << q.isEmpty();

	int i = 0;
	linkQueue <int> s;
	for (int i = 0; i < 10; ++i) s.enQueue(2 * i);
	while (!s.isEmpty())  cout << s.deQueue() << ' ';
	cout << endl;

	for (i = 0; i < 15; ++i) s.enQueue(i);
	while (!s.isEmpty()) 	 cout << s.deQueue() << ' ';
	cout << endl;

	return 0;


}

