#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#define M 11

int hashFunc(string str) {
	int key = 0;
	//top - pot

	for (int i = 0; i < str.length(); i++) {
		key += (int)tolower(str[i])*(i+1);
	}

	return key % M;
}

struct Word
{
	string word;
	string type;
	string mean;
};

struct Node
{
	Word key;	
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

//Them phan tu vao bang bam
Node* createNode(Word key) {
	Node* p = new Node;
	p->key = key;
	p->next = NULL;
	return p;
}

void insertNode(HashTable &ht, Word key) {
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
}

//Xuat bang bam ra man hinh
void printHashTable(HashTable ht) {
	for (int i = 0; i < M; i++) {
		if (ht.h[i] != NULL) {
			cout << "BUCKET " << i << ": ";
			Node* p = ht.h[i];
			while (p != NULL) {
				cout << p->key.word;
				p = p->next;
				if (p != NULL) {
					cout << "->";
				}
			}
			cout << endl;
		}
	}
}
//Tim kiem tren bang bam
Node* search(HashTable ht, string key) {
	int k = hashFunc(key);

	Node* q = ht.h[k];
	while (q != NULL && q->key.word != key) {
		q = q->next;
	}

	return q;
}
//Xoa phan tu tren bang bam
void delNode(HashTable& ht, string key) {
	int k = hashFunc(key);

	Node* q = ht.h[k];
	Node* qPrev = NULL;
	while (q != NULL && q->key.word != key) {
		qPrev = q;
		q = q->next;
	}

	//Khong tim thay key
	if (q == NULL)
		return;

	//Tim thay va xoa
	if (qPrev == NULL)
		ht.h[k] = q->next;
	else
		qPrev->next = q->next;

	q->next = NULL;
	delete q;
}

void readData(HashTable& ht) {
	ifstream fin("dictionary.txt");
	if (fin.is_open()) {
		while (!fin.eof()) {
			Word w;
			getline(fin, w.word, '#');
			getline(fin, w.type, '#');
			getline(fin, w.mean, '\n');
			insertNode(ht, w);
		}

		fin.close();
	}
}

int main() {
	HashTable ht;
	init(ht);

	readData(ht);
	
	printHashTable(ht);

	cout << "=========TIM KIEM=========\n";
	Node* res = search(ht, "sad");
	if (res != NULL) {
		cout << "Ket qua: " << res->key.type << "-" << res->key.mean << endl;
	}
	else
		cout << "Khong tim thay!\n";

	return 0;
}