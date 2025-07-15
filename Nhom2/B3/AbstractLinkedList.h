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
	Node<T>* next;
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


//Them phan tu vao cuoi danh sach
template <typename T>
void insertLast(Node<T>*& head, T x) {
	//Tao node moi
	Node<T>* p = createNode(x);

	if (head == NULL) {
		head = p;
	}
	else {
		Node<T>* tmp = head;

		while (tmp->next != NULL) {
			tmp = tmp->next;
		}

		tmp->next = p;
	}

}

//Them dau
template <typename T>
void insertFirst(Node<T>*& head, T x) {
	Node<T>* p = createNode(x);
	p->next = head;
	head = p;
}

//Xoa dau
template <typename T>
void delFirst(Node<T>*& head) {
	if (head == NULL) {
		cout << "DS Rong!\n";
		return;
	}

	Node<T>* p = head;
	head = head->next;

	p->next = NULL;
	delete p;
}

//Xoa cuoi
template <typename T>
bool delLast(Node<T>*& head) {
	if (head == NULL)
		return false;

	Node<T>* pLast = head;
	Node<T>* prevLast = NULL;

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

//Giai phong vung nho
template <typename T>
void detroyList(Node<T>*& head) {
	while (head != NULL) {
		delLast(head);
	}
}

template <typename T>
void sort(Node<T>* head, bool comparator(T, T)) {
	if (head == NULL)
		return;

	for (Node<T>* i = head; i->next != NULL; i = i->next) {
		for (Node<T>* j = i->next; j != NULL; j = j->next) {
			if (comparator(j->info, i->info)) {
				swap(i->info, j->info);
			}
		}
	}
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