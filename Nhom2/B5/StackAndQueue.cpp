#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Stack.h"
#include "Queue.h"
#include <stack>
#include <queue>
#include <string>
using namespace std;

//Chuyen 1 so tu he thap phan sang nhi phan
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
	Stack s;
	init(s);
	int a, b;

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
			case '-':
				push(s, a - b);
				break;
			case '*':
				push(s, a * b);
				break;
			case '/':
				if (b == 0) {
					cout << "Loi chia 0!\n";
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

	cout << "Ket qua: " << pop(s) << endl;
}

//Chuyen bieu thuc tu trung to sang hau to
int getPriority(string op) {
	if (op == "*" || op == "/")
		return 2;

	if (op == "+" || op == "-")
		return 1;

	return 0;
}

char* convertInfixToPostfix(char str[]) {
	char* res = new char[strlen(str)];
	res[0] = '\0';

	Queue postfix;
	init(postfix);

	stack<char*> s;

	char* p = strtok(str, " ");
	while (p != NULL) {
		if (isdigit(*p)) {
			enQueue(postfix, p);
		}
		else if (*p == '(') {
			s.push(p);
		}
		else if (*p == ')') {
			char* op = s.top();
			s.pop();
			while (*op != '(') {
				enQueue(postfix, op);
				op = s.top();
				s.pop();
			}
			
		}
		else {
			while (!s.empty() && getPriority(s.top()) >= getPriority(p)) {
				char* p = s.top();
				s.pop();

				enQueue(postfix, p);
			}
			s.push(p);
		}

		p = strtok(NULL, " ");
	}

	while (!s.empty()) {
		enQueue(postfix, s.top());
		s.pop();
	}

	while (!isEmpty(postfix)) {
		strcat(res, deQueue(postfix));
		strcat(res, " ");
	}

	return res;
}

int main() {
	char str[] = "2 + 4 - ( 5 - 3 ) / 2 + 3 - 1 * 5";
	/*char str[] = "2 4 + 5 3 - 2 / - 3 + 1 5 * -";*/

	//convertDecToBin(5);
	calExp(convertInfixToPostfix(str));
	
	return 0;
}