#include <iostream>
#include <string>

//已知二叉树前序和中序遍历，求顺序
using namespace std;

struct binode
{
	char ver;
	binode* left;
	binode* right;
	binode():ver(0), left(nullptr), right(nullptr) {};
	binode(char v) : ver(v), left(nullptr), right(nullptr) {};
};


void SaveTree(binode* root, int* al, int pos)
{
	al[pos] = root->ver - 'A' + 1;
	if (root->left != nullptr)
		SaveTree(root->left, al, pos * 2);
	if (root->right != nullptr)
		SaveTree(root->right, al, pos * 2 + 1);
}

binode* init(string s1, string s2)
{
	binode* current = new binode(s1[0]);
	int num = 0;
	for (; num < s2.length(); num++)
		if (s1[0] == s2[num]) break;
	if (num < s2.length() - 1)
		current->right = init(s1.substr(num + 1, s1.length() - num - 1), s2.substr(num + 1, s2.length() - num - 1));
	if (num > 0)
		current->left = init(s1.substr(1, num), s2.substr(0, num));
	return current;
}

int main19()
{
	string s1, s2;
	cin >> s1 >> s2;
	binode* root = init(s1, s2);
	int al[1005];
	for (int i = 0; i < 1005; i++) al[i] = 0;
	SaveTree(root, al, 1);
	int tail = 1004;
	for (; tail >= 0; tail--)
		if (al[tail]) break;
	for (int i = 1; i <= tail; i++)
	{
		if (al[i])
			cout << char(al[i] - 1 + 'A') << " ";
		else
			cout << "NULL ";
	}
	cout << endl;
	return 0;
}