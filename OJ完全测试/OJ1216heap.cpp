#include <iostream>
#include <queue>
using namespace std;

struct bnode
{
	int data;
	bool operator < (const bnode rp) const {
		return data > rp.data;
	}
};

int main18()
{
	int M;
	int tmp[20000];
	int i, j, k;
	char* op = new char[10];
	int toadd, tofind, denum, tode, findnum, t;
	cin >> M;
	priority_queue<bnode> q;
	bnode b;
	for (k = 0; k <= M - 1; ++k) {
		cin >> op;
		if (op[0] == 'i') {
			cin >> b.data;
			q.push(b);
		}

		if (op[0] == 'f') {
			i = 0;
			cin >> findnum;
			while (q.top().data <= findnum) {
				t = q.top().data;
				q.pop();
				tmp[i++] = t;
			}
			cout << i + 1<< endl;
			for (j = i - 1; j >= 0; --j) {
				b.data = tmp[j];
				q.push(b);
			}
		}

		if (op[0] == 'd') {
			cin >> tode>>denum;
			for (i = 0; i <= tode - 2; ++i) {
				t = q.top().data;
				q.pop();
				tmp[i] = t;
			}
			t = q.top().data - denum;
			q.pop();
			b.data = t;
			q.push(b);
			for (i = tode-2; i >= 0; --i) {
				b.data = tmp[i];
				q.push(b);
			}
		}

		//if (op[0] == 't') {
		//	cout << q.top().data<<'\n';
		//	q.pop();
		//}

	}

	return 0;
}