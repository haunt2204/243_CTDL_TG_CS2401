#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#define MAX 20

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

//Khai bao cau truc
struct Node {
	//Vung thong tin
	SinhVien info;

	//Vung lien ket
	Node* next;
};

//Khoi tao rong
void init(Node *&head) {
	head = NULL;
}
//Tao node moi
Node* createNode(SinhVien x) {
	Node* p = new Node;
	p->info = x;
	p->next = NULL;
	return p;
}

//Tim kiem
Node* search(Node* head, const int id) {
	Node* p = head;

	while (p != NULL && p->info.mssv != id) {
		p = p->next;
	}

	return p;
}

//Them phan tu vao cuoi danh sach
void insertLast(Node*& head, SinhVien x) {
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
void insertFirst(Node*& head, SinhVien x) {
	Node* p = createNode(x);
	p->next = head;
	head = p;
}

//Them sau phan tu q
bool insertNode(Node* head, const int id, SinhVien x) {
	Node* q = search(head, id);
	if (q == NULL)
		return false;

	Node* p = createNode(x);
	p->next = q->next;
	q->next = p;

	return true;
}

//Them tu file
void inputListFromFile(Node *&head, string fileName) {
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

//Duyet danh sach
void printList(Node* head) {
	if (head == NULL) {
		cout << "Danh sach rong!\n";
		return;
	}

	Node* tmp = head;
	while (tmp != NULL) {
		xuat1Sv(tmp->info);
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
bool delNode(Node*& head, const int id) {
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
void sort(Node* head) {
	if (head == NULL)
		return;

	for (Node* i = head; i->next != NULL; i=i->next) {
		for (Node* j = i->next; j!=NULL; j=j->next) {
			if (j->info.mssv<i->info.mssv) {
				swap(i->info, j->info);
			}
		}
	}
}

//Them phan tu moi vao danh sach co thu tu
void insertOrdered(Node*& head, SinhVien sv) {
	if (head == NULL || head->info.mssv > sv.mssv) {
		insertFirst(head, sv);
		return;
	}

	Node* p = createNode(sv);
	Node* q = head;

	while (q->next != NULL && q->next->info.mssv < sv.mssv) {
		q = q->next;
	}

	p->next = q->next;
	q->next = p;
}


//Giai phong vung nho
void detroyList(Node*& head) {
	while (head != NULL) {
		delLast(head);
	}
}

int main() {
	Node* head;
	init(head);

	//inputListFromFile(head, "SinhVien.txt");

	printList(head);

	/*cout << "================TIM KIEM=================\n";
	Node*q = search(head, 2018006);

	if (q!=NULL) {
		xuat1Sv(q->info);
	}*/

	/*cout << "================TIM VA XOA=================\n";
	delNode(head, 2018006);

	printList(head);*/

	/*SinhVien sv;
	sv.mssv = 9999;

	insertNode(head, 2018007, sv);
	printList(head);*/

	cout << "================SAP XEP=================\n";
	sort(head);

	//delNode(head, 2018006);
	cout << "================THEM VAO DS CO THU TU=================\n";
	SinhVien sv;
	sv.mssv = 20180061;
	insertOrdered(head, sv);

	printList(head);

	detroyList(head);
	printList(head);
	return 0;
}