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

void decode(Node* node, istringstream &strStream) {
	//Effects: print the str of the node at the path given in strStream, rooted in node
	char path;
	strStream >> path;
	if (!strStream) {
		cout << node->getstr();
	}
	else{
		if (path == '0') {
			decode(node->leftSubtree(), strStream);
		}
		else {
			decode(node->rightSubtree(), strStream);
		}
	}
}

int main(int argc, char *argv[]) {
    // TODO: implement this function
	HuffmanTree tree = HuffmanTree(argv[1]);
	ifstream iFile(argv[2]);
	while (iFile) {
		string str;
		iFile >> str;
		if (iFile) {
			istringstream strStream(str);
			decode(tree.root, strStream);
		}
	}
	iFile.close();
}