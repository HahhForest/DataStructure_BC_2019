#include "BinarySearchTree.h"

//若相等或本节点为空，返回本节点（为空表示没找到）
//否则，分流给左右子树递归
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

//被插节点总是叶子节点
//第二个参数为一个指向节点的非参数引用
//将新插入节点与其父节点关联起来（可以推一下，若不是引用无法实现功能）
//若没有引用，新插入节点将不知道其父节点是谁
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

	//结束时parent指向父节点， p=NULL， flag指示左右
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

//若删除叶节点，直接删，父节点相应指针置为0
//若只有一个子节点，其子节点代替接到其父节点上，仍满足结构
//若有两个子节点，选左子树中最大的或右子树中最小的为替身
template <class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER> ::remove(const KEY& x, BinaryNode*& t)
{
	if (t == NULL) return;

	if (x < t->data.key) remove(x, t->left);
	else if (x > t->data.key) remove(x, t->right);

	else if (t->left != NULL && t->right != NULL) {	//删除根节点-》有两个子节点
		BinaryNode* tmp = t->right;
		while (tmp->left != NULL) tmp = tmp->left;	//找到右子树最小值
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