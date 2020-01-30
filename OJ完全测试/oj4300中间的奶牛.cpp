#include<iostream>
using namespace std;

//�鲢����鲢���������������߶�����ʱ�������������
//��0~mid-1���ң�mid~right
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

//�鲢����
//O(NlogN)��������Ҫ����Ŀռ�
void mergeSort(int num[], int left, int right)
{
	int mid = (left + right) / 2;

	if (left == right) return;
	mergeSort(num, left, mid);
	mergeSort(num, mid + 1, right);
	//merge��mid���������ͷ��λ��
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