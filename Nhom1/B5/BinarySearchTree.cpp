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
void init(Node*& root) {
	root = NULL;
}

//Thao tac them
Node* createNode(int x) {
	Node* p = new Node;
	p->key = x;
	p->left = p->right = NULL;
	return p;
}

void insertNodeNoRec(Node*& root, const int x) {
	Node* p = createNode(x);
	if (root == NULL) {
		root = p;
		return;
	}
	Node* q = root;
	Node* parent = NULL;

	while (q != NULL) {
		parent = q;
		if (x > q->key)
			q = q->right;
		else if (x < q->key)
			q = q->left;
		else
			return;
	}

	if (x > parent->key)
		parent->right = p;
	else
		parent->left = p;
}

void insertNodeRec(Node*& root, const int x) {
	if (root == NULL)
		root = createNode(x);
	else if (x > root->key)
		insertNodeRec(root->right, x);
	else if (x < root->key)
		insertNodeRec(root->left, x);
	else
		return;
}

//Thao tac duyet
void duyetLNR(Node* root) {
	if (root == NULL)
		return;

	duyetLNR(root->left);
	cout << root->key << " ";
	duyetLNR(root->right);
}

void duyetLRN(Node* root) {
	if (root == NULL)
		return;

	duyetLRN(root->left);
	duyetLRN(root->right);
	cout << root->key << " ";
}

void duyetNLR(Node* root) {
	if (root == NULL)
		return;
	cout << root->key << " ";
	duyetNLR(root->left);
	duyetNLR(root->right);
}

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

		cout << p->key << "\t";
		p = p->right;
	}
}

//Duyet LRN, NLR, duyet theo chieu rong

//Kiem tra tinh chat CNPTK

//Thao tac xoa dung de quy

//Thao tac kiem tra rong
bool isEmpty(Node* root) {
	return root == NULL;
}

//Thao tac xoa
void delNodeNoRec(Node*& root, int key) {
	Node* q = root;
	Node* parent = NULL;

	//Tim node q chua key can xoa
	while (q != NULL && q->key != key) {
		parent = q;
		if (key > q->key)
			q = q->right;
		else
			q = q->left;
	}

	//Khong tim thay
	if (q == NULL)
		return;

	//q la nut bac 1 hoac nut la
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

	//q la nut bac 2
	Node* temp = q->left;
	parent = NULL;
	while (temp->right != NULL) {
		parent = temp;
		temp = temp->right;
	}
		
	//Chep du lieu cua temp cho q
	q->key = temp->key;
	if (parent != NULL)
		parent->right = temp->left;
	else
		q->left = temp->left;

	temp->left = NULL;
	delete temp;
}

//Thao tac tim kiem
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

//Giai phong
void detroyTree(Node*& root) {
	while (!isEmpty(root)) {
		delNodeNoRec(root, root->key);
	}
}

int main() {
	Node* root;
	init(root);

	insertNodeRec(root, 40);
	insertNodeRec(root, 30);
	insertNodeRec(root, 10);
	insertNodeRec(root, 60);
	insertNodeRec(root, 25);

	//delNodeNoRec(root, 40);

	duyetLNRNoRec(root);

	/*Node* res = search(root, 30);
	if (res)
		cout << "\nKet qua tim: " << res->key << endl;*/

	detroyTree(root);
	duyetLNR(root);
	return 0;
}