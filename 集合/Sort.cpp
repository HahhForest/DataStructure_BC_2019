#include <iostream>
using namespace std;
//�����㷨
//�������룬ѡ�񣬽������鲢����������
//�������򣺽�һ��Ԫ��֮ǰ�����п���������ģ�������뱣�����򣬴ӵڶ�������n��һ�β��룬����������
//ѡ������ÿ�δ�ʣ��Ԫ����ѡ����С��Ԫ�أ��ų�����
//��������ÿ�ζ�����Ԫ�ؽ��бȽ�ȷ���Ƿ�Ҫ����
//�鲢���򣺺ϲ������Ѿ�����ı�
//�������򷨣��ڴ����򷨣���ͨ������ķ�ʽ�������ĸ���λ��������

//��������
//ֱ�Ӳ�������
//ʱ�临�Ӷȣ����ԴﵽO(n^2)
void simplesertSort(int num[], int size)
{
	int tobesort = 1, tmp,tobecompare;
	for (tobesort; tobesort <= size - 1; tobesort += 1) {
		tmp = num[tobesort];
		if (tmp >= num[tobesort - 1]) continue;
		for (tobecompare = tobesort - 1; tobecompare >= 0; tobecompare -= 1) {
			if (tmp < num[tobecompare]) 
				num[tobecompare+1] = num[tobecompare];
			if (tmp >= num[tobecompare]) {
				num[tobecompare + 1] = tmp;
				break;
			}
		}
		if (tobecompare == -1) num[0] = tmp;
	}
}

//����ֱ�Ӳ�������
void testsimplesertSort(int num[], int size)
{
	simplesertSort(num, size);
	cout << "\nֱ�Ӳ�������";
	for (int i = 0; i <= 9; i += 1) cout << num[i] << ' ';
}

//��������
//�۰���������ö��ַ������ҵ�����λ��
//��������O(n^2)
void bisertSort(int num[], int size)
{
	int left, mid, right, toinsert,tomove, tmp, todo = 1;
	for (todo; todo <= size - 1; ++todo) {
		tmp = num[todo];
		left = 0; right = todo - 1;

		if (tmp >= num[todo - 1])
			continue;

		while (left != right) {
			mid = (left + right) / 2;

			if (num[mid] > tmp)
				right = mid - 1;
			else {
				if (num[mid + 1] > todo)
					break;
				else
					left = mid + 1;
			}
		}
		if (num[left] <= tmp)
			toinsert = left + 1;
		else
			toinsert = left - 1;

		for (tomove = todo - 1; tomove >= toinsert + 1; --tomove) 
			num[tomove + 1] = num[tomove];
		num[toinsert] = tmp;
	}

}

//�����۰��������
void testbisertSort(int num[], int size)
{
	bisertSort(num, size);
	cout << "\n�۰��������";
	for (int i = 0; i <= size - 1; ++i)
		cout << num[i] << ' ';
}

//��������
//ϣ������gap��N/2ƽ����1
//���Ȼ��N^2������ƽ��δN^(3/2)
void shellSort(int num[], int size)
{
	int i, j, tmp, gap = size / 2;
	for (gap; gap > 0; gap /= 2) {
		for (i = gap; i <= size - 1; ++i) {
			tmp = num[i];
			for (j = i - gap; j >= 0 && num[j] > tmp; j -= gap) 
				num[j + gap] = num[j];
			
			num[j + gap] = tmp;
		}
	}
}

//����ϣ������
void testshellSort(int num[], int size)
{
	shellSort(num, size);
	cout << "\nϣ������";
	for (int i = 0; i <= size - 1; ++i)
		cout << num[i]<<' ';
}

//ѡ������
//ֱ��ѡ������O(N^2)
void simpleselectSort(int num[], int size)
{
	int i,minpoint, tmp, toput;
	for (toput = 0; toput <= size - 1; ++toput) {
		minpoint = toput;
		for (i = toput; i <= size - 1; ++i) {
			if (num[i] < num[minpoint])
				minpoint = i;
		}
		tmp = num[minpoint];
		num[minpoint] = num[toput];
		num[toput] = tmp;
	}
}

//����ֱ��ѡ������
void testsimpleselectSort(int num[], int size)
{
	simpleselectSort(num, size);
	cout << "\nֱ��ѡ������";
	for (int i = 0; i <= size - 1; ++i)
		cout << num[i] << ' ';
}

//���������¹��˺���
void percolateDown(int num[], int hole, int size)
{
	int child, tmp = num[hole];
	
	for (; hole * 2 + 1 < size; hole = child) {
		child = hole * 2 + 1;
		if (child != size - 1 && num[child + 1] > num[child])
			child++;
		if (num[child] > tmp)
			num[hole] = num[child];
		else break;
	}
	num[hole] = tmp;
}

