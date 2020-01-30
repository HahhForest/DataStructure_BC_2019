#include <iostream>
using namespace std;
//排序算法
//包括插入，选择，交换，归并，基数排序
//插入排序：将一个元素之前的序列看作是有序的，将其插入保持有序，从第二个至第n个一次插入，则序列有序
//选择排序：每次从剩下元素中选出最小的元素，排成序列
//交换排序：每次对两个元素进行比较确定是否要交换
//归并排序：合并两个已经有序的表
//基数排序法（口袋排序法）：通过分配的方式对整数的各个位依次排序

//插入排序
//直接插入排序
//时间复杂度：可以达到O(n^2)
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

//测试直接插入排序
void testsimplesertSort(int num[], int size)
{
	simplesertSort(num, size);
	cout << "\n直接插入排序：";
	for (int i = 0; i <= 9; i += 1) cout << num[i] << ' ';
}

//插入排序
//折半插入排序，用二分法快速找到插入位置
//最坏情况还是O(n^2)
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

//测试折半插入排序
void testbisertSort(int num[], int size)
{
	bisertSort(num, size);
	cout << "\n折半插入排序：";
	for (int i = 0; i <= size - 1; ++i)
		cout << num[i] << ' ';
}

//插入排序
//希尔排序：gap从N/2平分至1
//最坏仍然是N^2，但是平均未N^(3/2)
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

//测试希尔排序
void testshellSort(int num[], int size)
{
	shellSort(num, size);
	cout << "\n希尔排序：";
	for (int i = 0; i <= size - 1; ++i)
		cout << num[i]<<' ';
}

//选择排序
//直接选择排序：O(N^2)
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

//测试直接选择排序
void testsimpleselectSort(int num[], int size)
{
	simpleselectSort(num, size);
	cout << "\n直接选择排序：";
	for (int i = 0; i <= size - 1; ++i)
		cout << num[i] << ' ';
}

//堆排序向下过滤函数
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

//选择排序
//堆排序：使用最大堆，O(NlogN)
//与优先级队列中的堆不同的是，数据从0开始存储，父节点在(i-1)/2, 左子在2i+1
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

//测试堆排序
void testheapSort(int num[], int size)
{
	heapSort(num, size);
	cout << "\n堆排序：";
	for (int i = 0; i <= size - 1; ++i)
		cout << num[i] << ' ';
}

//交换排序
//冒泡排序：最坏O(N^2)
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

//测试冒泡排序
void testbubbleSort(int num[], int size)
{
	bubbleSort(num, size);
	cout << "\n冒泡排序：";
	for (int i = 0; i <= size - 1; ++i)
		cout << num[i] << ' ';
}

//快速排序划分函数
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

//交换排序
//快速排序：执行一次划分，两个递归（左右）
//最坏：O(N^2)；最好：O(NlogN)
void quickSort(int num[], int low, int high)
{
	int mid;

	if (low >= high) return;
	mid = divide(num, low, high);
	quickSort(num, low, mid - 1);
	quickSort(num, mid + 1, high);
}

//交换排序包装函数
void testquickSort(int num[], int size)
{
	quickSort(num, 0, size - 1);
	cout << "\n快速排序：";
	for (int i = 0; i <= size - 1; ++i)
		cout << num[i] << ' ';
}

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
	mergeSort(num, mid+1, right);
	//merge的mid是右有序表开头的位置
	merge(num, left, mid + 1, right);
}

//归并排序包装函数
void testmergeSort(int num[], int size)
{
	mergeSort(num, 0, size - 1);
	cout << "\n归并排序：";
	for (int i = 0; i <= size - 1; ++i)
		cout << num[i] << ' ';
}

//去重
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

//基数排序：口袋排序法
//口袋排序法结点类
struct node {
	int data;
	node* next;
	
	node() { next = NULL; }
	node(int d) :data(d), next(NULL) {};
};

//口袋排序法
void bucketSort(node*& p)		//p：链表头
{
	node* bucket[10], * last[10], * tail;
	int i, j, k, base = 1, max = 0, len = 0;

	//找最大键值
	for (tail = p; tail != NULL; tail = tail->next) 
		if (tail->data > max)	max = tail->data;
	
	//找最大键值的位数
	if (max == 0) 
		len = 0;
	else while (max > 0) {
		++len;
		max /= 10;
	}

	//执行len次分配与重组
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
		p = NULL;	//重组后的链表头
		
		//执行重组
		for (j = 0; j <= 9; ++j) {
			if (bucket[j] == NULL) continue;
			if (p == NULL)  p = bucket[j];
			else tail->next = bucket[j];
			tail = last[j];
		}
		tail->next = NULL;                   // 表尾置空
		base *= 10;                          // 为下一次分配做准备
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