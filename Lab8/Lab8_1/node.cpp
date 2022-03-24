#include "node.h"
#include <iostream>
using namespace std;



	//Node::Node(int _value, int _n = 2):value(_value), n(_n), child_num(0), parent(nullptr), children(new Node*[n]), height(0){}
		// EFFECTS: create a root node with value and n

	void Node::addChild(Node* child)
	// REQUIRES: n of the child node is the same with n of this
	// EFFECTS: add the node child to the children array
	//          throw an exception tooManyChildren when child_num exceed n
	{
		if (child_num >= n) {
			tooManyChildren err;
			throw err;
		}
		children[child_num] = new Node(child->value, n);
		children[child_num]->parent = this;
		child_num++;
	}

	Node::~Node()
		// EFFECTS: destroy the whole tree rooted at sub
	{
		for (int i = 0; i < child_num; i++) {
			delete children[i];
		}
		delete[] children;
		children = nullptr;
	}

	void Node::addChild(int _value)
		// EFFECTS: create a child node with value and add it to the children array
		//			throw an exception tooManyChildren when child_num exceed n
	{
		if (child_num == n) {
			tooManyChildren err;
			throw err;
		}
		Node temp = Node(_value, n);
		addChild(&temp);
	}

	void Node::traverse()
		// EFFECTS: print the value of the nodes using a pre-order traversal,
		//          separated by a space.
		//          A pre-order traversal print the value of the node
		//          and then traverse its child nodes
		//          according to the sequence in children array.
		//          For example, the output of the tree above is
		//          1 2 4 5 6 8 9 3 7
		//          And the output of the tree below is
		//          1 3 5 6 2 4
	{
		cout << value << " ";
		for (int i = 0; i < child_num; i++) {
			children[i]->traverse();
		}
	}

	bool Node::contain(Node* sub)
		// EFFECTS: return whether the tree rooted at sub is a subtree of this
	{
		if (this->getHeight() != sub->getHeight()) {
			for (int i = 0; i < child_num; i++) {
				if (children[i]->contain(sub) == 1) return 1;
			}
			return 0;
		}
		else {
			if (((this->value == sub->value) && (this->n == sub->n) && (this->child_num == sub->child_num)) == 0) return 0;
			for (int i = 0; i < child_num; i++) {
				if (children[i]->contain(sub->children[i]) == 0) return 0;
			}
			return 1;
		}
	}

	int Node::getHeight()
		// EFFECTS: return height of this
	{
		if (child_num == 0) return 0;
		for (int i = 0; i < child_num; i++) {
			if (height < children[i]->getHeight() + 1) height = children[i]->getHeight() + 1;
		}
		return height;
	}

	Node& Node::operator[](int i)
		// EFFECTS: return a reference of (i+1) th child node of this,
		//          e.g. node1[0] returns a reference of the first child node of node1
		//          if i is invalid, throw an invalidIndex
	{
		if (child_num <= i) {
			invalidIndex err;
			throw err;
		}
		return *children[i];
	}


