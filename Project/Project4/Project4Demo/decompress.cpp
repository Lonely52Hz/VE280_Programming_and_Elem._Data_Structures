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

int main(int argc, char *argv[]) {
    // TODO: implement this function
    HuffmanTree huffmantree(argv[1]);
    ifstream binaryfile;
    binaryfile.open(argv[2]);
    string binarystring;
    while (binaryfile >> binarystring) {
        Node* node = huffmantree.root;
        for (int i = 0; i < binarystring.length(); ++i) {
            if (binarystring[i] == '0') {
                node = node->leftSubtree();// leftsubtree
            }
            else {
                node = node->rightSubtree(); // rightsubtree
            }
        }
        cout << node->getstr();
    }
    binaryfile.close();
    return 0;
}