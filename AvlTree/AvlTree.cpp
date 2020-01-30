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
	AvlNode* t1 = t->left;	//指向危机节点的左子节点，即未来的根节点
	t->left = t1->right;
	t1->right = t;
	t->height = max(height(t->left), height(t->right)) + 1;
	t1->height = max(height(t1->left), height(t)) + 1;
	t = t1;
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::RR(AvlNode*& t)
{
	AvlNode* t1 = t->right;		//指向危机节点的右子节点，即未来的根节点
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
	if (t == NULL)	//在空树上插入，此时新插入的就是根节点
		t = new AvlNode(x, NULL, NULL);

	else if (x.key < t->left.key) {	//小于根节点的key，递归在左子树上插入
		insert(x, t->left);
		if (height(t->left) - height(t->right) == 2) 	//t失衡，此时t为危机节点
			if (x.key < t->left->data.key) LL(t);	//插入在t左子的左子树上，对应LL型
			else LR(t);	//插入在t左子的右子树上，对应RR型
	}

	else if (x.key > t->left.key) {	//小于根节点的key，递归在右子树上插入
		insert(x, t->right);
		if (height(t->right) - height(t->left) == 2)	//t失衡，此时t为危机节点
			if (x.key > t->right->data.key) RR(t);//插入在t右子的右子树上，对应RR型
		else RL(t);	//插入在t左子的右子树上，对应RL型
	}

	//重新计算t的高度
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
	
	if (x == t->data.key) {	//删除根节点

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

	if (x < t->data.key) {	//在左子树上删除
		if (remove(x, t->left)) return true;
		return adjust(t, 0);
	}

	else {	//在右子树上删除
		if (remov(x, t->right)) return true;
		return adjust(t, 1);
	}
}

template <class KEY, class OTHER>
bool AvlTree<KEY, OTHER>::adjust(AvlNode*& t, int subTree)
{
	if (subTree) {                           //  在右子树上删除，使右子树变矮
		if (height(t->left) - height(t->right) == 1) return true;            // 情况a
		if (height(t->right) == height(t->left)) { --t->height; return false; } // 情况b
		if (height(t->left->right) > height(t->left->left))                 // 情况d
		{
			LR(t);	return false;
		}
		LL(t);
		if (height(t->right) == height(t->left)) return false; else return true;
	}
	else {      // 在左子树删除
		if (height(t->right) - height(t->left) == 1) return true;             // 情况a
		if (height(t->right) == height(t->left)) { --t->height; return false; } // 情况b
		if (height(t->right->left) > height(t->right->right))               // 情况d
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
