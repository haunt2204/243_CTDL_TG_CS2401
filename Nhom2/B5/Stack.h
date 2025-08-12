#include <iostream>

using namespace std;

#define MAX 20

struct Stack
{
	int a[MAX];
	int top;
};

//Khoi tao rong
void init(Stack& s) {
	s.top = -1;
}

//Them vao stack
void push(Stack& s, int x) {
	s.a[++s.top] = x;
}

//Lay ra khoi stack
int pop(Stack& s) {
	return s.a[s.top--];
}

//Kiem tra stack rong
bool isEmpty(Stack s) {
	return s.top == -1;
}