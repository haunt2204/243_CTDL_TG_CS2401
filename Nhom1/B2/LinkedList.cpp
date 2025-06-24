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

//Thao tac tim kiem
Node* search(Node* head, int id) {
	Node* p = head;
	while (p != NULL && p->info.mssv != id) {
		p = p->next;
	}
	return p;
}

//Them phan tu vao dau, cuoi danh sach
void insertFirst(Node*& head, SinhVien x) {
	Node* p = createNode(x);
	p->next = head;
	head = p;
}
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

void insertAfter(Node* head, const int key, const SinhVien x) {
	Node* q = search(head, key);
	if (q != NULL) {
		Node* p = createNode(x);
		p->next = q->next;
		q->next = p;
	}
}

void insertOrdered(Node*& head, SinhVien x) {
	if (head == NULL || head->info.mssv > x.mssv) {
		insertFirst(head, x);
		return;
	}

	Node* p = createNode(x);
	Node* q = head;

	while (q->next != NULL && q->next->info.mssv < x.mssv) {
		q = q->next;
	}

	p->next = q->next;
	q->next = p;
}

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
	while (q->next!=NULL) {
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
				if (j->info.mssv < i->info.mssv)
					swap(i->info, j->info);
			}
		}
	}
}

int main() {
	Node* head;
	init(head);

	/*inputListFromFile(head, "SinhVien.txt");

	printList(head);*/

	/*cout << "================TIM KIEM================\n";
	Node* res = search(head, 20128002);
	if (res) {
		xuat1Sv(res->info);
	}
	else
		cout << "Khong tim thay!\n";*/

	/*cout << "================THEM SAU Q================\n";
	SinhVien x;
	x.mssv = 20180022;
	insertAfter(head, 2018002, x);
	printList(head);*/

	/*cout << "================XOA DAU================\n";
	delNode(head, 2018001);

	printList(head);

	cout << "================TRUY XUAT PHAT TU================\n";
	Node* res = getNodeAt(head, 1);
	xuat1Sv(res->info);*/

	/*cout << "================SAP XEP================\n";
	sort(head);
	delNode(head, 2018005);
	printList(head);*/

	SinhVien sv;
	cin >> sv.mssv;

	insertOrdered(head, sv);
	printList(head);

	detroyList(head);
	return 0;
}