#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//Khai bao cau truc
struct Node
{
	int info;
	Node* next;
};

struct CircularLinkedList
{
	Node* head, * tail;
};

//Khoi tao rong
void init(CircularLinkedList& l) {
	l.head = l.tail = NULL;
}

//Them dau
Node* createNode(int x) {
	Node* p = new Node;
	p->info = x;
	p->next = NULL;

	return p;
}

void insertFirst(CircularLinkedList& l, int x) {
	Node* p = createNode(x);

	if (l.head == NULL) {
		l.head = l.tail = p;
		p->next = l.head;
	}
	else {
		p->next = l.head;
		l.head = p;
		l.tail->next = l.head;
	}
}

//Duyet 
void printList(CircularLinkedList l) {
	if (l.head == NULL) {
		cout << "DS rong!\n";
		return;
	}
	Node* p = l.head;
	while (p->next != l.head) {
		cout << p->info << " ";
		p = p->next;
	}
	cout << p->info << endl;
}

//Xoa
void delFirst(CircularLinkedList& l) {
	if (l.head == NULL) {
		return;
	}

	Node* p = l.head;
	l.head = l.head->next;

	if (l.head == p) {
		l.head = l.tail = NULL;
	}
	else {
		l.tail->next = l.head;
	}

	p->next = NULL;
	delete p;
}

//Giai phong
void detroyList(CircularLinkedList& l) {
	while (l.head != NULL) {
		delFirst(l);
	}
}

int main() {
	CircularLinkedList l;
	init(l);

	insertFirst(l, 15);
	insertFirst(l, 10);
	insertFirst(l, 9);
	insertFirst(l, 45);
	insertFirst(l, 21);

	printList(l);

	detroyList(l);
	return 0;
}
