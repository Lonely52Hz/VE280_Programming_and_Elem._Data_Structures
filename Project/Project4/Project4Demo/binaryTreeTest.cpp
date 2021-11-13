#include "binaryTree.h"
#include <iostream>

using namespace std;

int main() {

	Node* f = new Node("f", 6, nullptr, nullptr);
	Node* f1 = new Node("f", 6, nullptr, nullptr);
	Node* g = new Node("g", 7, nullptr, nullptr);
	Node* g1 = new Node("g", 7, nullptr, nullptr);
	Node* e = new Node("e", 8, nullptr, nullptr);
	Node* e1 = new Node("e", 8, nullptr, nullptr);
	Node* d = new Node("d", 3, f, g);
	Node* d1 = new Node("d", 3, f1, g1);
	Node* b = new Node("b", 2, nullptr, d);
	//Node* b1 = new Node("b", 2, nullptr, d1);
	Node* c = new Node("c", 5, nullptr, e);
	//Node* c1 = new Node("c", 5, nullptr, e1);
	Node* a = new Node("a", 4, b, c);
	//Node* a1 = new Node("a", 4, b1, nullptr);



	BinaryTree large(a);

	//BinaryTree small(&a1);

	BinaryTree m(d1);



	cout << m.contained_by(large) << endl;



	return 0;

}