# include"../linkList/linkList.cpp"

int main13()
{
	char* op = new char[10];
	int type = 0, m, n;
	cin >> op;
	cin >> m >> n;
	if (op[0] == 'i')
		type = 0;
	if (op[0] == 'c')
		type = 1;
	if (op[0] == 'd')
		type = 2;

	linkList<int> qm1, qn1, out1;
	linkList<char> qm2, qn2, out2;
	linkList<double> qm3, qn3, out3;
	int m1, n1;
	char m2, n2;
	double m3, n3;
	int i;

	if (type == 0) {
		for (i = 0; i <= m - 1; ++i) {
			cin >> m1;
			qm1.insert(0, m1);
		}
		for (i = 0; i <= n - 1; ++i) {
			cin >> n1;
			qn1.insert(0, n1);
		}

		for (i = 0; i <= n - 1; ++i)
			out1.insert(0, qn1.visit(i));
		for (i = 0; i <= m - 1; ++i)
			out1.insert(0, qm1.visit(i));

		for (i = 0; i <= m + n - 1; ++i)
			cout << out1.visit(i) << ' ';
	}

	if (type == 1) {
		for (i = 0; i <= m - 1; ++i) {
			cin >> m2;
			qm2.insert(0, m2);
		}
		for (i = 0; i <= n - 1; ++i) {
			cin >> n2;
			qn2.insert(0, n2);
		}

		for (i = 0; i <= n - 1; ++i)
			out2.insert(0, qn2.visit(i));
		for (i = 0; i <= m - 1; ++i)
			out2.insert(0, qm2.visit(i));

		for (i = 0; i <= m + n - 1; ++i)
			cout << out2.visit(i) << ' ';
	}

	if (type == 2) {
		for (i = 0; i <= m - 1; ++i) {
			cin >> m3;
			qm3.insert(0, m3);
		}
		for (i = 0; i <= n - 1; ++i) {
			cin >> n3;
			qn3.insert(0, n3);
		}

		for (i = 0; i <= n - 1; ++i)
			out3.insert(0, qn3.visit(i));
		for (i = 0; i <= m - 1; ++i)
			out3.insert(0, qm3.visit(i));

		for (i = 0; i <= m + n - 1; ++i)
			cout << out3.visit(i) << ' ';
	}

	return 0;
}