#include <iostream>
using namespace std;

#include "seqQueue.h"
#include "seqQueue.cpp"

int main()
{
	seqQueue<char> q(2);
	q.enQueue('A');
	q.enQueue('B');
	q.enQueue('C');
	cout << q.deQueue();
	cout << q.deQueue();
	cout << q.getHead();
	cout << q.deQueue();
	cout << q.isEmpty();

}
