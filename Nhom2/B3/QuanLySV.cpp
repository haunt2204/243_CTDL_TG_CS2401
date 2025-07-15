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

//Tim kiem
template <typename T>
Node<T>* search(Node<T>* head, const int id) {
	Node* p = head;

	while (p != NULL && p->info.mssv != id) {
		p = p->next;
	}

	return p;
}


//Them sau phan tu q
template <typename T>
bool insertNode(Node<T>* head, const int id, T x) {
	Node* q = search(head, id);
	if (q == NULL)
		return false;

	Node* p = createNode(x);
	p->next = q->next;
	q->next = p;

	return true;
}

//Them tu file
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

//Xoa phan tu mang gia tri q mang gia tri id
template <typename T>
bool delNode(Node<T>*& head, const int id) {
	Node* q = head;
	Node* prevQ = NULL;

	while (q != NULL && q->info.mssv != id) {
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
bool cmpWithId(SinhVien sv1, SinhVien sv2) {
	return sv1.mssv - sv2.mssv;
}

//Them phan tu moi vao danh sach co thu tu
template <typename T>
void insertOrdered(Node<T>*& head, T sv) {
	if (head == NULL || head->info.mssv > sv.mssv) {
		insertFirst(head, sv);
		return;
	}

	Node<T>* p = createNode(sv);
	Node<T>* q = head;

	while (q->next != NULL && q->next->info.mssv < sv.mssv) {
		q = q->next;
	}

	p->next = q->next;
	q->next = p;
}


int main() {
	Node<SinhVien>* head;
	init(head);

	inputListFromFile(head, "SinhVien.txt");

	sort(head, cmpWithId);
	printList(head);

	detroyList(head);
	printList(head);
	return 0;
}