#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Khai bao cau truc
#define M 17

int hashFunc(string str) {
	//top - pot
	int key = 0;

	for (int i = 0; i < str.length(); i++) {
		key += (int)tolower(str[i])*(i+1);
	}

	return key % M;
}

struct Word {
	string word;
	string type;
	string mean;
};

struct Node
{
	Word info;
	Node* next;
};

struct HashTable
{
	Node* h[M];
};

//Khoi tao rong
void init(HashTable& ht) {
	for (int i = 0; i < M; i++) {
		ht.h[i] = NULL;
	}
}

Node* createNode(Word key) {
	Node* p = new Node;
	p->info = key;
	p->next = NULL;

	return p;
}

//Them phan tu vao bang bam
void insert(HashTable& ht, Word key) {
	int k = hashFunc(key.word);
	if (ht.h[k] == NULL) {
		ht.h[k] = createNode(key);
		return;
	}

	Node* pLast = ht.h[k];

	while (pLast->next != NULL) {
		pLast = pLast->next;
	}

	pLast->next = createNode(key);
	return;
}
//Tim kiem
Node* search(HashTable ht, string key) {
	int k = hashFunc(key);

	Node* q = ht.h[k];
	while (q != NULL && q->info.word != key) {
		q = q->next;
	}

	return q;
}


//Duyet
void print(HashTable ht) {
	for (int i = 0; i < M; i++) {
		if (ht.h[i] != NULL) {
			cout << "BUCKET " << i << ": ";
			Node* p = ht.h[i];
			while (p != NULL) {
				cout << p->info.word;
				p = p->next;
				if (p != NULL)
					cout << "-->";
			}
			cout << endl;
		}
	}
}
//Xoa 1 phan tu trong bang bam
void delNode(HashTable& ht, string key) {
	int k = hashFunc(key);

	Node* q = ht.h[k];
	Node* qPrev = NULL;

	while (q != NULL && q->info.word != key) {
		qPrev = q;
		q = q->next;
	}

	//Khong tim thay
	if (q == NULL)
		return;

	if (qPrev == NULL) {
		ht.h[k] = q->next;
	}
	else
	{
		qPrev->next = q->next;
	}

	q->next = NULL;
	delete q;
}

//Doc tap tin
void readData(HashTable &ht) {
	ifstream fin("dictionary.txt");
	if (fin.is_open()) {
		while (!fin.eof()) {
			Word w;

			getline(fin, w.word, '#');
			getline(fin, w.type, '#');
			getline(fin, w.mean, '\n');

			insert(ht, w);
		}

		fin.close();
	}
}

int main() {
	HashTable ht;
	init(ht);

	readData(ht);

	print(ht);

	cout << "=========TIM KIEM==========\n";
	
	Node* res = search(ht, "love");
	if (res)
		cout << "Ket qua: " << res->info.word << "-" << res->info.type << "-" << res->info.mean << endl;
	else
		cout << "Khong tim thay!\n";

	

	return 0;
}