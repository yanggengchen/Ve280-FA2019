#include "binaryTree.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

/* ================================== Node =================================== */
Node::Node(const std::string &str, int num, Node *left, Node *right) {
    // TODO: implement this function.
	this->str = str;
	this->num = num;
	this->left = left;
	this->right = right;
}

Node* Node::leftSubtree() const{
    // TODO: implement this function.  
	return left;
}

void Node::setleft(Node *n) {
    // TODO: implement this function.  
	left = n;
}

Node* Node::rightSubtree() const{
    // TODO: implement this function. 
	return right;
}

void Node::setright(Node *n) {
    // TODO: implement this function.  
	right = n;
}

string Node::getstr() const {
    // TODO: implement this function.  
	return str;
}

int Node::getnum() const {
    // TODO: implement this function.
	return num;
}

void Node::incnum() {
    // TODO: implement this function.
	num++;
}

Node *Node::mergeNodes(Node *leftNode, Node *rightNode) {
    // TODO: implement this function.
	Node *result = new Node(leftNode->str + rightNode->str, leftNode->num + rightNode->num, leftNode, rightNode);
	return result;
}

/* =============================== Binary Tree =============================== */

BinaryTree::BinaryTree(Node *rootNode){
    // TODO: implement this function.
	root = rootNode;
}

static void delete_helper(Node* node) {
	//Modifies: this
	//Effects: delete this node and left and right subtree of this node
	if (node->leftSubtree() != nullptr) delete_helper(node->leftSubtree());
	if (node->rightSubtree() != nullptr) delete_helper(node->rightSubtree());
	delete node;
	node = nullptr;
}

BinaryTree::~BinaryTree() {
    // TODO: implement this function.
	delete_helper(this->root);
}

string helper_findpath(const Node* node, const string &s, string path){
	//Effects: find where s is located and return the path from node to s, where 0 represents left and 1 represent right
	if (node->getstr() == s) return path;
	if (node->leftSubtree() != nullptr) {
		string result = helper_findpath(node->leftSubtree(), s, path + "0");
		if (result != "-1") return result;
	}
	if (node->rightSubtree() != nullptr) {
		string result = helper_findpath(node->rightSubtree(), s, path + "1");
		if (result != "-1") return result;
	}
	return "-1";
}

string BinaryTree::findPath(const string &s) const{
    // TODO: implement this function.
	if (root == nullptr) return "-1";
	return helper_findpath(root, s, "");
}

int sum_helper(Node* root) {
	//Effects: sum up the num of all the nodes using recursive method
	if (root == nullptr) return 0;
	if (root->leftSubtree() == nullptr && root->rightSubtree() == nullptr) return root->getnum();
	int sum = root->getnum();
	if (root->leftSubtree() != nullptr) sum = sum + sum_helper(root->leftSubtree());
	if (root->rightSubtree() != nullptr) sum = sum + sum_helper(root->rightSubtree());
	return sum;
}

int BinaryTree::sum() const {
    // TODO: implement this function.
	return sum_helper(root);
}

int depth_helper(Node* root) {
	//Effects: using recursive method to find the height of the tree
	if (root == nullptr) return 0;
	if ((root->leftSubtree() == nullptr) && (root->rightSubtree() == nullptr)) return 1;
	int left = 0, right = 0;
	if (root->leftSubtree() != nullptr) left = depth_helper(root->leftSubtree()) + 1;
	if (root->rightSubtree() != nullptr) right = depth_helper(root->rightSubtree()) + 1;
	if (left > right) return left;
	else return right;
}

int BinaryTree::depth() const {
    // TODO: implement this function.
	return depth_helper(root);
}

void preorder_helper(Node* root) {
	//Effects: print the numbers according to the order: this, left, right
	if (root == nullptr) return;
	cout << root->getnum();
	if (root->leftSubtree() != nullptr) {
		cout << " ";
		preorder_helper(root->leftSubtree());
	}
	if (root->rightSubtree() != nullptr) {
		cout << " ";
		preorder_helper(root->rightSubtree());
	}
}

void BinaryTree::preorder_num() const {
    // TODO: implement this function.
	preorder_helper(root);
	cout << endl;
}

void inorder_helper(Node* root) {
	//Effects: print the str according to the order: left, this, right
	if (root == nullptr) return;
	if (root->leftSubtree() != nullptr) {
		inorder_helper(root->leftSubtree());
		cout << " ";
	}
	cout << root->getstr();
	if (root->rightSubtree() != nullptr) {
		cout << " ";
		inorder_helper(root->rightSubtree());
	}
}

void BinaryTree::inorder_str() const {
    // TODO: implement this function.
	inorder_helper(root);
	cout << endl;
}

void postorder_helper(Node* root) {
	//Effects: print the str according to the order: left, right, this
	if (root == nullptr) return;
	if (root->leftSubtree() != nullptr) {
		postorder_helper(root->leftSubtree());
		cout << " ";
	}
	if (root->rightSubtree() != nullptr) {
		postorder_helper(root->rightSubtree());
		cout << " ";
	}
	cout << root->getnum();
}

void BinaryTree::postorder_num() const {
    // TODO: implement this function.
	postorder_helper(root);
	cout << endl;
}

bool allPathSumGreater_helper(Node* root, int sum) {
	//Effects: determine if the sum of numbers in all path rooted in this node is greater than sum
	if ((root->leftSubtree() == nullptr) || (root->rightSubtree() == nullptr)) return sum < root->getnum();
	return (allPathSumGreater_helper(root->leftSubtree(),sum - root->getnum()) && allPathSumGreater_helper(root->rightSubtree(), sum - root->getnum()));
}

bool BinaryTree::allPathSumGreater(int sum) const {
    // TODO: implement this function.
	return allPathSumGreater_helper(root, sum);
}

bool covered_by_helper(Node* root, const Node* tree) {
	//Effects: return whether root is covered by tree
	if (root == nullptr) return 1;
	else if (tree == nullptr) return 0;
	else return (root->getnum() == tree->getnum() && covered_by_helper(root->leftSubtree(), tree->leftSubtree()) && covered_by_helper(root->rightSubtree(), tree->rightSubtree()));
}

bool BinaryTree::covered_by(const BinaryTree &tree) const {
    // TODO: implement this function.
	return covered_by_helper(root, tree.root);
}

bool contained_by_helper(Node* root, const Node* tree) {
	//Effects: return whether root is contained by tree
	return (covered_by_helper(root, tree) || covered_by_helper(root, tree->leftSubtree()) || covered_by_helper(root, tree->rightSubtree()));
}

bool BinaryTree::contained_by(const BinaryTree &tree) const {
    // TODO: implement this function.
	return contained_by_helper(root, tree.root);
}

Node* copy_helper(const Node* node) {
	//Effects: deep copy node and return the copy
	if (node == nullptr) return nullptr;
	Node* copy = new Node(node->getstr(), node->getnum(), nullptr, nullptr);
	copy->setleft(copy_helper(node->leftSubtree()));
	copy->setright(copy_helper(node->rightSubtree()));
	return copy;
}

BinaryTree BinaryTree::copy() const {
    // TODO: implement this function.
	BinaryTree copy = BinaryTree(copy_helper(root));
	return copy;
}
