#include "binaryTree.h"
#include "huffmanTree.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

bool compare(Node* a, Node* b) {
	//Requires: a and b are not nullptr
	//Effects: compare whether a is larger than b
	if (a->getnum() != b->getnum()) return a->getnum() > b->getnum();
	return (a->getstr())[0] > (b->getstr())[0];
}

void get_tree(Node *allnodes[55], char ch, int &num_nodes) {
	//Modifies: allnodes
	//Effects: establish the nodes according to input, observed through ch
	string str = {};
	str = str + ch;
	bool flag = 0;
	for (int i = 0; i < num_nodes; i++) {
		if (allnodes[i]->getstr() == str) {
			allnodes[i]->incnum();
			flag = 1;
			break;
		}
	}
	if (flag == 0) {
		allnodes[num_nodes] = new Node(str, 1);
		num_nodes++;
	}
}

void get_root(Node* allnodes[55], int &num_nodes) {
	//Modifies: allnodes
	//Effects: merge the nodes in the array and obtain the root for huffmanTree
	sort(&allnodes[0], &allnodes[num_nodes], compare);
	int last_position = 54;
	while (num_nodes > 1) {
		allnodes[num_nodes] = allnodes[num_nodes - 1]->mergeNodes(allnodes[num_nodes - 2], allnodes[num_nodes - 1]);
		allnodes[last_position] = allnodes[num_nodes - 1];
		allnodes[last_position - 1] = allnodes[num_nodes - 2];
		sort(&allnodes[0], &allnodes[num_nodes + 1], compare);
		allnodes[num_nodes] = nullptr;
		allnodes[num_nodes - 1] = nullptr;
		num_nodes--;
		last_position -= 2;
	}
}

int main(int argc, char *argv[]) {
    // TODO: implement this function
	ifstream iFile(argv[argc - 1]);
	//ifstream iFile("textfile.txt");
	//int argument = 2;
	Node* allnodes[55] = {};
	int num_nodes = 0;
	char ch;
	while (iFile.get(ch)) {
		get_tree(allnodes, ch, num_nodes);
	}
	get_root(allnodes, num_nodes);
	HuffmanTree tree = HuffmanTree(allnodes[0]);
	iFile.close();
	if (argc == 3) {
		tree.printTree();
	}
	if (argc == 2) {
		iFile.open(argv[1]);
		while (iFile.get(ch)) {
			string str = {};
			str = str + ch;
			cout << tree.findPath(str) << " ";
		}
	}

}