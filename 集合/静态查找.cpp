#include <iostream>
using namespace std;

//���ϵĴ洢��������������
//���ϵĲ��������ҡ�����
//���ݣ�
//��̬���ұ�
//��̬���ұ���������ɢ�б�
//�����㷨
//��洢�ϵĲ�������
//���ཻ��

//����Ԫ������
template <class KEY, class OTHER>
struct SET
{
	KEY key;
	OTHER other;
};

//������Ż����˳�����
//0λ�ÿճ���Ϊ�����ڡ������ܷ���һ��ֵ��ʡ��һ�μ���±������
template <class KEY, class OTHER>
int seqSearch(SET<KEY, OTHER>data[], int size, const KEY& x)
{
	int i;
	data[0].key = x;
	for ( i = size; x != data[i].key; --i);
	return i;
}

//�����˳�����
//�����ǵ���˳��
template<class KEY, class OTHER>
int seqSearch2(SET<KEY, OTHER>data[], int size, const KEY& x)
{
	int i;
	data[0].key = x;
	for ( i = size; x < data[i].key; --i);
	if (x == data[i].key) return i;
	else return 0;
}

//��������ֲ���
//�����ǵ���˳��
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

//�������ֵ����
//���������ݷֲ��ȽϾ��ȵ����
//���ݴ��µķֲ������ȷ������Ԫ��λ��
//�����ǵ���˳��
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
