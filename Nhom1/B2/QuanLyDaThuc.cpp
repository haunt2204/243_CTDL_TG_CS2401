#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#define MAX 20

struct Term
{
	float coef;//He so
	float exp;//Bac
};

void nhap1Term(Term& t) {
	cout << "Nhap he so: ";
	cin >> t.coef;
	cout << "Nhap bac: ";
	cin >> t.exp;
}

void xuat1Term(Term t) {
	cout << t.coef << "x^" << t.exp;
}

//Khai bao cau truc
struct Node {
	//Vung thong tin
	Term info;

	//Vung lien ket
	Node* next;
};

//Khoi tao rong
void init(Node*& head) {
	head = NULL;
}
//Tao node moi
Node* createNode(Term x) {
	Node* p = new Node;
	p->info = x;
	p->next = NULL;
	return p;
}

//Thao tac tim kiem
Node* search(Node* head, int id) {
	Node* p = head;
	while (p != NULL && p->info.exp != id) {
		p = p->next;
	}
	return p;
}

//Them phan tu vao dau, cuoi danh sach
void insertFirst(Node*& head, Term x) {
	Node* p = createNode(x);
	p->next = head;
	head = p;
}
void insertLast(Node*& head, Term x) {
	//Tao node moi
	Node* p = createNode(x);

	///
	if (head == NULL) {
		head = p;
	}
	else {
		Node* tmp = head;

		while (tmp->next != NULL) {
			tmp = tmp->next;
		}

		tmp->next = p;
	}

}

void insertAfter(Node* head, const int key, const Term x) {
	Node* q = search(head, key);
	if (q != NULL) {
		Node* p = createNode(x);
		p->next = q->next;
		q->next = p;
	}
}

void insertOrdered(Node*& head, Term x) {
	if (head == NULL || head->info.exp < x.exp) {
		insertFirst(head, x);
		return;
	}

	Node* p = createNode(x);
	Node* q = head;

	while (q->next != NULL && q->next->info.exp > x.exp) {
		q = q->next;
	}

	if (q->info.exp == x.exp) {
		q->info.coef = x.coef;
		return;
	}

	p->next = q->next;
	q->next = p;
}


//Duyet danh sach
void printList(Node* head) {
	if (head == NULL) {
		cout << "Danh sach rong!\n";
		return;
	}

	Node* tmp = head;
	cout << "f(x) = ";
	while (tmp != NULL) {
		xuat1Term(tmp->info);
		if(tmp->next!=NULL)
			cout << " + ";
		tmp = tmp->next;
	}

}

//Xoa phan tu trong DSLK
bool delFirst(Node*& head) {
	if (head == NULL)
		return false;
	Node* p = head;
	head = head->next;
	p->next = nullptr;
	delete p;
}

bool delLast(Node*& head) {
	if (head == NULL)
		return false;
	Node* q = head;
	Node* prevQ = NULL;
	while (q->next != NULL) {
		prevQ = q;
		q = q->next;
	}
	if (prevQ == NULL) {
		head = NULL;
	}
	else
		prevQ->next = NULL;

	delete q;
}

bool delNode(Node*& head, const int key) {
	Node* q = head;
	Node* qPrev = NULL;

	while (q != NULL && q->info.exp != key) {
		qPrev = q;
		q = q->next;
	}

	if (q == NULL)
		return false;

	if (qPrev == NULL) {
		head = head->next;
	}
	else
		qPrev->next = q->next;

	q->next = NULL;
	delete q;
	return true;
}

//Giai phong danh sach
void detroyList(Node*& head) {
	while (head != NULL) {
		delFirst(head);
	}
}

//Truy xuat phan tu thu i
Node* getNodeAt(Node*& head, int index) {
	Node* p = head;
	int i = 0;

	while (p != NULL && i < index) {
		p = p->next;
		i++;
	}

	return p;
}

//Sap xep
void sort(Node* head) {
	if (head != NULL) {
		for (Node* i = head; i->next != NULL; i = i->next) {
			for (Node* j = i->next; j != NULL; j = j->next) {
				if (j->info.exp < i->info.exp)
					swap(i->info, j->info);
			}
		}
	}
}

int main() {
	Node* head;
	init(head);

	Term t1, t2;

	t1.coef = 2;
	t1.exp = 2;
	insertOrdered(head, t1);

	t2.coef = 2;
	t2.exp = 3;
	insertOrdered(head, t2);

	printList(head);

	detroyList(head);
	return 0;
}