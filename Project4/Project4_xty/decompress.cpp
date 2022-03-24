#include "binaryTree.h"
#include "huffmanTree.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
    // TODO: implement this function
    if(argc < 3 || argc > 3){
        cout << "Wrong number of argument!" << endl;
        return 0;
    }
    string file1 = argv[1];
    string file2 = argv[2];

    HuffmanTree tree(file1);
    ifstream file;
    file.open(file2);

    string code;
    int flag = 1;
    while(getline(file, code, ' ') && flag == 1){
        flag = 0;
        if(code == tree.findPath(" ")) {
            cout << " ";
            flag = 1;
            continue;
        }
        else if(code == tree.findPath("\n")) {
            cout << endl;
            flag = 1;
            continue;
        }
        else{
            for(int i = 0; i < 26; i++){
                if(code == tree.findPath(string(1, i + 'a'))) {
                    cout << string(1, i + 'a');
                    flag = 1;
                    break;
                }
            }
            continue;
        }
    }
    if(flag == 0){
        cout << "No matching character for the binary code!" << endl;
    }
    file.close();
    return 0;
}