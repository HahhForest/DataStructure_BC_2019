#include<iostream>
using namespace std;
#include "../linkQueue/linkQueue.cpp"

//������
template <class T>
class tree
{
	struct node {
		T data;
		node* son, * brother;
		node(T d, node* s = NULL, node* b = NULL) {
			data = d;
			son = s;
			brother = b;
		}
		node() {};
	};
	node* root;

public:
	tree(node* t = NULL) { root = t; }
	void createTree(T flag);
	void create();	//��Դ��������
	void preOrder() { preOrder(root); }
	void postOrder() { postOrder(root); }
	void levelOrder();

private:
	void preOrder(node *t);
	void postOrder(node *t);
};

template <class T>
void tree<T>::createTree(T flag)
{
	linkQueue<node*> q;
	node* tmp;
	T x, son;

	//��������flag��ʾ��
	cout << "\n������ڵ㣺";
	cin >> x;
	root = new node(x);
	q.enQueue(root);

	while (!q.isEmpty()) {
		tmp = q.deQueue();
		cout << "\n���� " << tmp->data << " �����ж��ӣ�";
		cin >> son;
		if (son == flag)
			continue;
		tmp->son = new node(son);
		tmp = tmp->son;
		q.enQueue(tmp);	//��һ��������ӣ������ֵܶ�������������
		while (true) {
			cin >> son;
			if (son == flag)
				break;
			tmp->brother = new node(son);
			tmp = tmp->brother;
			q.enQueue(tmp);
		}
	}
	cout << "�����ɹ�\n";
}


template<class T>
void tree<T>::create()
{
	linkQueue<node*> q;
	int n, l, r, son, g;
	int i, t;
	cin >> n;
	T* weight = new T[n+5];
	int* left = new int[n+5];
	int* right = new int[n+5];
	T w;
	node* tmp;

	for (i = 1; i <= n; ++i) {
		cin >> l >> r >> w;
		left[i] = l;	right[i] = r;	weight[i] = w;
	}

	//Ѱ�Ҹ��ڵ�
	int* gen = new int[n + 5];
	for (i = 1; i <= n; ++i)
		gen[i] = 0;
	for (i = 1; i <= n; ++i) {
		gen[left[i]] = 1;
		gen[right[i]] = 1;
	}
	for (g = 1; g <= n; ++g)
		if (gen[g] == 0)
			break;

	//ȷ�����ڵ�Ϊ��һ���ڵ�
	root = new node(weight[g]);
	q.enQueue(root);

	while (!q.isEmpty()) {
		tmp = q.deQueue();
		for (i = 1; i <= n; ++i)
			if (weight[i] == tmp->data)
				break;
		son = left[i];
		if (son == 0)
			continue;
		tmp->son = new node(weight[son]);
		tmp = tmp->son;
		q.enQueue(tmp);	//��һ���������
		while (true) {
			son = right[son];
			if (son == 0)
				break;
			tmp->brother = new node(weight[son]);
			tmp = tmp->brother;
			q.enQueue(tmp);
		}
	}
	delete[]weight;
	delete[]left;
	delete[]right;
	delete[]gen;
}

//˽��ǰ�����
template<class T>
void tree<T>::preOrder(node* t)
{
	//�жϵݹ�����
	if (t == NULL) {
		return;
	}

	//���ʵ�ǰ�ڵ�
	cout << t->data<<' ';	

	//��������������
	node* p = t->son;
	while (p != NULL) {
		preOrder(p);
		p = p->brother;
	}
}

//˽�к�������
template<class T>
void tree<T>::postOrder(node* t)
{
	//�ݹ���ֹ����
	if (t == NULL) {
		return;
	}

	//�ݹ����������
	node* p = t->son;
	while (p != NULL) {
		postOrder(p);
		p = p->brother;
	}

	//�������Լ�
	cout << t->data << ' ';
}

//��α�����ʹ��һ������Ϊ����
//���ڵ�������ӣ�Ȼ���ظ�ȡ���ڵ㣬����Ԫ�أ��������
template<class T>
void tree<T>::levelOrder()
{
	linkQueue<node*> q;
	node* tmp;

	if (root == NULL)
		return;

	q.enQueue(root);
	while (!q.isEmpty()) {
		tmp = q.deQueue();
		cout << tmp->data << ' ';
		tmp = tmp->son;
		while (tmp != NULL) {
			q.enQueue(tmp);
			tmp = tmp->brother;
		}
	}
}

int main19()
{
	tree<long long int> test;
	test.create();
	//test.createTree(0);

	test.preOrder();
	cout << endl;
	test.postOrder();
	cout << endl;
	test.levelOrder();

	return 0;
}