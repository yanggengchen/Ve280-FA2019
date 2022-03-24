#include "binaryTree.h"
#include "huffmanTree.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int min_freq(Node **node, const int *arr){
    int min = 0;
    int num = -1;
    for(int i = 0; i < 55; i++){
        if(arr[i] == 0) continue;
        else{
            if(min == 0) {
                min = arr[i];
                num = i;
                continue;
            }
            if(arr[i] < min || (arr[i] == min && node[i]->getstr() < node[num]->getstr())){
                min = arr[i];
                num = i;
            }
        }
    }
    return num;
}

Node *mergeNode(Node *leftNode, Node *rightNode) {
    Node *merge = new Node(leftNode->getstr() + rightNode->getstr(), leftNode->getnum() + rightNode->getnum(), leftNode, rightNode);
    return merge;
}

int main(int argc, char *argv[]) {
    // TODO: implement this function
    int flag;
    int count = 0;
    int freq[55];
    Node *node[55];
    char c;

    for(int i = 0; i < 55; i++){
        freq[i] = 0;
    }

    if(argc == 3) flag = 1;
    else flag = 0;

    string name = argv[argc - 1];
    ifstream file;
    file.open(name);



    while(file.get(c)){
        if(c == ' ') freq[26] ++;
        else if(c == '\n') freq[27] ++;
        else freq[c - 'a'] ++;
    }

    for(int i = 0; i < 26; i++){
        if(freq[i] != 0){
            count ++;
            char t = i + 'a';
            string s = string(1, t);
            node[i] = new Node(s, freq[i]);
        }
    }
    if(freq[26] != 0){
        node[26] = new Node(" ", freq[26]);
        count ++;
    }
    if(freq[27] != 0){
        node[27] = new Node("\n", freq[27]);
        count ++;
    }

    int index = 28;
    while(count > 1){
        int right = min_freq(node, freq);
        freq[right] = 0;
        int left = min_freq(node, freq);
        freq[left] = 0;

        node[index] = mergeNode(node[left], node[right]);
        freq[index] = node[index]->getnum();
        index ++;
        count --;
    }

    HuffmanTree tree(node[index - 1]);

    if(flag == 1) tree.printTree();
    else{
        file.close();
        file.open(name);
        while(file.get(c)){
            string s = string(1, c);
            cout << tree.findPath(s);
            cout << " ";
        }
    }
    file.close();
    return 0;
}