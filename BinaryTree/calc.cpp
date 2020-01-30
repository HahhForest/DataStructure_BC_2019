//#include "calc.h"
//
//calc::node *calc:: create( char *&s)
//{
//	calc::node *p, * root = NULL;
//	Type returnType;
//	int value;
//
//	while (*s) {
//		returnType = calc::getToken(s, value);
//
//		switch (returnType) {
//			case DATA: case OPAREN:
//				if (returnType == DATA)
//					p = new calc::node(DATA, value);
//				else p = create(s);
//
//				if (root != NULL)
//					if (root->rchild == NULL) root->rchild = p;
//					else root->rchild->rchild = p;
//
//			case CPAREN: case EOL: return root;
//			case ADD: case SUB:
//				if (root == NULL) {
//					p = new node(returnType, 0);
//					root = new node(returnType, 0, p);
//				}
//				else root = new node(returnType, 0, root);
//				break;
//			case MULTI: case DIV:
//				if (root = NULL) {
//					p = new node(returnType, 0);
//					root = new node(returnType, 0, p);
//				}
//				else if (root->type == MULTI || root->type == DIV)
//					root = new node(returnType, 0, root);
//				else root->rchild = new node(returnType, 0, root->rchild);
//		}
//	}
//	return root;
//}
//
//calc::Type calc::getToken(char*& s, int& data)
//{
//	char type;
//
//	while (*s == ' ') ++s;		//跳过空格
//
//	if (*s >= '0' && *s <= '9') {	//遇到运算数
//		data = 0;
//		while (*s >= '0' && *s <= '9') {
//			data = data * 10 + *s - '0';
//			++s;
//		}
//		return DATA;
//	}
//	if (*s == '\0') return EOL;
//	
//	type = *s; ++s;
//	switch (type) {
//	case'+': return ADD;
//	case'-': return SUB;
//	case'*': return MULTI;
//	case'/': return DIV;
//	case'(': return OPAREN;
//	case')': return CPAREN;
//	default: return EOL;
//	}
//
//}
//
//int calc::result(calc::node* t)
//{
//	int num1, num2;
//
//	if (t->type == DATA) return t->data;
//	num1 = result(t->lchild);
//	num2 = result(t->rchild);
//	switch (t->type) {
//	case ADD: t->data = num1 + num2; break;
//	case SUB: t->data = num1 - num2; break;
//	case MULTI: t->data = num1 * num2; break;
//	case DIV: t->data = num1 / num2; 
//	}
//	return t->data;
//}
//
////int main3()
////{
////	calc exp("2*3+(1 * 2*3+6*6) * (2+3)/5 + 2/2");
////	cout << exp.result() << endl;
////	return 0;
////
////}