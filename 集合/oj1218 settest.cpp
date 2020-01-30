#include <iostream>
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

int desame(int num[], int size)
{
	int i, j, repeat = 0;
	for (i = 1, j = 1; j <= size - 1;) {
		if (num[j] != num[i - 1])
			num[i++] = num[j++];
		else {
			j += 1;
			repeat += 1;
		}
	}
	return size - repeat;
}

void output(int set[], int size)
{
	if (size > 0) cout << set[0];
	for (int k = 1; k <= size - 1; ++k)
		cout << ' ' << set[k];
	cout << '\n';
	/*for (int k = 0; k <= size - 1; ++k)
		cout << set[k] << ' ';*/

}

int main7()
{
	int opnum=0;
	int i, j, setnum=0;
	int k, cmp1, cmp2;
	char op;
	char* operation = new char[200];
	int set[100], size=0;
	const int x = 1;

	cin >> opnum;
	for (i = 0; i <= opnum - 1; ++i) {
		cin >> op >> setnum;
		//cout << '\n' << op << ' ' << setnum << '\n';
		int* newset = new int[setnum];
		for (k = 0; k <= setnum - 1; ++k) cin >> newset[k];
		//cout << "\nnewset: ";
		//for (k = 0; k <= setnum - 1; ++k) cout << newset[k]<<' ';
		//cout << '\n';

		mergeSort(newset, 0, setnum-1);

		int newsize = 0;
		switch (op) {
		case '+': {
			int point = 0;
			for (point = 0; point <= setnum - 1;) {
				set[size++] = newset[point++];
			}
			mergeSort(set, 0, size-1);
			size = desame(set, size);

			//cout << "\n+: ";

			output(set, size);
			break;
		}
		case '-': {
			
			int cmp1, cmp2, repeat=0, tmpoint = 0;
			int* tmp = new int[size];
			for (cmp1 = 0, cmp2 = 0; cmp1 <= size - 1;) {	
				if (cmp2 == setnum + 1) {
					tmp[tmpoint++] = set[cmp1++];
					continue;
				}
				if (set[cmp1] == newset[cmp2]) {
					++cmp1;
					++repeat;
				}
				if (set[cmp1] > newset[cmp2])
					++cmp2;
				if (set[cmp1] < newset[cmp2]) {
					tmp[tmpoint++] = set[cmp1++];
				}
			}
			size = size - repeat;
			for (k = 0; k <= size - 1; ++k)
				set[k] = tmp[k];

			output(set, size);
			break;
		}
		case '*': {
			int point = 0, tmpoint = 0, newsize = 0;
			int* tmp = new int[size];

			for (point = 0; point <= setnum - 1;) {
				set[size++] = newset[point++];
			}
			mergeSort(set, 0, size-1);

			for (k = 1; k <= size - 1; ) {
				//cout << "k: " << k << endl;
				if (set[k] == set[k - 1]) {
					tmp[tmpoint++] = set[k++];
					++newsize;

					while (set[k] == set[k - 1]) ++k;
				}
				else
					++k;
			}
			size = newsize;
			for (k = 0; k <= size - 1; ++k)
				set[k] = tmp[k];

			output(set, size);
			break;
		}
		}
	}
	return 0;
}