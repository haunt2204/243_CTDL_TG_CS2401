#define _CRT_SECURE_NO_WARNINGS
#include "Stack.h"
#include <stack>
#include "Queue.h"
#include <iostream>
using namespace std;




//Chuyen tu he co so 10 sang nhi phan
void convertDecToBin(int n) {
	Stack s;
	init(s);

	while (n != 0) {
		push(s, n % 2);
		n = n / 2;
	}

	while (!isEmpty(s)) {
		cout << pop(s);
	}
	cout << endl;
}

void calExp(char str[]) {
	int a, b;
	Stack s;
	init(s);

	char* p = strtok(str, " ");
	while (p != NULL) {

		if (isdigit(*p)) {
			push(s, atoi(p));
		}
		else {
			b = pop(s);
			a = pop(s);
			switch (*p)
			{
			case '+':
				push(s, a + b);
				break;
			case '*':
				push(s, a * b);
				break;
			case '-':
				push(s, a - b);
				break;
			case '/':
				if (b == 0) {
					cout << "Loi chia cho 0!\n";
					return;
				}
				push(s, a / b);
				break;
			default:
				break;
			}
		}
		p = strtok(NULL, " ");
	}

	cout << "Ket qua phep tinh: " << pop(s) << endl;
}

int getPriority(string op) {
	if (op == "*" || op == "/")
		return 2;
	if (op == "+" || op == "-")
		return 1;
	return 0;
}

char* infixToPostfix(char str[]) {
	Queue postfix;
	init(postfix);

	stack<char*> s;

	char* p = strtok(str, " ");
	while (p != NULL) {
		if (isdigit(*p)) {
			enQueue(postfix, p);
		} else if (*p == '(') {
			s.push(p);
		} else if (*p == ')') {
			char* op = s.top();
			s.pop();
			while (*op != '(') {
				enQueue(postfix, op);

				op = s.top();
				s.pop();
			}
		}
		else {
			while (!s.empty() && getPriority(p) <= getPriority(s.top())) {
				enQueue(postfix, s.top());
				s.pop();
			}
			s.push(p);
		}

		p = strtok(NULL, " ");
	}

	while (!s.empty()) {
		enQueue(postfix, s.top());
		s.pop();
	}

	char* res = new char[strlen(str)];
	res[0] = '\0';

	while (!isEmpty(postfix)) {
		strcat(res, deQueue(postfix));
		if (!isEmpty(postfix))
			strcat(res, " ");
	}

	return res;
}

int main() {
	convertDecToBin(5);
	char str[] = "2 + 4 - ( 5 - 3 ) / 2 + 3 - 1 * 5";
	calExp(infixToPostfix(str));
	return 0;
}