#ifndef DLIST_IMPL_H
#define DLIST_IMPL_H

#include "dlist.h"
using namespace std;

template <class T>
bool Dlist<T>::isEmpty() const {
	return (first == nullptr);
}

template <class T>
void Dlist<T>::insertFront(T* op){
	int flag = 0;
	if (isEmpty()) flag = 1;
	node* np = new node;
	np->next = first;
	np->prev = nullptr;
	np->op = op;
	if (flag == 0) first->prev = np;
	first = np;
	if (flag == 1)	last = np;
}

template <class T>
void Dlist<T>::insertBack(T* op) {
	int flag = 0;
	if (isEmpty()) flag = 1;
	node* np = new node;
	np->next = nullptr;
	np->prev = last;
	np->op = op;
	if (flag == 0) last->next = np;
	last = np;
	if (flag == 1) first = np;
}

template <class T>
T* Dlist<T>::removeFront() {
	if (isEmpty()) {
		emptyList err;
		throw err;
	}
	node* front = first;
	T* result = first->op;
	if (first == last) {
		last = nullptr;
		first = nullptr;
	}
	else {
		first = front->next;
		first->prev = nullptr;
	}
	delete front;
	return result;
}

template <class T>
T* Dlist<T>::removeBack() {
	if (isEmpty()) {
		emptyList err;
		throw err;
	}
	node* end = last;
	T* result = last->op;
	if (first == last) {
		first = nullptr;
		last = nullptr;
	}
	else {
		last = end->prev;
		last->next = nullptr;
	}
	delete end;
	return result;
}

template <class T>
T* Dlist<T>::remove(bool (*cmp)(const T*, const T*), T* ref) {
	node* cur = first;
	if (cur == nullptr) return nullptr;
	while (!cmp(ref, cur->op)) {
		cur = cur->next;
		if (cur == nullptr) return nullptr;
	}
	if (cmp(cur->op, first->op)) {
		T* result = removeFront();
		return result;
	}
	else if (cmp(cur->op, last->op)) {
		T* result = removeBack();
		return result;
	}
	else {
		T* result = cur->op;
		cur->prev->next = cur->next;
		cur->next->prev = cur->prev;
		delete cur;
		return result;
	}
	return nullptr;
}

template <class T>
void Dlist<T>::removeAll() {
	while (!isEmpty()) {
		T *op = removeFront();
		delete op;
	}
}

template <class T>
void Dlist<T>::copyAll(const Dlist& l) {
	node* cur = l.first;
	while (cur != nullptr) {
		T* op = new T(*cur->op);
		this->insertBack(op);
		cur = cur->next;
	}
}

template <class T>
Dlist<T>::Dlist() {
	first = nullptr;
	last = nullptr;
}

template <class T>
Dlist<T>::~Dlist() {
	removeAll();
}

template <class T>
Dlist<T>::Dlist(const Dlist& l) :first(0), last(0){
	copyAll(l);
}

template <class T>
Dlist<T>& Dlist<T>::operator= (const Dlist<T>& l) {
	copyAll(l);
	return *this;
}

#endif