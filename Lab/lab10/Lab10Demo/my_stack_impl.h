/*
 * This is an exercise of VE280 Lab 10, SU2020.
 * Written by Martin Ma.
 * Latest Update: 7/17/2020.
 * Copyright © 2020 Mars-tin. All rights reserved.
 */

#ifndef MY_STACK_IMPL_H
#define MY_STACK_IMPL_H

#include <iostream>
#include "my_stack.h"


template <class T>
void Stack<T>::print()
{
    Node<T>* itr = head;
    while(itr){
        std::cout << itr->val;
        itr = itr->next;
    }
    std::cout << "\n";
}

template <class T>
void Stack<T>::removeAll() {
    while (!isEmpty()) {
        pop();
    }
}

template <class T>
void Stack<T>::copyFrom_helper(Node<T>* list) {
    if (!list) {
        return;
    }
    copyFrom_helper(list->next);
    push(list->val);
}

template <class T>
void Stack<T>::copyFrom(const Stack<T>& s) {
    if (!isEmpty()) {
        removeAll();
    }
    copyFrom_helper(s.head);
}

template <class T>
Stack<T>::Stack() {
    head = nullptr;
}

template <class T>
Stack<T>::Stack(const Stack<T>& s) {
    head = nullptr;
    copyFrom(s);
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& s) {
    if (this != &s) {
        removeAll();
        copyFrom(s);
    }
    return* this;
}

template <class T>
Stack<T>::~Stack() {
    removeAll();
}

template <class T>
bool Stack<T>::isEmpty() const {
    return !head;
}

template <class T>
size_t Stack<T>::size() const {
    size_t count = 0;
    Node<T>* current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

template <class T>
void Stack<T>::push(T val) {
    Node<T>* np = new Node<T>;
    np->val = val;
    np->next = head;
    head = np;
}

template <class T>
void Stack<T>::pop() {
    Node<T>* victim = head;
    if (isEmpty()) {
        stackEmpty e;
        throw e;
    }
    head = victim->next;
    delete victim;
}

template <class T>
T Stack<T>::top() const {
    if (isEmpty()) {
        stackEmpty e;
        throw e;
    }
    return head->val;
}

template <class T>
void reverse(Stack<T>& s) {
    Stack<T> s_temp = s;
    while (!s.isEmpty()) {
        s.pop();
    }
    if (s_temp.isEmpty()) {
        return;
    }
    while (!s_temp.isEmpty()) {
        s.push(s_temp.top());
        s_temp.pop();
    }
}

template <class T>
Stack<T> operator +(Stack<T>& s, T val) {
    Stack<T> ns = s;
    reverse(ns);
    ns.push(val);
    reverse(ns);
    return ns;
}

template <class T>
Stack<T> operator +(Stack<T>& first, Stack<T>& second) {
    Stack<T> nfirst = first;
    Stack<T> nsecond = second;
    reverse(nfirst);
    while (!nsecond.isEmpty()) {
        nfirst.push(nsecond.top());
        nsecond.pop();
    }
    reverse(nfirst);
    return nfirst;
}

#endif //MY_STACK_IMPL_H