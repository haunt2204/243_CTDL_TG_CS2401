#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//Khai bao cau truc
template <typename T>
struct Node {
	//Vung thong tin
	T info;

	//Vung lien ket
	Node* next;
};

//Khoi tao rong
template <typename T>
void init(Node<T>*& head) {
	head = NULL;
}
//Tao node moi
template <typename T>
Node<T>* createNode(T x) {
	Node<T>* p = new Node<T>;
	p->info = x;
	p->next = NULL;
	return p;
}

//Them phan tu vao dau, cuoi danh sach
template <typename T>
void insertFirst(Node<T>*& head, T x) {
	Node<T>* p = createNode(x);
	p->next = head;
	head = p;
}

template <typename T>
void insertLast(Node<T>*& head, T x) {
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

//Xoa phan tu trong DSLK
template <typename T>
bool delFirst(Node<T>*& head) {
	if (head == NULL)
		return false;
	Node<T>* p = head;
	head = head->next;
	p->next = nullptr;
	delete p;
}

template <typename T>
bool delLast(Node<T>*& head) {
	if (head == NULL)
		return false;
	Node<T>* q = head;
	Node<T>* prevQ = NULL;
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

//Giai phong danh sach
template <typename T>
void detroyList(Node<T>*& head) {
	while (head != NULL) {
		delFirst(head);
	}
}

//Truy xuat phan tu thu i
template <typename T>
Node<T>* getNodeAt(Node<T>*& head, int index) {
	Node<T>* p = head;
	int i = 0;

	while (p != NULL && i < index) {
		p = p->next;
		i++;
	}

	return p;
}

//Duyet danh sach
template <typename T>
void printList(Node<T>* head) {
	if (head == NULL) {
		cout << "Danh sach rong!\n";
		return;
	}

	Node<T>* tmp = head;
	while (tmp != NULL) {
		cout << tmp->info;
		tmp = tmp->next;
	}

}

//Sap xep
template <typename T>
void sort(Node<T>* head, bool comparator(T, T)) {
	if (head != NULL) {
		for (Node<T>* i = head; i->next != NULL; i = i->next) {
			for (Node<T>* j = i->next; j != NULL; j = j->next) {
				if (comparator(j->info, i->info))
					swap(i->info, j->info);
			}
		}
	}
}