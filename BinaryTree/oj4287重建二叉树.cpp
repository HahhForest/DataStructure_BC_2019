#include<iostream>
using namespace std;

class tree
{
	struct node
	{
		node* left;
		node* right;
		char data;
		node() :left(NULL), right(NULL) {};
		node(char item, node* L = NULL, node* R = NULL) :data(item), left(L), right(R) {};
		~node() {};
	};
	node* root;
	void postorder(node* t) const
	{
		if (t != NULL) {
			postorder(t->left);
			postorder(t->right);
			cout << t->data;
		}

		
	}

public:
	tree() :root(NULL) {}	//构造一棵空二叉树
	tree(const char item) { root = new node(item); }
	~tree() {};

	void postorder()const
	{
		if (root) {
			postorder(root);
		}
	}
	void buildTreefromlevel(char levelList[], int n);
	//由前序和中序遍历数组建树
	node* buildTreefrompreandmid(char pre[], int pl, int pr, char mid[], int ml, int mr)
	{
		if (pl > pr) return NULL;
		node* p;
		int i;
		p = new node(pre[pl]);
		int pos;
		
		for (i = pl; i <= pr; ++i)
			if (mid[i] == pre[pl])
				break;
		
		pos = i;
		p->left = buildTreefrompreandmid(pre, pl + 1, pl + pos - ml, mid, ml, pos - 1);

		p->right = buildTreefrompreandmid(pre, pl + pos - ml + 1, pr, mid, pos + 1, mr);

		return p;
	}
};


int main1()
{
	char pre[100000], mid[100000];
	cin >> pre >> mid;
	int i = 0;
	while (pre[i] != '\0') i += 1;

	tree test('#');
	test.buildTreefrompreandmid(pre, 0, i-1, mid, 0, i-1);

	test.postorder();
	return 0;
}



//void maketree(char* pre, char* mid, char* tree, int preleft, int preright, int midleft, int midright)
//{
//
//}
//
//int main()
//{
//	char pre[100000],  mid[100000], tree[100000] ;
//	cin >> pre >> mid;
//	int i = 0;
//	while(pre[i] != '\0') 
//		i += 1;
//
//
//	int prel = 0, midl = 0;
//	int prer = i, midr = i;
//
//
//	return 0;
//}