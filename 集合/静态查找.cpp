#include <iostream>
using namespace std;

//集合的存储：借用其他容器
//集合的操作：查找、排序
//内容：
//静态查找表
//动态查找表：查找树，散列表
//排序算法
//外存储上的查找排序
//不相交集

//集合元素类型
template <class KEY, class OTHER>
struct SET
{
	KEY key;
	OTHER other;
};

//无序表：优化后的顺序查找
//0位置空出来为“岗哨”，总能返回一个值，省略一次检查下标的运算
template <class KEY, class OTHER>
int seqSearch(SET<KEY, OTHER>data[], int size, const KEY& x)
{
	int i;
	data[0].key = x;
	for ( i = size; x != data[i].key; --i);
	return i;
}

//有序表：顺序查找
//假设是递增顺序
template<class KEY, class OTHER>
int seqSearch2(SET<KEY, OTHER>data[], int size, const KEY& x)
{
	int i;
	data[0].key = x;
	for ( i = size; x < data[i].key; --i);
	if (x == data[i].key) return i;
	else return 0;
}

//有序表：二分查找
//假设是递增顺序
template<class KEY, class OTHER>
int binarySearch(SET<KEY, OTHER>data[], int size, const KEY& x)
{
	int low = 1, high = size, mid;
	while (low <= high) {
		mid = (low + high) / 2;

		if (x == data[mid].key)	return mid;
		if (x < data[mid].key) high = mid - 1;
		else low = mid + 1;
	}
	return 0;
}

//有序表：插值查找
//适用于数据分布比较均匀的情况
//根据大致的分布情况来确定被查元素位置
//假设是递增顺序
template<class KEY, class OTHER>
int interSearch(SET<KEY, OTHER> data[], int size, const KEY& x)
{
	int low = 1, high = size, next;
	while (low <= high) {
		next = low + ((x - data[low].key) * (high - low - 1) / (data[high].key - data[low].key));
		
		if (x == data[next].key) return next;
		if (x < data[next].key) high = next - 1;
		else low = next + 1;
	}
	return 0;
}

int main7()
{
	SET<int, char> a[11];
	for (int i = 1; i <= 10; ++i)
		a[i].key = 2 * i;
		
	cout << interSearch(a, 10, 9);
	return 7;
}
