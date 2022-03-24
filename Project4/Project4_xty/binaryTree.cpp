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
	return this->left; 
}

void Node::setleft(Node *n) {
    // TODO: implement this function.
    this->left = n;
}

Node* Node::rightSubtree() const{
    // TODO: implement this function. 
	return this->right; 
}

void Node::setright(Node *n) {
    // TODO: implement this function.
    this->right = n;
}

string Node::getstr() const {
    // TODO: implement this function. 
	return this->str; 
}

int Node::getnum() const {
    // TODO: implement this function.
	return this->num;  
}

void Node::incnum() {
    // TODO: implement this function.
    this->num += 1;
}

Node *Node::mergeNodes(Node *leftNode, Node *rightNode) {
    // TODO: implement this function.
    Node *merge = new Node(leftNode->getstr() + rightNode->getstr(), leftNode->getnum() + rightNode->getnum(), leftNode, rightNode);
    return merge;
}

/* =============================== Binary Tree =============================== */

static Node *new_root(Node *node){
    if(node == NULL) return NULL;
    Node *temp = new Node(node->getstr(), node->getnum(), new_root(node->leftSubtree()), new_root(node->rightSubtree()));
    return temp;
}

static Node *find_node(Node *node, Node *tree){
    if(node == NULL) return NULL;
    if(node->getnum() == tree->getnum()) return node;
    Node *temp;
    temp = find_node(node->leftSubtree(), tree);
    if(temp == NULL) temp = find_node(node->rightSubtree(), tree);
    return temp;
}

BinaryTree::BinaryTree(Node *rootNode){
    // TODO: implement this function.
    if(rootNode == NULL) return;
    this->root = rootNode;
}

static void delete_Node(Node *n){
    if(n->leftSubtree() != NULL) delete_Node(n->leftSubtree());
    if(n->rightSubtree() != NULL) delete_Node(n->rightSubtree());
    delete n;
    n = NULL;
}

BinaryTree::~BinaryTree() {
    // TODO: implement this function.
    if(root != NULL) delete_Node(root);
}

static string findPath_helper(const Node *n, const string &s){
    if(n == NULL) return "-1";
    if(n->getstr() == s) return "";
    if(findPath_helper(n->leftSubtree(), s) != "-1") return "0" + findPath_helper(n->leftSubtree(), s);
    if(findPath_helper(n->rightSubtree(), s) != "-1") return "1" + findPath_helper(n->rightSubtree(), s);
    return "-1";
}

string BinaryTree::findPath(const string &s) const{
    // TODO: implement this function.
    return findPath_helper(root, s);
}

static int sum_helper(Node *node){
    if(node == NULL) return 0;
    return node->getnum() + sum_helper(node->leftSubtree()) + sum_helper(node->rightSubtree());
}

int BinaryTree::sum() const {
    // TODO: implement this function.
    return sum_helper(root);

}

static int depth_helper(Node *node){
    if(node == NULL) return 0;
    int left = depth_helper(node->leftSubtree());
    int right = depth_helper(node->rightSubtree());
    return max(left, right) + 1;
}
int BinaryTree::depth() const {
    // TODO: implement this function.
    return depth_helper(root);
}

static void preorder_helper(Node *node){
    if(node == NULL) return;
    cout << node->getnum() << " ";
    preorder_helper(node->leftSubtree());
    preorder_helper(node->rightSubtree());
}

void BinaryTree::preorder_num() const {
    // TODO: implement this function.
    preorder_helper(root);
    cout << endl;
}

static void inorder_helper(Node *node){
    if(node == NULL) return;
    inorder_helper(node->leftSubtree());
    cout << node->getstr() << " ";
    inorder_helper(node->rightSubtree());
}

void BinaryTree::inorder_str() const {
    // TODO: implement this function.
    inorder_helper(root);
    cout << endl;
}

static void postorder_helper(Node *node){
    if(node == NULL) return;
    postorder_helper(node->leftSubtree());
    postorder_helper(node->rightSubtree());
    cout << node->getnum() << " ";
}

void BinaryTree::postorder_num() const {
    // TODO: implement this function.
    postorder_helper(root);
    cout << endl;
}

static bool allPath_helper(Node *node, int sum){
    if(node == NULL && sum >= 0) return false;
    if(node->getnum() > sum) return true;
    if(!allPath_helper(node->leftSubtree(), sum - node->getnum())) return false;
    return allPath_helper(node->rightSubtree(), sum - node->getnum());
}
bool BinaryTree::allPathSumGreater(int sum) const {
    // TODO: implement this function.
    return allPath_helper(root, sum);
}

static bool covered_helper(Node *node, Node *tree){
    if(node == NULL) return true;
    if(tree == NULL) return false;
    return (node->getnum() == tree->getnum()) && covered_helper(node->leftSubtree(), tree->leftSubtree()) && covered_helper(node->rightSubtree(), tree->rightSubtree());
}

bool BinaryTree::covered_by(const BinaryTree &tree) const {
    // TODO: implement this function.
    return covered_helper(root, tree.root);
}

bool BinaryTree::contained_by(const BinaryTree &tree) const {
    // TODO: implement this function.
    if(covered_helper(root, tree.root)) return true;
    Node *temp = find_node(tree.root, root);
    return covered_helper(temp, root);
}

BinaryTree BinaryTree::copy() const {
    // TODO: implement this function.
    BinaryTree tree = BinaryTree(new_root(root));
    return tree;

}



