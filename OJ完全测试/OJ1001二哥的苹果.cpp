#include <iostream>
using namespace std;
#include <queue>

struct bnode
{
	int data;
	bool operator <(const bnode rp) const {
		return data > rp.data;
	}
};

int main16()
{
	priority_queue<bnode> q;
	int height, stool, num;
	int i, apple, result = 0;
	bnode topush;
	
	cin >> height >> stool >> num;
	for (i = 0; i <= num - 1; ++i) {
		cin >> apple;
		topush.data = apple;
		q.push(topush);
	}

	for (i = 0; i <= num - 1; ++i) {
		if (q.top().data <= height + stool) {
			result += 1;
			q.pop();
			continue;
		}
		if (q.top().data > height + stool) {
			break;
		}
	}

	cout << result;
	return 0;
}