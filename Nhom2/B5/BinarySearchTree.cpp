#include <iostream>
#include <stack>
using namespace std;

//Khai bao cau truc
struct Node
{
	int key;
	Node* left, * right;
};

//Khoi tao rong
void treeEmpty(Node*& root) {
	root = NULL;
}
//Them phan tu vao cay: khong dung de quy
Node* createNode(int x) {
	Node* p = new Node;
	p->key = x;
	p->left = p->right = NULL;

	return p;
}

void insertNode(Node*& root, int key) {
	if (root == NULL) {
		root = createNode(key);
		return;
	}

	Node* q = root;
	Node* parent = NULL;

	while (q != NULL) {
		parent = q;

		if (key > q->key)
			q = q->right;
		else if (key < q->key)
			q = q->left;
		else {
			cout << "Khoa da ton tai!\n";
			return;
		}
	}

	if (key > parent->key)
		parent->right = createNode(key);
	else
		parent->left = createNode(key);
}

//Them vao cay dung de quy
void insertNodeRec(Node*& root, const int key) {
	if (root == NULL)
		root = createNode(key);
	else if (key > root->key)
		insertNodeRec(root->right, key);
	else if (key < root->key)
		insertNodeRec(root->left, key);
	else
		return;
}

//Thao tac duyet cay: LNR, LRN, NLR (dung de quy)
void duyetLNR(Node* root) {
	if (root == NULL) {
		return;
	}

	duyetLNR(root->left);
	cout << root->key << " ";
	duyetLNR(root->right);
}

//Duyet cay khong dung de quy
void duyetLNRNoRec(Node* root) {
	stack<Node*> s;

	Node* p = root;

	while (p != NULL || !s.empty()) {
		while (p != NULL) {
			s.push(p);
			p = p->left;
		}

		p = s.top();
		s.pop();

		cout << p->key << " ";
		p = p->right;
	}

}

////SV tu cai dat:
//Duyet khong de quy: LRN, NLR

//Duyet cay theo chieu rong

//Kiem tra tinh chat CNPTK

//Thao tac xoa dung de quy

//Thao tac tim kiem 1 phan tu trong cay
Node* search(Node* root, int key) {
	Node* q = root;

	while (q != NULL && q->key != key) {
		if (key > q->key)
			q = q->right;
		else
			q = q->left;
	}

	return q;
}
//Thao tac xoa (khong de quy)
void delNode(Node*& root, int key) {
	Node* q = root;
	Node* parent = NULL;

	while (q != NULL && q->key != key) {
		parent = q;

		if (key > q->key)
			q = q->right;
		else
			q = q->left;
	}

	//Tim khong thay
	if (q == NULL)
		return;

	//Node can xoa la nut la hoac nut bac 1
	if (q->left == NULL || q->right == NULL) {
		Node* temp = q->left != NULL ? q->left : q->right;

		if (q == root)
			root = temp;
		else if (key > parent->key)
			parent->right = temp;
		else
			parent->left = temp;

		delete q;
		return;
	}
	//Xoa nut cha bac 2
	Node* temp = q->left;
	parent = NULL;

	while (temp->right != NULL) {
		parent = temp;
		temp = temp->right;
	}

	//Chep du lieu cua nut the mang cho q
	q->key = temp->key;
	
	//Dieu chinh lien ket
	if (parent != NULL)
		parent->right = temp->left;
	else
		q->left = temp->left;

	//Xoa nut the mang
	temp->left = NULL;
	delete temp;
}

bool isEmpty(Node* root) {
	return root == NULL;
}

void detroyTree(Node*& root) {
	while (!isEmpty(root)) {
		delNode(root, root->key);
	}
}

int main() {
	Node* root;
	treeEmpty(root);

	insertNodeRec(root, 40);
	insertNodeRec(root, 50);
	insertNodeRec(root, 30);
	insertNodeRec(root, 60);
	insertNodeRec(root, 45);

	duyetLNRNoRec(root);

	cout << "\n=========TIM KIEM===========\n";
	Node* res = search(root, 60);
	if (res)
		cout << res->key << endl;
	else
		cout << "Khong tim thay!\n";

	cout << "\n=========XOA===========\n";
	delNode(root, 40);
	duyetLNR(root);

	detroyTree(root);
	duyetLNR(root);
	return 0;
}