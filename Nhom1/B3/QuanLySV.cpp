#include "AbstractLinkedList.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;


struct SinhVien
{
	long mssv;
	string hoTen;
	char ngaySinh[11];
	string queQuan;
	double dtb;
};

void nhap1Sv(SinhVien& sv) {
	cout << "Nhap MSSV: ";
	cin >> sv.mssv;
	cout << "Nhap ho ten: ";
	cin.ignore(1);
	getline(cin, sv.hoTen, '\n');
	cout << "Nhap ngay sinh: ";
	cin >> sv.ngaySinh;
	cout << "Nhap que quan: ";
	cin.ignore(1);
	getline(cin, sv.queQuan);
	cout << "Nhap diem TB: ";
	cin >> sv.dtb;
}

void xuat1Sv(SinhVien sv) {
	cout << "===============================\n";
	cout << "ID: ";
	cout << sv.mssv << endl;
	cout << "Ho va ten: ";
	cout << sv.hoTen << endl;
	cout << "Ngay sinh: ";
	cout << sv.ngaySinh << endl;
	cout << "Que quan: ";
	cout << sv.queQuan << endl;
	cout << "Diem trung binh: ";
	cout << sv.dtb << endl;
	cout << "===============================\n";
}

ostream& operator<<(ostream& out, const SinhVien& sv) {
	out << "===============================\n";
	out << "ID: ";
	out << sv.mssv << endl;
	out << "Ho va ten: ";
	out << sv.hoTen << endl;
	out << "Ngay sinh: ";
	out << sv.ngaySinh << endl;
	out << "Que quan: ";
	out << sv.queQuan << endl;
	out << "Diem trung binh: ";
	out << sv.dtb << endl;
	out << "===============================\n";

	return out;
}

//Thao tac tim kiem
template <typename T>
Node<T>* search(Node<T>* head, int id) {
	Node<T>* p = head;
	while (p != NULL && p->info.mssv != id) {
		p = p->next;
	}
	return p;
}

template <typename T>
void insertAfter(Node<T>* head, const int key, const T x) {
	Node<T>* q = search(head, key);
	if (q != NULL) {
		Node* p = createNode(x);
		p->next = q->next;
		q->next = p;
	}
}

template <typename T>
void insertOrdered(Node<T>*& head, T x) {
	if (head == NULL || head->info.mssv > x.mssv) {
		insertFirst(head, x);
		return;
	}

	Node<T>* p = createNode(x);
	Node<T>* q = head;

	while (q->next != NULL && q->next->info.mssv < x.mssv) {
		q = q->next;
	}

	p->next = q->next;
	q->next = p;
}

template <typename T>
void inputListFromFile(Node<T> *&head, string fileName) {
	ifstream fin(fileName);

	if (fin.is_open()) {

		while (!fin.eof()) {
			SinhVien sv;

			fin >> sv.mssv;
			fin.ignore();
			getline(fin, sv.hoTen, '#');
			fin.getline(sv.ngaySinh, 11, '#');
			getline(fin, sv.queQuan, '#');
			fin >> sv.dtb;

			insertFirst(head, sv);
		}

		fin.close();
	}
}

template <typename T>
bool delNode(Node<T>*& head, const int key) {
	Node<T>* q = head;
	Node<T>* qPrev = NULL;

	while (q != NULL && q->info.mssv != key) {
		qPrev = q;
		q = q->next;
	}

	if (q == NULL)
		return false;

	if (qPrev == NULL) {
		head = head->next;
	}else
		qPrev->next = q->next;

	q->next = NULL;
	delete q;
	return true;
}

bool cmpWithId(SinhVien sv1, SinhVien sv2) {
	return sv1.mssv < sv2.mssv;
}

int main() {
	Node<SinhVien>* head;
	init(head);

	inputListFromFile(head, "SinhVien.txt");

	sort(head, cmpWithId);

	printList(head);

	detroyList(head);
	return 0;
}