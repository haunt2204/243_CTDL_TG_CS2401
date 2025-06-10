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
	getline(cin,sv.queQuan);
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


//Khai bao 
struct ArrayList
{
	SinhVien ds[MAX];
	int soLuong;
};

//Khoi tao rong
void init(ArrayList& l) {
	l.soLuong = 0;
}

void inputList(ArrayList& l) {
	cout << "Nhap so luong SV: ";
	cin >> l.soLuong;
	for (int i = 0; i < l.soLuong; i++) {
		nhap1Sv(l.ds[i]);
	}
}


//Them phan tu tai vi tri vt
int insert(ArrayList& l, SinhVien sv, int vt=0) {
	if (l.soLuong >= MAX || vt >= l.soLuong + 1)
		return -1;

	for (int i = l.soLuong; i > vt; i--) {
		l.ds[i] = l.ds[i - 1];
	}
	l.ds[vt] = sv;
	l.soLuong += 1;

	return 1;
}

//Thao tac xoa 1 phan tu tai vi tri vt
int delSv(ArrayList& l, const int vt = 0) {
	if (vt < 0 || vt>=l.soLuong) {
		return -1;
	}

	for (int i = vt; i < l.soLuong - 1; i++) {
		l.ds[i] = l.ds[i + 1];
	}

	l.soLuong--;
	return 1;
}
//Thao tac tim kiem 1 phan tu id
int find(ArrayList l, const int id) {
	for (int i = 0; i < l.soLuong; i++) {
		if (l.ds[i].mssv == id)
			return i;
	}

	return -1;
}
//Thao tac sap xep theo: Id, Ho ten, Que quan,....

int cmpWithIdAsc(SinhVien sv1, SinhVien sv2) {
	return sv1.mssv - sv2.mssv;
}

int cmpWithIdDesc(SinhVien sv1, SinhVien sv2) {
	return -(sv1.mssv - sv2.mssv);
}

int cmpWithNameAsc(SinhVien sv1, SinhVien sv2) {
	return sv1.hoTen.compare(sv2.hoTen);
}

void sort(ArrayList &l, int comparator(SinhVien,SinhVien)) {
	for (int i = 0; i < l.soLuong - 1; i++) {
		for (int j = i + 1; j < l.soLuong; j++) {
			if (comparator(l.ds[j], l.ds[i])<0) {
				swap(l.ds[j], l.ds[i]);
			}
		}
	}
}
//Nhap du lieu tu tap tin
void inputListFromFile(ArrayList& l, string fileName) {
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

			insert(l, sv,l.soLuong);
		}

		fin.close();
	}
}

void outputList(ArrayList l) {
	if (l.soLuong == 0) {
		cout << "Danh sach rong!\n";
		return;
	}

	for (int i = 0; i < l.soLuong; i++) {
		xuat1Sv(l.ds[i]);
	}
}

int main() {
	ArrayList l;
	init(l);

	//inputList(l);

	inputListFromFile(l, "SinhVien.txt");

	//Them phan tu vao danh sach o vi tri vt
	//SinhVien sv;
	//sv.mssv = 3;
	//insert(l, sv, 0);
	//Xuat danh sach ra man hinh
	/*outputList(l);

	cout << "================XOA SV==============\n";
	int index = find(l, 2018001);

	if (index == -1) {
		cout << "Khong tim thay!\n";
	}
	else {
		delSv(l, index);
		outputList(l);
	}*/

	cout << "================SAP XEP==============\n";
	sort(l, cmpWithNameAsc);
	outputList(l);

	return 0;
}