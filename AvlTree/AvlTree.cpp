# include "AvlTree.h"

template<class KEY, class OTHER>
SET<KEY, OTHER>* AvlTree<KEY, OTHER>::find(const KEY& x) const
{
	AvlNode* t = root;

	while (t && t->data.key != x)
		if (t->data.key > x) t = t->left;
		else t = t->right;
	if (t == NULL) return NULL;
	else return (SET<KEY, OTHER> * t);
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::LL(AvlNode*& t)
{
	AvlNode* t1 = t->left;	//ָ��Σ���ڵ�����ӽڵ㣬��δ���ĸ��ڵ�
	t->left = t1->right;
	t1->right = t;
	t->height = max(height(t->left), height(t->right)) + 1;
	t1->height = max(height(t1->left), height(t)) + 1;
	t = t1;
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::RR(AvlNode*& t)
{
	AvlNode* t1 = t->right;		//ָ��Σ���ڵ�����ӽڵ㣬��δ���ĸ��ڵ�
	t->right = t1->left;
	t1->left = t;
	t->height = max(height(t->left), height(t->right)) + 1;
	t1->height = max(height(t1->right), height(t)) + 1;
	t = t1;
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::LR(AvlNode*& t)
{
	RR(t->left);
	LL(t);
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::RL(AvlNode*& t)
{
	LL(t->right);
	RR(t);
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::insert(const SET<KEY, OTHER>& x)
{
	insert(x, root);
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::insert(const SET<KEY, OTHER>& x, AvlTree*& t)
{
	if (t == NULL)	//�ڿ����ϲ��룬��ʱ�²���ľ��Ǹ��ڵ�
		t = new AvlNode(x, NULL, NULL);

	else if (x.key < t->left.key) {	//С�ڸ��ڵ��key���ݹ����������ϲ���
		insert(x, t->left);
		if (height(t->left) - height(t->right) == 2) 	//tʧ�⣬��ʱtΪΣ���ڵ�
			if (x.key < t->left->data.key) LL(t);	//������t���ӵ��������ϣ���ӦLL��
			else LR(t);	//������t���ӵ��������ϣ���ӦRR��
	}

	else if (x.key > t->left.key) {	//С�ڸ��ڵ��key���ݹ����������ϲ���
		insert(x, t->right);
		if (height(t->right) - height(t->left) == 2)	//tʧ�⣬��ʱtΪΣ���ڵ�
			if (x.key > t->right->data.key) RR(t);//������t���ӵ��������ϣ���ӦRR��
		else RL(t);	//������t���ӵ��������ϣ���ӦRL��
	}

	//���¼���t�ĸ߶�
	t->height = max(height(t->left), height(t->right)) + 1;
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::remove(const KEY& x)
{
	remove(x, root);
}

template<class KEY, class OTHER>
bool AvlTree<KEY, OTHER>::remove(const KEY& x, AvlNode*& t)
{
	if (t == NULL) return true;
	
	if (x == t->data.key) {	//ɾ�����ڵ�

		if (t->left == NULL || t->right == NULL) {
			AvlNode* oldNode = t;
			t = (t->left != NULL) ? t->left : t->right;
			delete oldNode;
			return false;
		}

		else {
			AvlNode* tmp = t->right;
			while (tmp->left != NULL) tmp = tmp->left;
			t->data = tmp->data;
			if (remove(tmp->data.key, t->right)) return true;
			return adjust(t, 1);
		}
	}

	if (x < t->data.key) {	//����������ɾ��
		if (remove(x, t->left)) return true;
		return adjust(t, 0);
	}

	else {	//����������ɾ��
		if (remov(x, t->right)) return true;
		return adjust(t, 1);
	}
}

template <class KEY, class OTHER>
bool AvlTree<KEY, OTHER>::adjust(AvlNode*& t, int subTree)
{
	if (subTree) {                           //  ����������ɾ����ʹ�������䰫
		if (height(t->left) - height(t->right) == 1) return true;            // ���a
		if (height(t->right) == height(t->left)) { --t->height; return false; } // ���b
		if (height(t->left->right) > height(t->left->left))                 // ���d
		{
			LR(t);	return false;
		}
		LL(t);
		if (height(t->right) == height(t->left)) return false; else return true;
	}
	else {      // ��������ɾ��
		if (height(t->right) - height(t->left) == 1) return true;             // ���a
		if (height(t->right) == height(t->left)) { --t->height; return false; } // ���b
		if (height(t->right->left) > height(t->right->right))               // ���d
		{
			RL(t);	return false;
		}
		RR(t);
		if (height(t->right) == height(t->left)) return false; else return true;
	}
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::makeEmpty(AvlNode* t)
{
	if (t->left) makeEmpty(t->left);
	if (t->right) makeEmpty(t->right);
	delete t;
}
