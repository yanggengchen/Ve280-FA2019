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
bool Stack<T>::isEmpty() const {
	return (head == nullptr);
}

template <class T>
size_t Stack<T>::size() const{
	size_t count = 0;
	Node<T> *current = head;
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
	if (isEmpty()) {
		stackEmpty err;
		throw err;
	}
	Node<T>* victim = head;
	head = victim->next;
	delete victim;
}

template <class T>
T Stack<T>::top() const {
	if (isEmpty()) {
		stackEmpty err;
		throw err;
	}
	return head->val;
}

template <class T>
void Stack<T>::removeAll() {
	while (!isEmpty()) {
		pop();
	}
}

template <class T>
void copy_helper(const Node<T>* node, Stack<T>& l) {
	if (node == nullptr) return;
	copy_helper(node->next, l);
	l.push(node->val);
}

template <class T>
void Stack<T>::copyFrom(const Stack &s) {
	if (!isEmpty()) removeAll();
	copy_helper(s.head, *this);
}

template <class T>
Stack<T>::Stack() {
	head = nullptr;
}

template <class T>
Stack<T>::~Stack() {
	removeAll();
}

template <class T>
Stack<T>::Stack(const Stack& s) :head(0) {
	copyFrom(s);
}

template <class T>
Stack<T>& Stack<T>::operator= (const Stack<T>& s) {
	copyFrom(s);
	return *this;
}

template <class T>
void reverse(Stack<T>& s) {
	Stack<T> reversed = Stack<T>();
	while (!s.isEmpty()) {
		reversed.push(s.top());
		s.pop();
	}
	s = reversed;
}

template <class T>
Stack<T> operator +(Stack<T>& s, T val) {
	Stack<T> result = s;
	reverse(result);
	result.push(val);
	reverse(result);
	return result;
}

template <class T>
Stack<T> operator +(Stack<T>& first, Stack<T>& second) {
	Stack<T> stack_1 = first;
	Stack<T> stack_2 = second;
	reverse(stack_1);
	while (!stack_2.isEmpty()) {
		stack_1.push(stack_2.top());
		stack_2.pop();
	}
	reverse(stack_1);
	return stack_1;
}
#endif //MY_STACK_IMPL_H