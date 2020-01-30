#include<iostream>
using namespace std;
#include <queue>

//放入优先级队列的节点
struct bnode
{
	int data;
	bool operator < (const bnode rp) const {
		return data > rp.data;
	}
};

int main15()
{
	priority_queue<bnode> q;
	int opnum, i;
	char* op = new char[10];
	int toadd;
	bnode add, show;
	cin >> opnum;
	for (i = 0; i <= opnum - 1; ++i) {
		cin >> op;

		//insert
		if (op[0] == 'i') {
			cin >> toadd;
			add.data = toadd;
			q.push(add);
			continue;
		}

		//delete
		if (op[0] == 'd') {
			q.pop();
			continue;
		}

		//min
		if (op[0] == 'm') {
			show = q.top();
			cout << show.data << '\n';
			continue;
		}
	}
	return 0;
}