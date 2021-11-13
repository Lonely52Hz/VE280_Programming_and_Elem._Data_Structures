#include "binaryTree.h"
#include "huffmanTree.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char *argv[])
{
    // TODO: implement this function
    ifstream bin(argv[2]);
    HuffmanTree huff(argv[1]);
    string str, out;
    Node *tar;
    while (bin >> str)
    {
        tar = huff.root;
        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] == 48)
            {
                tar = tar->leftSubtree();
            }
            else
            {
                tar = tar->rightSubtree();
            }
        }
        cout << tar->getstr();
    }
    return 0;
}