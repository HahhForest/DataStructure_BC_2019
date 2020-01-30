#include"../linkList/linkList.cpp"

int main14()
{
	long long int m, n, k = 1,  result = 0;
	int i = 0, j = 0, m1, n1, ch = 0;
	cin >> m >> n;

	//cout << m + n << endl;
	linkList<int> qm, qn;
	while (m != 0) {
		qm.insert(i, m % 10);
		m /= 10;
		++i;
	}
	while (n != 0) {
		qn.insert(j, n % 10);
		n /= 10;
		++j;
	}
	while (i != 0 || j != 0) {
		if (i == 0) {
			m = 0;
			n = qn.visit(0);
			result += ((m + n + ch) % 10) * k;

			qn.remove(0);
			ch = (m + n + ch) / 10;
			k *= 10;
			--j;
			continue;
		}
		if (j == 0) {
			n = 0;
			m = qm.visit(0);
			result += ((m + n + ch) % 10) * k;

			qm.remove(0);
			ch = (m + n + ch) / 10;
			k *= 10;
			--i;
			continue;
		}
		if (i != 0 && j != 0) {
			m = qm.visit(0);
			n = qn.visit(0);
			result += ((m + n + ch) % 10) * k;

			qm.remove(0);
			qn.remove(0);
			ch = (ch + m + n) / 10;
			k *= 10;
			--i;
			--j;
			continue;
		}
	}
	result += ch * k;
	cout << result;
	return 0;
}