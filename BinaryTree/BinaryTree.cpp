#include "BinaryTree.h"

template <class T>
int BinaryTree<T>::size(node *t) const
{
	if (!t) return 0;
	return 1 + size(t->left) + size(t->right);
}

template<class T>
int BinaryTree<T>::height(node* t) const
{
	if (!t) return 0;
	else {
		int lt = height(t->left), rt = height(t->right);
		return 1 + ((lt > rt) ? lt : rt);
	}
}
template<class T>
void BinaryTree<T>::clear(node* t)
{
	if (t->left) clear(t->left);
	if (t->right) clear(t->right);
	delete t;
}

template<class T>
void BinaryTree<T>::createTree(T flag)
{
	linkQueue<node*> que;
	node* tmp;
	T x, ldata, rdata;

	cout << "\n输入根节点：";
	cin >> x;
	root = new node(x);
	que.enQueue(root);

	while (!que.isEmpty()) {
		tmp = que.deQueue();
		cout << "\n分别输入" << tmp->data
			<< "的左右子(" << flag
			<< "表示空结点)：";
		cin >> ldata >> rdata;
		if (ldata != flag)
			que.enQueue(tmp->left = new node(ldata));	
		if (rdata != flag)
			que.enQueue(tmp->right = new node(rdata));
	}
	cout << "创建成功！\n" ;
}

template<class T>
void BinaryTree<T>::preOrder(node* t) const
{
	if (t != NULL) {
		cout << t->data << ' ';
		preOrder(t->left);
		preOrder(t->right);
	}
}

template<class T>
void BinaryTree<T>::midOrder(node* t) const
{
	if (t != NULL) {
		midOrder(t->left);
		cout << t->data << ' ';
		midOrder(t->right);
	}
}

template<class T>
void BinaryTree<T>::postOrder(node* t) const
{
	if (t != NULL) {
		postOrder(t->left);
		postOrder(t->right);
		cout << t->data << ' ';
	}
}

template<class T>
void BinaryTree<T>::preOrder2() const
{
	linkStack<node*> s;
	node* current;

	cout << "前序遍历：";
	s.push(root);
	while (!s.isEmpty()) {
		current = s.pop();
		cout << current->data<<' ';
		if (current->right) s.push(current->right);
		if (current->left) s.push(current->left);
	}
}
template<class T>
void BinaryTree<T>::midOrder2() const
{
	linkStack<stnode> s;
	stnode current(root);

	cout << "中序遍历：";
	s.push(current);

	while (!s.isEmpty()) {
		current = s.pop();
		if (++current.popTimes == 2) {
			cout << (current.Node)->data<<' ';
			if ((current.Node)->right)
				s.push(stnode((current.Node)->right));
		}
		else {
			s.push(current);
			if ((current.Node)->left)
				s.push(stnode((current.Node)->left));
		}
	}
}

template<class T>
void BinaryTree<T>::postOrder2() const
{
	linkStack<stnode> s;
	stnode current(root);

	cout << "后序遍历：";
	s.push(current);

	while (!s.isEmpty()) {
		current = s.pop();
		if (++current.popTimes == 3) {
			cout << (current.Node)->data << ' ';
			continue;
		}
		s.push(current);
		if (current.popTimes == 1) {
			if ((current.Node)->left)
				s.push(stnode((current.Node)->left));
		}
		else {
			if ((current.Node)->right)
				s.push(stnode((current.Node)->right));
		}
	}
}

template<class T>
void BinaryTree<T>::buildTreefromlevel(T levelList[], int n)
{
	if (n < 1) return;
	node* p;
	int index;
	linkQueue<node*> q1;
	linkQueue<int> q2;

	root = new node(levelList[1]);
	q1.enQueue(root);
	q2.enQueue(1);

	while (!q1.isEmpty()) {
		p = q1.deQueue();
		index = q2.deQueue();

		if (index * 2 <= n) {	//说明此节点的左子存在
			p->left = new node(levelList[2 * index]);
			q1.enQueue(p->left);
			q2.enQueue(2 * index);
		}

		if (index * 2 + 1 <= n) {
			p->right = new node(levelList[index * 2 + 1]);
			q1.enQueue(p->right);
			q2.enQueue(index * 2 + 1);
		}
	}
}


