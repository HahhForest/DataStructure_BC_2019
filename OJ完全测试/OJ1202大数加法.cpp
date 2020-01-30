#include <iostream>
using namespace std;
#include "../linkList/linkList.cpp"

int main12()
{
	long long int m, n, result = 0;
	long long int i=0, j=0, k = 1, l, ch = 0;
	int min;
	cin >> m >> n;
	cout << m + n << endl;
	//cout << "m: " << m << '\t' << "n: " << n << endl;
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
	min = (i <= j) ? i : j;
	long long int toadd;

	for (l = 1; l <= min ; ++l) {
		m = qm.visit(0);
		n = qn.visit(0);
		toadd = ((m + n + ch) % 10) * k;
		result += toadd;
		k *= 10;
		ch = (m + n + ch) / 10;
		qm.remove(0);
		qn.remove(0);
	}

	//cout << result << endl;
	//cout << ch <<'\t'<<k<< endl;
	l = 0;
	if (i > j)
		while (l <= i - j - 1) {
			toadd = ((qm.visit(0) + ch) % 10) * k;
			result += toadd;
			ch = (qm.visit(0) + ch) / 10;
			k *= 10;
			qm.remove(0);
			l += 1;
		}
	if(i < j) 
		while (l <= j - i - 1) {
			//cout << "qn: " << qn.visit(0) << '\t' << "ch: " << ch << endl;
			toadd = ((qn.visit(0) + ch) % 10) * k;
			//cout << toadd <4+2< endl;
			result += toadd;
			ch = (qn.visit(0) + ch) / 10;
			k *= 10;
			qn.remove(0);
			l += 1;
		}
	result += ch * k;
	cout << result;
	return 0;
}