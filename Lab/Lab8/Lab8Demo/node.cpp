#include "node.h"
#include <iostream>

using namespace std;

void Node::addChild(Node* child) {
	if (child_num >= n) {
		tooManyChildren toomany;
		delete child;
		throw toomany;
	}
	else {
		children[child_num] = child;
		child_num++;
		child->parent = this;
	}
}

Node::Node(int _value, int _n) {
	value = _value;
	child_num = 0;
	n = _n;
	parent = NULL;
	children = new Node * [_n];
	height = 0;
}

Node::~Node() {
	for (int i = 0; i < child_num; ++i) {
		delete children[i];
	}
	delete[] children;
}

void Node::addChild(int _value) {
	if (child_num >= n) {
		tooManyChildren toomany;
		throw toomany;
	}
	else {
		Node* new_node = new Node(_value, n);
		addChild(new_node);
	}
}

void Node::traverse_helper(Node* _child) {
	if (_child == NULL) {
		return;
	}
	else {
		cout << _child->value << " ";
		for (int i = 0; i < _child->child_num; ++i) {
			traverse_helper(_child->children[i]);
		}
	}
}

void Node::traverse() {
	traverse_helper(this);
}

bool Node::isSame(Node* tree, Node* sub) {
	if (tree != NULL && sub != NULL) {
		if (tree->value == sub->value && tree->child_num == sub->child_num) {
			for (int i = 0; i < tree->child_num; ++i) {
				if (!isSame(tree->children[i], sub->children[i])) {
					return false;
				}
			}
		}
		else {
			return false;
		}
	}
	else if (tree == NULL && sub == NULL) {
		return true;
	}
	else {
		return false;
	}
	return true;
}

bool Node::contain_helper(Node* tree, Node* sub) {
	bool flag = isSame(tree, sub);
	if (!flag) {
		for (int i = 0; i < tree->child_num; ++i) {
			if (contain_helper(tree->children[i], sub)) {
				return true;
			}
		}
	}
	return flag;
}

bool Node::contain(Node* sub) {
	bool flag = isSame(this, sub);
	if(!flag) {
		for (int i = 0; i < child_num; ++i) {
			if (contain_helper(this->children[i], sub)) {
				return true;
			}
		}
	}
	return flag;
}

int Node::getHeight_helper(Node* tree) {
	int temp = 0;
	int answer = 0;
	if (tree->child_num == 0) {
		return 0;
	}
	for (int i = 0; i < tree->child_num; ++i) {
		temp = getHeight_helper(tree->children[i]);
		if (answer < temp) {
			answer = temp;
		}
	}
	return answer + 1;
}

int Node::getHeight() {
	height = getHeight_helper(this);
	return height;
}

Node& Node::operator[](int i) {
	if (i < 0 || i >= child_num) {
		invalidIndex invalid;
		throw invalid;
	}
	else {
		return *children[i];
	}
}