//ѡ������
//������ʹ�����ѣ�O(NlogN)
//�����ȼ������еĶѲ�ͬ���ǣ����ݴ�0��ʼ�洢�����ڵ���(i-1)/2, ������2i+1
void heapSort(int num[], int size)
{
	int i, tmp;
	for (i = size / 2 - 1; i >= 0; i--)
		percolateDown(num, i, size);

	for (i = size - 1; i > 0; --i) {
		tmp = num[0];
		num[0] = num[i];
		num[i] = tmp;
		percolateDown(num, 0, i);
	}
}

//���Զ�����
void testheapSort(int num[], int size)
{
	heapSort(num, size);
	cout << "\n������";
	for (int i = 0; i <= size - 1; ++i)
		cout << num[i] << ' ';
}

//��������
//ð�������O(N^2)
void bubbleSort(int num[], int size)
{
	bool tran = true;
	int tmp, i;
	while (tran==true) {
		tran = false;
		for (i = 0; i <= size - 2; ++i) {
			if (num[i] > num[i + 1]) {
				tmp = num[i];
				num[i] = num[i + 1];
				num[i + 1] = tmp;
				tran = true;
			}
			else continue;
		}
		//cout << "\ntran: " << tran;
	}
}

//����ð������
void testbubbleSort(int num[], int size)
{
	bubbleSort(num, size);
	cout << "\nð������";
	for (int i = 0; i <= size - 1; ++i)
		cout << num[i] << ' ';
}

//�������򻮷ֺ���
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

//���������װ����
void testquickSort(int num[], int size)
{
	quickSort(num, 0, size - 1);
	cout << "\n��������";
	for (int i = 0; i <= size - 1; ++i)
		cout << num[i] << ' ';
}

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
	mergeSort(num, mid+1, right);
	//merge��mid���������ͷ��λ��
	merge(num, left, mid + 1, right);
}

//�鲢�����װ����
void testmergeSort(int num[], int size)
{
	mergeSort(num, 0, size - 1);
	cout << "\n�鲢����";
	for (int i = 0; i <= size - 1; ++i)
		cout << num[i] << ' ';
}

//ȥ��
int desame(int num[], int size)
{
	int i, j, repeat=0;
	for (i = 1, j = 1; j <= size - 1;) {
		if (num[j] != num[i - 1])
			num[i++] = num[j++];
		else {
			j += 1;
			repeat += 1;
		}
	}
	return size-repeat;
}

//void test(int set[], int newset[], int size, int setnum)
//{
//	int cmp1, cmp2;
//	for (cmp1 = 0, cmp2 = 0; cmp1 <= size - 1;) {
//		if (cmp2 == setnum ) {
//			if (set[cmp1] != set[cmp1 - 1]) cout << set[cmp1] << ' ';
//			++cmp1;
//		}
//		else {
//			if (newset[cmp2] < set[cmp1]) ++cmp2;
//			if (newset[cmp2] == set[cmp1]) { ++cmp2; ++cmp1; }
//			if (newset[cmp2] > set[cmp1]) { cout << set[cmp1] << ' '; ++cmp1; }
//		}
//	}
//}

//�������򣺿ڴ�����
//�ڴ����򷨽����
struct node {
	int data;
	node* next;
	
	node() { next = NULL; }
	node(int d) :data(d), next(NULL) {};
};

//�ڴ�����
void bucketSort(node*& p)		//p������ͷ
{
	node* bucket[10], * last[10], * tail;
	int i, j, k, base = 1, max = 0, len = 0;

	//������ֵ
	for (tail = p; tail != NULL; tail = tail->next) 
		if (tail->data > max)	max = tail->data;
	
	//������ֵ��λ��
	if (max == 0) 
		len = 0;
	else while (max > 0) {
		++len;
		max /= 10;
	}

	//ִ��len�η���������
	for (i = 0; i <= len; ++i) {
		for (j = 0; j <= 9; ++j)
			bucket[j] = last[j] = NULL;
		while (p != NULL) {
			k = (p->data) / base % 10;
			if (bucket[k] == NULL)
				bucket[k] = last[k] = p;
			else
				last[k] = last[k]->next = p;
			p = p->next;
		}
		p = NULL;	//����������ͷ
		
		//ִ������
		for (j = 0; j <= 9; ++j) {
			if (bucket[j] == NULL) continue;
			if (p == NULL)  p = bucket[j];
			else tail->next = bucket[j];
			tail = last[j];
		}
		tail->next = NULL;                   // ��β�ÿ�
		base *= 10;                          // Ϊ��һ�η�����׼��
	}
}

int main5()
{
	int test[10] = { 1,5,8,9,10,14,17,25,63,71 };
	int test1[3] = { 1,9,10 };
	//testsimplesertSort(test, 10);
	//testbisertSort(test, 10);

	//testshellSort(test, 10);

	//testsimpleselectSort(test, 10);

	//testheapSort(test, 10);

	//testbubbleSort(test, 10);

	//testquickSort(test, 10);

	//testmergeSort(test, 10);

	//test(test2, test1, 10, 3);

	return 0;
}