#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cassert>
#include "dlist.h"

using namespace std;

template <class T>
class my_stack {
	Dlist<T> list;
	int size; //size of stack

public:
	my_stack();
	// EFFECTS: constructor

	void push(T val);
	// EFFECTS: push

	void pop();
	// EFFECTS: pop

	T top();
	// EFFECTS: top value

	bool Empty();
	// EFFECTS: judge empty
};

template <class T>
my_stack<T>::my_stack() {
	// EFFECTS: constructor
	size = 0;
}

template <class T>
void my_stack<T>::push(T val) {
	// EFFECTS: push
	T* np = new T(val);
	list.insertFront(np);
	size++;
}

template <class T>
void my_stack<T>::pop() {
	// EFFECTS: pop
	T* np = list.removeFront();
	delete np;
	size--;
}

template <class T>
T my_stack<T>::top() {
	// EFFECTS: top value
	T* np = list.removeFront();
	T answer = *np;
	T* nnp = new T(*np);
	list.insertFront(nnp);
	delete np;
	return answer;
}

template <class T>
bool my_stack<T>::Empty() {
	// EFFECTS: judge empty
	return (size == 0);
}

bool judege(string a, string b);
// EFFECTS: judge precedence

void convert(string& token, string& output, my_stack<string>* opstack);
// EFFECTS: step 2 convertion

void compute(string& token, my_stack<int>* evaluate);
// EFFECTS: step 3 computation

int main() {
	string token, line;
	string output = "";
	my_stack<string> opstack;
	my_stack<int> evaluate;
	istringstream postfix, rpn;
	getline(cin, line);
	postfix.str(line);
	int result;
	while (postfix >> token) { //while there are tokens to be read:
		try { convert(token, output, &opstack); }
		catch (int a) { return 0; }
	}
	while (!opstack.Empty()) { //there are still operator tokens on the stack
		if (opstack.top()=="("||opstack.top()==")") {
			cout << "ERROR: Parenthesis mismatch" << endl;
			return 0;
		}
		output.append(opstack.top()).append(" ");
		opstack.pop();
	}
	cout << output << endl;
	rpn.str(output);
	while (rpn >> token) {
		try { compute(token, &evaluate); }
		catch (int a) { return 0; }
	}
	result = evaluate.top();
	evaluate.pop();
	if (!evaluate.Empty()) {
		cout << "ERROR: Too many operands" << endl;
		return 0;
	}
	cout << result << endl;
	return 0;
}

bool judege(string a, string b) {
	if (a == "*" || a == "/") { //high 
		return true;
	}
	else if (a == "+" || a == "-") {
		if (b == "+" || b == "-") { // same
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

void convert(string& token, string& output, my_stack<string>* opstack) {
	if (token[0] >= 48 && token[0] <= 57) { //if the token is a number
		output.append(token).append(" ");
	}
	else if (token == "+" || token == "-" || token == "*" || token == "/") { // the token is an operator then
		while (!opstack->Empty() && judege(opstack->top(), token) && opstack->top() != "(") {
			output.append(opstack->top()).append(" ");
			opstack->pop();
		}
		opstack->push(token);
	}
	else if (token == "(") { // the token is a left parenthesis (i.e. "(")
		opstack->push(token);
	}
	else if (token == ")") { // the token is a right parenthesis (i.e. ")")
		if (opstack->Empty()) {
			cout << "ERROR: Parenthesis mismatch" << endl;
			throw 1;
		}
		while (opstack->top() != "(") {
			output.append(opstack->top()).append(" ");
			opstack->pop();
			if (opstack->Empty()) {
				cout << "ERROR: Parenthesis mismatch" << endl;
				throw 1;
			}
		}
		if (opstack->top() == "(") {
			opstack->pop();
		}
	}
}

void compute(string&token, my_stack<int>* evaluate) {
	int m, n;
	if (token[0] >= 48 && token[0] <= 57) { //If an operand is found, push it to the stack
		evaluate->push(stoi(token));
	}
	else if (token == "+" || token == "-" || token == "*" || token == "/") { // If an operator is found
		if (evaluate->Empty()) {
			cout << "ERROR: Not enough operands" << endl;
			throw 1;
		}
		m = evaluate->top();
		evaluate->pop();
		if (evaluate->Empty()) {
			cout << "ERROR: Not enough operands" << endl;
			throw 1;
		}
		n = evaluate->top();
		evaluate->pop();
		if (token == "+") {
			evaluate->push(n + m);
		}
		else if (token == "-") {
			evaluate->push(n - m);
		}
		else if (token == "*") {
			evaluate->push(n * m);
		}
		else {
			if (m == 0) {
				cout << "ERROR: Divide by zero" << endl;
				throw 1;
			}
			else {
				evaluate->push(n / m);
			}
		}
	}
}

