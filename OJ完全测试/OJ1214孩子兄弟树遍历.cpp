#include<iostream>
using namespace std;
#include "../linkQueue/linkQueue.cpp"

//定义树
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
	void create();	//针对此题的输入
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

	//创建树，flag表示空
	cout << "\n输入根节点：";
	cin >> x;
	root = new node(x);
	q.enQueue(root);

	while (!q.isEmpty()) {
		tmp = q.deQueue();
		cout << "\n输入 " << tmp->data << " 的所有儿子：";
		cin >> son;
		if (son == flag)
			continue;
		tmp->son = new node(son);
		tmp = tmp->son;
		q.enQueue(tmp);	//第一个儿子入队，所有兄弟都接在它的上面
		while (true) {
			cin >> son;
			if (son == flag)
				break;
			tmp->brother = new node(son);
			tmp = tmp->brother;
			q.enQueue(tmp);
		}
	}
	cout << "建树成功\n";
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

	//寻找根节点
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

	//确定根节点为第一个节点
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
		q.enQueue(tmp);	//第一个儿子入队
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

//私有前序遍历
template<class T>
void tree<T>::preOrder(node* t)
{
	//判断递归条件
	if (t == NULL) {
		return;
	}

	//访问当前节点
	cout << t->data<<' ';	

	//遍历访问所有子
	node* p = t->son;
	while (p != NULL) {
		preOrder(p);
		p = p->brother;
	}
}

//私有后续遍历
template<class T>
void tree<T>::postOrder(node* t)
{
	//递归终止条件
	if (t == NULL) {
		return;
	}

	//递归访问所有子
	node* p = t->son;
	while (p != NULL) {
		postOrder(p);
		p = p->brother;
	}

	//最后访问自己
	cout << t->data << ' ';
}

//层次遍历：使用一个队列为工具
//根节点首先入队，然后重复取出节点，访问元素，儿子入队
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