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

			insertLast(head, sv);
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

int main() {
	Node* head;
	init(head);

	inputListFromFile(head, "SinhVien.txt");

	printList(head);

	return 0;
}