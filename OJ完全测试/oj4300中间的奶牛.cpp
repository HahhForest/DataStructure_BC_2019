#include<iostream>
using namespace std;

//归并排序归并函数：在左右两边都有序时生成整个有序表
//左：0~mid-1；右：mid~right
void merge(int num[], int left, int mid, int right)
{
	int* tmp = new int[right - left + 1];
	int i = left, j = mid, k = 0;

	while (i < mid && j <= right) {
		if (num[i] <= num[j])
			tmp[k++] = num[i++];
		if (num[i] > num[j])
			tmp[k++] = num[j++];
	}

	while (i < mid) tmp[k++] = num[i++];
	while (j <= right) tmp[k++] = num[j++];

	for (i = 0, k = left; k <= right;)
		num[k++] = tmp[i++];
	delete[]tmp;
}

//归并排序
//O(NlogN)，但是需要额外的空间
void mergeSort(int num[], int left, int right)
{
	int mid = (left + right) / 2;

	if (left == right) return;
	mergeSort(num, left, mid);
	mergeSort(num, mid + 1, right);
	//merge的mid是右有序表开头的位置
	merge(num, left, mid + 1, right);
}

int main5()
{
	int N;

	cin >> N;
	int* cows = new int[N];

	for (int i = 0; i <= N - 1; ++i)
		cin >> cows[i];

	mergeSort(cows, 0, N - 1);
	cout << cows[N / 2];

	delete[]cows;
	return 0;
}