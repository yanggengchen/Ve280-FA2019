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
bool List<T>::isEmpty() const {
	return (first == nullptr);
}

template <class T>
void List<T>::insertBack(T val) {
	node_t<T> *np = new node_t<T>;
	np->next = nullptr;
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
const node_t<T>* List<T>::returnHead() const {
	return first;
}

template <class T>
T List<T>::removeFront() {
	if (first == nullptr) {
		emptyList err;
		throw err;
	}
	node_t<T>* victim = first;
	first = victim->next;
	T result = victim->val;
	delete victim;
	return result;
}

template <class T>
void List<T>::removeAll() {
	while (!isEmpty()) {
		removeFront();
	}
}

template <class T>
void copy_helper(const node_t<T>* node, List<T>& l) {
	if (node == nullptr) return;
	l.insertBack(node->val);
	copy_helper(node->next, l);
}

template <class T>
void List<T>::copyFrom(const List& l) {
	if (!isEmpty()) removeAll();
	copy_helper(l.returnHead(), *this);
}

template <class T>
List<T>::List() {
	first = nullptr;
	last = nullptr;
}

template <class T>
List<T>::~List() {
	removeAll();
}
template <class T>
List<T>::List(const List& l) :first(0), last(0){
	copyFrom(l);
}

template <class T>
List<T>& List<T>::operator=(const List<T>& l) {
	copyFrom(l);
	return *this;
}

int getSize_list(const List<int>& l) {
	int count = 0;
	const node_t<int>* current = l.returnHead();
	while (current) {
		count++;
		current = current->next;
	}
	return count;
}

int compare(const node_t<int> *a, const node_t<int> *b) {
	if (a->next == nullptr) {
		if (a->val > b->val) return 1;
		else if (a->val < b->val) return 0;
		else return -1;
	}
	int result = compare(a->next, b->next);
	if (result == 1 || result == 0) return result;
	else {
		if (a->val > b->val) return 1;
		else if (a->val < b->val) return 0;
		else return -1;
	}
}

bool isLarger(const List<int>& a, const List<int>& b) {
	if (getSize_list(a) > getSize_list(b)) return 1;
	if ((getSize_list(a) < getSize_list(b)) || (getSize_list(a) == 0 && getSize_list(b) == 0)) return 0;
	int result = compare(a.returnHead(), b.returnHead());
	if (result == -1) return 0;
	else return result;
}

void Add_helper(const node_t<int> *a, const node_t<int> *b, int carry, List<int> &l) {
	if (a != nullptr && b != nullptr) {
		int num = a->val + b->val + carry;
		if (num >= 10) {
			carry = 1;
			l.insertBack(num - 10);
		}
		else {
			carry = 0;
			l.insertBack(num);
		}
		Add_helper(a->next, b->next, carry, l);
	}
	else if (a == nullptr && b != nullptr) {
		int num = b->val + carry;
		if (num >= 10) {
			carry = 1;
			l.insertBack(num - 10);
		}
		else {
			carry = 0;
			l.insertBack(num);
		}
		Add_helper(nullptr, b->next, carry, l);
	}
	else if (a != nullptr && b == nullptr) {
		int num = a->val + carry;
		if (num >= 10) {
			carry = 1;
			l.insertBack(num - 10);
		}
		else {
			carry = 0;
			l.insertBack(num);
		}
		Add_helper(a->next, nullptr, carry, l);
	}
	else {
		if (carry == 1) {
			l.insertBack(1);
			return;
		}
		return;
	}
}

List<int> Add(const List<int>& a, const List<int>& b) {
	List<int> l = List<int>();
	Add_helper(a.returnHead(), b.returnHead(), 0, l);
	return l;
}
#endif //INTLIST_IMPL_H
