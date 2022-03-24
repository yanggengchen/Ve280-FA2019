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
	if (a->getnum() != b->getnum()) return a->getnum() > b->getnum();
	return (a->getstr())[0] > (b->getstr())[0];
}

int main(int argc, char* argv[]) {
	// TODO: implement this function
	ifstream iFile("textfile.txt");
	Node* allnodes[55] = {};
	int num_nodes = 0;
	char ch;
	while (iFile.get(ch)) {
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
	HuffmanTree tree = HuffmanTree(allnodes[0]);
	iFile.close();
	tree.preorder_num();
}