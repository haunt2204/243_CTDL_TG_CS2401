#include <iostream>
#include <string>
#include <fstream>
using namespace std;

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

//Tim kiem
Node* search(Node* head, const float id) {
	Node* p = head;

	while (p != NULL && p->info.exp != id) {
		p = p->next;
	}

	return p;
}

//Them phan tu vao cuoi danh sach
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

//Them dau
void insertFirst(Node*& head, Term x) {
	Node* p = createNode(x);
	p->next = head;
	head = p;
}

//Them sau phan tu q
bool insertNode(Node* head, const float id, Term x) {
	Node* q = search(head, id);
	if (q == NULL)
		return false;

	Node* p = createNode(x);
	p->next = q->next;
	q->next = p;

	return true;
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

//Xoa dau
void delFirst(Node*& head) {
	if (head == NULL) {
		cout << "DS Rong!\n";
		return;
	}

	Node* p = head;
	head = head->next;

	p->next = NULL;
	delete p;
}

//Xoa cuoi
bool delLast(Node*& head) {
	if (head == NULL)
		return false;

	Node* pLast = head;
	Node* prevLast = NULL;

	while (pLast->next != NULL) {
		prevLast = pLast;
		pLast = pLast->next;
	}

	if (prevLast == NULL)
		head = NULL;
	else
		prevLast->next = NULL;

	delete pLast;

	return true;
}
//Xoa phan tu mang gia tri q mang gia tri id
bool delNode(Node*& head, const float id) {
	Node* q = head;
	Node* prevQ = NULL;

	while (q != NULL && q->info.exp != id) {
		prevQ = q;
		q = q->next;
	}

	if (q == NULL) {
		return false;
	}

	if (prevQ == NULL)
		head = head->next;
	else
		prevQ->next = q->next;

	q->next = NULL;
	delete q;

	return true;
}
//Sap xep danh sach (Interchange Sort)
void sort(Node* head) {
	if (head == NULL)
		return;

	for (Node* i = head; i->next != NULL; i = i->next) {
		for (Node* j = i->next; j != NULL; j = j->next) {
			if (j->info.exp < i->info.exp) {
				swap(i->info, j->info);
			}
		}
	}
}

//Them phan tu moi vao danh sach co thu tu
void insertOrdered(Node*& head, Term t) {
	if (head == NULL || head->info.exp < t.exp) {
		insertFirst(head, t);
		return;
	}

	Node* p = createNode(t);
	Node* q = head;

	while (q->next != NULL && q->next->info.exp >= t.exp) {
		q = q->next;
	}

	if (q->info.exp == t.exp) {
		q->info = t;
		return;
	}
	
	p->next = q->next;
	q->next = p;
}
////Ham tinh gia tri da thuc
//double f(Node* head, float x) {
//	///
//}


//Giai phong vung nho
void detroyList(Node*& head) {
	while (head != NULL) {
		delLast(head);
	}
}

int main() {
	Node* head;
	init(head);

	Term t1, t2, t3, t4;

	t1.coef = 2;
	t1.exp = 3;
	insertOrdered(head, t1);

	t2.coef = 3;
	t2.exp = 2;
	insertOrdered(head, t2);

	t3.coef = -1;
	t3.exp = 1;
	insertOrdered(head, t3);

	t4.coef = 5;
	t4.exp = 2;
	insertOrdered(head, t4);

	printList(head);

	detroyList(head);
	return 0;
}