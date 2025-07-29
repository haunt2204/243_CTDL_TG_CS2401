#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Stack.h"
#include "Queue.h"
#include <stack>
#include <queue>
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

int main() {
	//2 + 4 - ( 5 - 3 ) / 2 + 3 - 1 * 5
	char str[] = "2 4 + 5 3 - 2 / - 3 + 1 5 * -";

	//convertDecToBin(5);
	calExp(str);

	Queue q;
	init(q);

	char tmp[] = "2";

	enQueue(q, tmp);
	cout << deQueue(q) << endl;
	cout << isEmpty(q) << endl;
	return 0;
}