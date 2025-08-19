#include <iostream>
using namespace std;

#define M 7

int hashFunc(int key) {
    return key % M;
}

//Khai bao cau truc
struct IntValue
{
    int value;
    int freq;
};

struct Node
{
    IntValue* key;
    int next;
};

struct HashTable
{
    Node h[M];
    int r;
};

//Khoi tao rong
void init(HashTable& ht) {
    for (int i = 0; i < M; i++) {
        ht.h[i].key = NULL;
        ht.h[i].next = -1;
    }
    ht.r = M - 1;
}
//Them phan tu vao bang bam
void insertNode(HashTable& ht, IntValue* key) {
    int k = hashFunc(key->value);

    if (ht.h[k].key == NULL) {
        ht.h[k].key = key;
    
    }
    else if (ht.r >= 0) {
        //Xay ra dung do
        if (ht.h[k].key->value == key->value) {
            ht.h[k].key->freq += 1;
            return;
        }
        while (ht.h[k].next != -1) {
            if (ht.h[k].key->value == key->value) {
                ht.h[k].key->freq += 1;
                return;
            }
            k = ht.h[k].next;
        }

        ht.h[ht.r].key = key;
        ht.h[k].next = ht.r;
    }

    while (ht.r >= 0 && ht.h[ht.r].key != NULL) {
        ht.r--;
    }
}
//Tim kiem

//Thao tac xoa

//In bang bam ra man hinh
void printList(HashTable ht) {
    for (int i = 0; i < M; i++) {
        if (ht.h[i].key != NULL) {
            cout << "BUCKET " << i << ": " 
                << ht.h[i].key->value << "(" 
                << ht.h[i].key->freq << ")->" 
                << ht.h[i].next << endl;
       }
    }
}

int main()
{
    HashTable ht;
    init(ht);

    int a[] = {7,7,35,5,21,5,4,7};
    int n = sizeof(a) / sizeof(a[0]);

    for (int i = 0; i < n; i++) {
        IntValue* tmp = new IntValue;
        tmp->value = a[i];
        tmp->freq = 1;
        insertNode(ht, tmp);
    }

    printList(ht);

    return 0;
}
