#include <iostream>
using namespace std;

struct Node
{
	char* info;
	Node* next;
};

struct Queue
{
	Node* head, * tail;
};

//Khoi tao rong
void init(Queue& q) {
	q.head = q.tail = NULL;
}
//Them vao queue
Node* createNode(char* x) {
	Node* p = new Node;
	p->info = x;
	p->next = NULL;
	return p;
}

void enQueue(Queue& q, char* x) {
	Node* p = createNode(x);
	if (q.head == NULL) {
		q.head = q.tail = p;
		return;
	}

	q.tail->next = p;
	q.tail = p;
}

//Lay ra tu queue
char* deQueue(Queue& q) {
	if (q.head == NULL)
		return NULL;

	Node* p = q.head;
	char* data = p->info;

	q.head = q.head->next;
	if (q.head == NULL) {
		q.tail = NULL;
	}
	else {
		p->next = NULL;
	}
	

	delete p;

	return data;
}

//Kiem tra rong
bool isEmpty(Queue q) {
	return q.head == NULL;
}