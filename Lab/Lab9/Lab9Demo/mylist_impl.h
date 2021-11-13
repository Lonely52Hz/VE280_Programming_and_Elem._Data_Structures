//
// Created by cyx on 20-5-29.
//

#ifndef INTLIST_IMPL_H
#define INTLIST_IMPL_H

#include <iostream>
#include "mylist.h"

template <class T>
void List<T>::print()
{
    node_t<T>* itr = first;
    while(itr){
        std::cout << itr->val;
        itr = itr->next;
    }
    std::cout << "\n";
}

template <class T>
void List<T>::removeAll() {
    while (!isEmpty()) {
        removeFront();
    }
}

template <class T>
void List<T>::copyFrom(const List& l) {
    if (!isEmpty()) {
        removeAll();
    }
    if (!l.first) {
        return;
    }
    node_t<T>* current = l.first;
    while (current) {
        this->insertBack(current->val);
        current = current->next;
    }
}

template <class T>
bool List<T>::isEmpty() const {
    return !first;
}

template <class T>
void List<T>::insertBack(T val) {
    node_t<T>* np = new node_t<T>;
    np->next = NULL;
    np->val = val;
    if (isEmpty()) {
        first = last = np;
    }
    else {
        last->next = np;
        last = np;
    }
}

template <class T>
T List<T>::removeFront() {
    if (isEmpty()) {
        emptyList e;
        throw e;
    }
    node_t<T>* victim = first;
    first = victim->next;
    T result = victim->val;
    delete victim;
    return result;
}

template <class T>
const node_t<T>* List<T>::returnHead() const {
    return first;
}

template <class T>
List<T>::List() {
    first = NULL;
    last = NULL;
}

template <class T>
List<T>::List(const List& l) {
    first = NULL;
    last = NULL;
    copyFrom(l);
}

template <class T>
List<T>& List<T>::operator=(const List<T>& l) {
    if (this != &l) {
        removeAll();
        copyFrom(l);
    }
    return* this;
}

template <class T>
List<T>::~List() {
    removeAll();
}

bool isLarger(const List<int>& a, const List<int>& b) {
    int a_num = 0;
    int b_num = 0;
    bool flag = false;
    if (a.isEmpty() && b.isEmpty()) {
        return false;
    }
    else if (!a.isEmpty() && b.isEmpty()) {
        return true;
    }
    else if (a.isEmpty() && !b.isEmpty()) {
        return false;
    }
    else {
        node_t<int>* current_a =(node_t<int> *) a.returnHead();
        while (current_a) {
            a_num++;
            current_a = current_a->next;
        }
        node_t<int>* current_b = (node_t<int>*) b.returnHead();
        while (current_b) {
            b_num++;
            current_b = current_b->next;
        }
        if (a_num > b_num) {
            return true;
        }
        else if (a_num < b_num) {
            return false;
        }
        else {
            current_a = (node_t<int>*) a.returnHead();
            current_b = (node_t<int>*) b.returnHead();
            while (current_a) {
                if (current_a->val > current_b->val) {
                    flag = true;
                }
                else if (current_a->val < current_b->val) {
                    flag = false;
                }
                current_a = current_a->next;
                current_b = current_b->next;
            }
        }
    }
    return flag;
}

List<int> Add(const List<int>& a, const List<int>& b) {
    int carry = 0;
    int temp = 0;
    node_t<int>* current_a = (node_t<int>*) a.returnHead();
    node_t<int>* current_b = (node_t<int>*) b.returnHead();
    List<int> ans;
    if (a.isEmpty() && b.isEmpty()) {
        return a;
    }
    else if (!a.isEmpty() && b.isEmpty()) {
        return a;
    }
    else if (a.isEmpty() && !b.isEmpty()) {
        return b;
    }
    else {
        while (current_a || current_b) {
            if (current_a && current_b) {
                temp = current_a->val + current_b->val + carry;
                if (temp >= 10) {
                    carry = 1;
                    ans.insertBack(temp - 10);
                }
                else {
                    carry = 0;
                    ans.insertBack(temp);
                }
                current_a = current_a->next;
                current_b = current_b->next;
                if (!current_a && !current_b) {
                    if (carry == 1) {
                        ans.insertBack(1);
                    }
                }
            }
            else if (current_a && !current_b) {
                temp = current_a->val + carry;
                if (temp >= 10) {
                    carry = 1;
                    ans.insertBack(temp - 10);
                }
                else {
                    carry = 0;
                    ans.insertBack(temp);
                }
                current_a = current_a->next;
                if (!current_a) {
                    if (carry == 1) {
                        ans.insertBack(1);
                    }
                }
            }
            else {
                temp = current_b->val + carry;
                if (temp >= 10) {
                    carry = 1;
                    ans.insertBack(temp - 10);
                }
                else {
                    carry = 0;
                    ans.insertBack(temp);
                }
                current_b = current_b->next;
                if (!current_b) {
                    if (carry == 1) {
                        ans.insertBack(1);
                    }
                }
            }
        }
    }
    return ans;
}

#endif //INTLIST_IMPL_H
