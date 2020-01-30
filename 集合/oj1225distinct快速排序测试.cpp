#include <iostream>
using namespace std;

int divide(int num[], int low, int high)
{
	int k = num[low];
	do {
		while (num[high] >= k && low < high) --high;
		if (low < high) {
			num[low] = num[high];
			++low;
		}
		while (num[low] <= k && low < high) ++low;
		if (low < high) {
			num[high] = num[low];
			--high;
		}
	} while (low != high);
	num[low] = k;
	return low;
}

//��������
//��������ִ��һ�λ��֣������ݹ飨���ң�
//���O(N^2)����ã�O(NlogN)
void quickSort(int num[], int low, int high)
{
	int mid;

	if (low >= high) return;
	mid = divide(num, low, high);
	quickSort(num, low, mid - 1);
	quickSort(num, mid + 1, high);
}

int main2()
{
	int size, tmp, i, num=1 ;
	int* lst;
	lst = new int[10000000];
	cin >> size;
	for (i = 0; i <= size - 1; ++i) {
		cin >> tmp;
		lst[i] = tmp;
	}
	quickSort(lst, 0, size - 1);
	//for (i = 1; i <= size - 1; ++i)
	//	if (lst[i] != lst[i - 1])
	//		++num;
	//cout << num;
	cout << lst[0];
	for (i = 1; i <= size - 1; ++i)
		cout << ' ' << lst[i];
	return 0;
}