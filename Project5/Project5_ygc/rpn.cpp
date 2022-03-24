#include "dlist.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cassert>

using namespace std;

class parenthesis_mismatch{};
class not_enough_operants{};
class divide_by_zero{};
class too_many_operants{};

template <class T>
class Stack {
	Dlist<T> list;
public:
	void push(T* val);
	//Effects: push val into the stack
	T* pop();
	//Effects: pop the front of the stack, throw err if empty
	bool Stack_isEmpty();
	//Effects: return whether the stack is empty
	T* top();
	//Effects: return a pointer to the top of the stack
	void removeAll();
	//Effects: clear the stack
};

template <class T>
void Stack<T>::push(T* val) {
	this->list.insertFront(val);
}

template <class T>
T* Stack<T>::pop() {
	return this->list.removeFront();
}

template <class T>
bool Stack<T>::Stack_isEmpty() {
	return this->list.isEmpty();
}

template <class T>
T* Stack<T>::top() {
	T* temp = list.removeFront();
	list.insertFront(temp);
	return temp;
}

template <class T>
void Stack<T>::removeAll() {
	while (!list.isEmpty()) {
		T* op = list.removeFront();
		delete op;
	}
}

void trans_rpn(istringstream &cin_Stream, string &read_cin, string &output, Stack<string> &operator_Stack) {
	//Effects: read from the input and push them either into output or operator stack
	while (cin_Stream >> read_cin) {
		if ((read_cin == "+") || (read_cin == "-") || (read_cin == "*") || (read_cin == "/")) {
			while ((!operator_Stack.Stack_isEmpty()) && (!((read_cin == "*" || read_cin == "/") && (*operator_Stack.top() == "+" || *operator_Stack.top() == "-"))) && (*operator_Stack.top() != "(")) {
				string* temp_op = operator_Stack.pop();
				output = output + *temp_op + " ";
				delete temp_op;
			}
			string* new_operator = new string(read_cin);
			operator_Stack.push(new_operator);
		}
		else if (read_cin == "(") {
			string* new_operator = new string(read_cin);
			operator_Stack.push(new_operator);
		}
		else if (read_cin == ")") {
			while (*operator_Stack.top() != "(") {
				string* temp_op = operator_Stack.pop();
				output = output + *temp_op + " ";
				delete temp_op;
				if (operator_Stack.Stack_isEmpty()) {
					parenthesis_mismatch err;
					operator_Stack.removeAll();
					throw err;
				}
			}
			string* temp_op = operator_Stack.pop();
			delete temp_op;

		}
		else {
			output = output + read_cin + " ";
		}
	}
}

void trans_rpn_clear_stack(string& output, Stack<string>& operator_Stack) {
	//Effects: pop the rest of the elements in the operator stack into output
	while (!operator_Stack.Stack_isEmpty()) {
		string* temp_op = operator_Stack.pop();
		if (*temp_op == "(") {
			parenthesis_mismatch err;
			delete temp_op;
			operator_Stack.removeAll();
			throw err;
		}
		output = output + *temp_op + " ";
		delete temp_op;
	}
}

void calculation(Stack<int> &Stack_int, istringstream &rpn_stream,string &read_rpn) {
	//Effects: does calculation given the element obtained from the expression
	if (read_rpn == "+" || read_rpn == "-" || read_rpn == "*" || read_rpn == "/") {
		if (Stack_int.Stack_isEmpty()) {
			not_enough_operants err;
			throw err;
		}
		int* right = Stack_int.pop();
		if (Stack_int.Stack_isEmpty()) {
			not_enough_operants err;
			delete right;
			throw err;
		}
		int* left = Stack_int.pop();
		int* result = new int;
		if (read_rpn == "+") {
			*result = *left + *right;
			Stack_int.push(result);
		}
		else if (read_rpn == "-") {
			*result = *left - *right;
			Stack_int.push(result);
		}
		else if (read_rpn == "*") {
			*result = *left * *right;
			Stack_int.push(result);
		}
		else {
			if (*right == 0) {
				divide_by_zero err;
				delete left;
				delete right;
				delete result;
				Stack_int.removeAll();
				throw err;
			}
			*result = *left / *right;
			Stack_int.push(result);
		}
		delete left;
		delete right;
	}
	else {
		int* temp = new int(atoi(read_rpn.c_str()));
		Stack_int.push(temp);
	}
}


int main(int argc, char* argv[]) {
	string line;
	getline(cin, line);
	istringstream cin_Stream(line);
	string read_cin;
	string output = {};
	Stack<string> operator_Stack;
	try {
		trans_rpn(cin_Stream, read_cin, output, operator_Stack);
	}
	catch (...) {
		cout << "ERROR: Parenthesis mismatch" << endl;
		return 0;
	}
	try {
		trans_rpn_clear_stack(output, operator_Stack);
	}
	catch (...) {
		cout << "ERROR: Parenthesis mismatch" << endl;
		return 0;
	}
	cout << output << endl;
	Stack<int> Stack_int;
	istringstream rpn_stream(output);
	string read_rpn;
	while (rpn_stream >> read_rpn) {
		try {
			calculation(Stack_int, rpn_stream, read_rpn);
		}
		catch (not_enough_operants err) {
			cout << "ERROR: Not enough operands" << endl;
			return 0;
		}
		catch (divide_by_zero err) {
			cout << "ERROR: Divide by zero" << endl;
			return 0;
		}
	}
	int* final_result = Stack_int.pop();
	try {
		if (!Stack_int.Stack_isEmpty()) {
			too_many_operants err;
			Stack_int.removeAll();
			delete final_result;
			throw err;
		}
	}
	catch (too_many_operants err) {
		cout << "ERROR: Too many operands" << endl;
		return 0;
	}
	cout << *final_result << endl;
	delete final_result;
	return 0;
}