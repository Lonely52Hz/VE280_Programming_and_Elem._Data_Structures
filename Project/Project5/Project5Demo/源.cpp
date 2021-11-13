#include <iostream>
#include "dlist.h"

using namespace std;

int main() {
	try {
		Dlist<int>* il = new Dlist<int>;
		int a = 1;
		int b = 2;
		int c = 0;
		int* a1 = &a;
		int* b1 = &b;
		int* c1 = &c;
		cout << il->isEmpty() << endl;
		il->insertBack(a1);
		il->insertBack(b1);
		il->insertFront(c1);
		il->removeFront();
		il->removeFront();
		il->removeFront();
		//il->removeFront();
		//il->print();
		cout << il->isEmpty() << endl;
		Dlist<int>* il2 = new Dlist<int>;
		il2 = il;
		//il2->print();
	}
	catch (emptyList e) {
		cout << "empty" << endl;
	}
	return 0;
}