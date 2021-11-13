#ifndef __DLIST_IMPL_H__
#define __DLIST_IMPL_H__

#include "dlist.h"

/*
template <class T>
void Dlist<T>::print()
{
	node* itr = first;
	while (itr) {
		std::cout << *(itr->op);
		itr = itr->next;
	}
	std::cout << "\n";
}
*/

template <class T>
bool Dlist<T>::isEmpty() const {
	return !first;
}

template <class T>
void Dlist<T>::insertFront(T* op) {
	node* np = new node;
	np->prev = nullptr;
	np->op = op;
	if (isEmpty()) {
		np->next = nullptr;
		first = last = np;
	}
	else {
		np->next = first;
		first->prev = np;
		first = np;
	}
}

template <class T>
void Dlist<T>::insertBack(T* op) {
	node* np = new node;
	np->next = nullptr;
	np->op = op;
	if (isEmpty()) {
		np->prev = nullptr;
		first = last = np;
	}
	else {
		last->next = np;
		np->prev = last;
		last = np;
	}
}

template <class T>
T* Dlist<T>::removeFront() {
	if (isEmpty()) {
		emptyList e;
		throw e;
	}
	node* victim = first;
	T* result = first->op;
	if (first->next == nullptr) {
		first = nullptr;
		last = nullptr;
	}
	else {
		first = victim->next;
		first->prev = nullptr;
	}
	delete victim;
	return result;
}

template <class T>
T* Dlist<T>::removeBack() {
	if (isEmpty()) {
		emptyList e;
		throw e;
	}
	node* victim = last;
	T* result = last->op;
	if (last->prev == nullptr) {
		first = nullptr;
		last = nullptr;
	}
	else {
		last = victim->prev;
		last->next = nullptr;
	}
	delete victim;
	return result;
}


template <class T>
T* Dlist<T>::remove(bool (*cmp)(const T*, const T*), T* ref) {
	node* current = first;
	T* result = nullptr;
	if (first == nullptr) {
		return nullptr;
	}
	if (first == last) {
		if (cmp(first->op, ref)) {
			result = first->op;
			first = nullptr;
			last = nullptr;
			delete current;
			return result;
		}
		else {
			return nullptr;
		}
	}
	if (cmp(first->op, ref)) {
		result = first->op;
		first = current->next;
		first->prev = nullptr;
		delete current;
		return result;
	}
	if (cmp(last->op, ref)) {
		current = last;
		result = last->op;
		last = current->prev;
		last->next = nullptr;
		delete current;
		return result;
	}
	while (!cmp(current->op, ref)) {
		current = current->next;
		if (current == nullptr) {
			delete current;
			return nullptr;
		}
	}
	result = current->op;
	current->prev->next = current->next;
	current->next->prev = current->prev;
	delete current;
	return result;
}


template <class T>
Dlist<T>::Dlist() {
	first = nullptr;
	last = nullptr;
}

template <class T>
Dlist<T>::Dlist(const Dlist<T>& l) {
	first = nullptr;
	last = nullptr;
	copyAll(l);
}

template <class T>
Dlist<T>& Dlist<T>::operator=(const Dlist<T>& l) {
	if (this != &l) {
		removeAll();
		copyAll(l);
	}
	return *this;
}

template <class T>
Dlist<T>::~Dlist() {
	removeAll();
}

template <class T>
void Dlist<T>::removeAll() {
	while (!isEmpty()) {
		T* op = removeFront();
		delete op;
	}
}

template <class T>
void Dlist<T>::copyAll(const Dlist<T>& l) {
	removeAll();
	if (l.isEmpty()) {
		return;
	}
	node* current = l.first;
	while (current) {
		T* n = new T(*(current->op));
		insertBack(n);
		current = current->next;
	}
}

#endif
