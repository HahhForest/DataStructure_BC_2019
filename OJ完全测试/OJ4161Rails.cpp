# include "../linkStack/linkStack.cpp"

int main17()
{
	bool yes = true;
	int n;
	int i, trainnum = 1, outnum = 1;
	linkStack<int> s;

	cin >> n;
	int* train = new int[n];
	for (i = 1; i <= n; ++i)
		cin >> train[i];

	while (outnum <= n) {
		if (trainnum == train[outnum]) {
			trainnum++;
			outnum++;
		}
		else if (!s.isEmpty() && s.top() == train[outnum]) {
			s.pop();
			outnum++;
		}
		else if (trainnum <= n) {
			s.push(trainnum);
			trainnum++;
		}
		else
			break;
	}

	if (outnum <= n)
		cout << "No";
	else
		cout << "Yes";

	return 0;
}