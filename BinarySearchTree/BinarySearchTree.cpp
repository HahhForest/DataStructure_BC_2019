#include "BinarySearchTree.h"

//����Ȼ򱾽ڵ�Ϊ�գ����ر��ڵ㣨Ϊ�ձ�ʾû�ҵ���
//���򣬷��������������ݹ�
template<class KEY, class OTHER>
SET<KEY, OTHER>* BinarySearchTree<KEY, OTHER>::find(const KEY& x, BinaryNode* t) const
{
	if (t == NULL || t->data.key == x)
		return &(t->data);

	if (x < t->data.key)
		return find(x, t->left);
	else
		return find(x, t->right);
}

//����ڵ�����Ҷ�ӽڵ�
//�ڶ�������Ϊһ��ָ��ڵ�ķǲ�������
//���²���ڵ����丸�ڵ����������������һ�£������������޷�ʵ�ֹ��ܣ�
//��û�����ã��²���ڵ㽫��֪���丸�ڵ���˭
template<class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::insert(const SET<KEY, OTHER>& x, BinaryNode*& t)
{
	if (t == NULL)
		t = new BinaryNode(x, NULL, NULL);
	else if (x.key < t->data.key)
		insert(x, t->left);
	else if (x.key > t->data.key)
		insert(x, t->right);
}

template<class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::insert2(const SET<KEY, OTHER>& x, BinaryNode*& t)
{
	BinaryNode* p = root, parent = NULL;
	int flag = 0;

	//����ʱparentָ�򸸽ڵ㣬 p=NULL�� flagָʾ����
	while (p) {
		if (p->data.key == x.key) return;
		if (p->data.key < x.key) {
			parent = p; p = p->left;
			flag = 0;
		}
		else {
			parent = p; p = p->right;
			flag = 1;
		}
	}

	BinaryNode* tmp = new BinaryNode(x);
	if (!parent) {
		root = tmp;
		return;
	}

	if (flag == 0) parent->left = tmp;
	else
		parent->right = tmp;
}

//��ɾ��Ҷ�ڵ㣬ֱ��ɾ�����ڵ���Ӧָ����Ϊ0
//��ֻ��һ���ӽڵ㣬���ӽڵ����ӵ��丸�ڵ��ϣ�������ṹ
//���������ӽڵ㣬ѡ�����������Ļ�����������С��Ϊ����
template <class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER> ::remove(const KEY& x, BinaryNode*& t)
{
	if (t == NULL) return;

	if (x < t->data.key) remove(x, t->left);
	else if (x > t->data.key) remove(x, t->right);

	else if (t->left != NULL && t->right != NULL) {	//ɾ�����ڵ�-���������ӽڵ�
		BinaryNode* tmp = t->right;
		while (tmp->left != NULL) tmp = tmp->left;	//�ҵ���������Сֵ
		t->data = tmp->data;
		remove(t->data.key, t->right);
	}

	else {
		BinaryNode* tt =  t;
		t = (t->left != NULL) ? t->left : t->right;
		delete  tt;
	}
}

template<class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::makeEmpty(BinaryNode* t)
{
	if (t->left) makeEmpty(t->left);
	if (t->right) makeEmpty(t->right);
	delete t;
}