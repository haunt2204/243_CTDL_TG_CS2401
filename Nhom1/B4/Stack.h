#include <iostream>
using namespace std;

#define MAX 20

//Khai bao cau truc
struct Stack
{
	int a[MAX];
	int top;
};

//Khoi tao rong
void init(Stack& s) {
	s.top = -1;
}

//Thao tac them
void push(Stack& s, int x) {
	s.a[++s.top] = x;
}

//Thao tac lay ra khoi stack
int pop(Stack& s) {
	return s.a[s.top--];
}

//Kiem tra rong
bool isEmpty(Stack s) {
	return s.top == -1;
}