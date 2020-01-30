#include<iostream>
using namespace std;

bool allsame(int* data, int len)
{
	bool ans = true;
	int i = 0;
	for (i = 1; i <= len - 1; ++i)
		if (data[i - 1] != data[i])
			ans = false;
	return ans;
}

int pow(int a, int b)
{
	int ans = 1;
	int i = 0;
	for (i = 0; i <= b - 1; ++i)
		ans *= a;
	return ans;
}

int dec2bi(int x, int max, int loc)
{
	int i, j;
	int* ans = new int[max];

	for (i = max - 1; i >= 0; --i) {
		j = pow(2, i);
		if (x / j != 0) {
			ans[i] = 1;
			x -= j;
		}
		else
			ans[i] = 0;
	}
	return ans[loc];
}

//chnum：特征数，即K
int* window(int* data, int left, int right, int chnum)
{
	int* ans = new int[chnum];

	int i, j;
	for (i = 0; i <= chnum - 1; ++i) {
		for (j = left; j <= right; ++j) {
			ans[i] += dec2bi(data[j], chnum, i);
		}
	}
	return ans;
}

//len：滑窗长度，即试探解
bool fromto(int l, int r, int len, int* data, int chnum)
{
	int* ans = new int[chnum];
	bool same = false;

	int left = l, right = r;
	for (int i = left; i <= right - len + 1; ++i) {
		ans = window(data, i, i + len - 1, chnum);
		same = allsame(ans, chnum);
		if (same)
			return true;
	}
	delete[]ans;
	return false;
}

int main6()
{
	bool issame = false;

	int N, K;
	cin >> N >> K;

	int i, j;
	int left = 0, right = N, len = N / 2;
	int test = 0;

	int* cows = new int[N];
	int* ch = new int[K];

	for (i = 0; i <= N - 1; ++i)
		cin >> cows[i];

	for (len = N; len >= 1; --len) {
		issame = fromto(0, N - 1, len, cows, K);
		if (issame) {
			cout << len;
			break;
		}
		//cout << len << " is not a solution\n";
	}
	if (len == 0)
		cout << 0;


	return 0;
}

//for (len = N; len >= 1; --len) {
//	issame = fromto(0, N - 1, len, cows, K);
//	if (issame) {
//		cout << len;
//		break;
//	}
//	//cout << len << " is not a solution\n";
//}
//if (len == 0)
//cout << 0;