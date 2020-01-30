#include <iostream>

using namespace std;

//set��û���ظ�Ԫ��
class set
{
private:
	int* data;
	int size;
public:
	set() :data(new int[1000]), size(0) {};
	bool find(int x);
	void insert(int x);
	int del(int x[], int setnum);
	void traverse();
	int uni(int x[], int setnum);
};

//�����Ƿ��ҵ�
bool set::find(int x)
{
	int i;
	for (i = 0; i <= size - 1; ++i)
		if (data[i] == x)
			return true;
	return false;
}

//��һ���б���������
int set::uni(int x[], int setnum)
{
	int* tmp = new int[size];
	int toadd;
	int i, newsize = 0, j = 0;
	for (i = 0; i <= setnum - 1; ++i) 
		if (find(x[i])) {
			toadd = x[i];
			tmp[j++] = x[i];
			++newsize;
		}
	size = newsize;
	for (i = 0; i <= size - 1;++i)
		data[i] = tmp[i];
	delete[]tmp;
	return size;
}

//����
void set::insert(int x)
{
	int i = 0, j = size;
	for (i; i <= size - 1;) {
		if (data[i] == x)
			return;
		if (data[i] <= x) ++i;
		if (data[i] > x) break;
	}
	if (i == size) {
		data[size++] = x;
		return;
	}
	else {
		for (j; j >= i+1; --j)
			data[j] = data[j - 1];
		data[i] = x;
		++size;
	}
}

//��һ���б���������
int set::del(int x[], int setnum)
{
	int k, cmp1, cmp2, repeat = 0, tmpoint = 0;
	int* tmp = new int[size];
	for (cmp1 = 0, cmp2 = 0; cmp1 <= size - 1;) {	
		if (cmp2 == setnum + 1) {
			tmp[tmpoint++] = data[cmp1++];
			continue;
		}
		if (data[cmp1] == x[cmp2]) {
			++cmp1;
			++repeat;
		}
		if (data[cmp1] > x[cmp2])
			++cmp2;
		if (data[cmp1] < x[cmp2]) {
			tmp[tmpoint++] = data[cmp1++];
		}
	}
	size = size - repeat;
	for (k = 0; k <= size - 1; ++k)
	data[k] = tmp[k]; 
	return size;
}

//���
void set::traverse()
{
		if (size > 0) cout << data[0];
	for (int k = 1; k <= size - 1; ++k)
		cout << ' ' << data[k];
	cout << '\n';

	//cout << "size: " << size;
}

//ð������
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
	}
}

//�б�ȥ��������
int desameandSort(int num[], int size)
{
	int i, j = 1, k, * tmp, repeat = 0;
	tmp = new int[size];
	bubbleSort(num, size);

	tmp[0] = num[0];
	for (i = 1; i <= size - 1; ) {
		if (num[i] == num[i - 1]) {
			++i;
			++repeat;
		}
		else
			tmp[j++] = num[i++];
	}
	size -= repeat;
	for (k = 0; k <= size - 1; ++k)
		num[k] = tmp[k];
	delete[]tmp;
	return size;
}

int main6()
{
	set theset;
	int opnum, i, j, k, setnum;
	char op;
	cin >> opnum;
	for (i = 0; i <= opnum - 1; ++i) {
		cin >> op >> setnum;
		int* newset = new int[setnum];
		for (j = 0; j <= setnum - 1;)
			cin >> newset[j++];

		setnum = desameandSort(newset, setnum);

		switch (op) {
		case '+': {
			for (k = 0; k <= setnum - 1;)
				theset.insert(newset[k++]);

			theset.traverse();
			break;
		}
		case '-': {
			theset.del(newset, setnum);
			theset.traverse();
			break;
		}
		case '*': {
			theset.uni(newset, setnum);
			theset.traverse();
			break;
		}
				delete[]newset;
		}
	}
	return 0;
}