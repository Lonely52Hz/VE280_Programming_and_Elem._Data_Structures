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

int findIndex(string temp, int character_num, Node** allcharacter);
// EFFECTS: return the index of temp, otherwise, return -1

void buildarry(int index, Node** allcharacter, int& character_num, string temp);
// MODIFIES: character_num
// EFFECTS: build the array that contains the 28 characters

void findsmallIndex(int& min1index, int& min2index, int character_num, Node** allcharacter);
// MODIFIES: min1index, min2index
// EFFECTS: find the two smallest index

void deletetwonode(int min1index, int min2index, int character_num, Node** allcharacter, Node* merge);
// MODIFIES: allcharacter
// EFFECTS: remove two smallest nodes


int main(int argc, char* argv[]) {
    // TODO: implement this function
    ifstream file;
    file.open(argv[argc - 1]);
    Node** allcharacter = new Node * [28]; // the arry store all 28 characters
    allcharacter[0] = new Node("\n", 0);
    int character_num = 1;
    string line;
    while (getline(file, line)) {
        allcharacter[0]->incnum();
        for (int i = 0; i < line.length(); ++i) {
            string temp = line.substr(i, 1);
            int index = findIndex(temp, character_num, allcharacter); // get the index of the character
            buildarry(index, allcharacter, character_num, temp); // build the array that can store 28 characters
        }
    }
    file.close();
    while (character_num > 1) {
        int min1index, min2index;
        findsmallIndex(min1index, min2index, character_num, allcharacter); // find two smallest index
        Node* merge = allcharacter[min2index]->mergeNodes(allcharacter[min2index], allcharacter[min1index]); // merge the two smallerst node
        deletetwonode(min1index, min2index, character_num, allcharacter, merge); // remove two smallest nodes
        character_num--;
    }
    HuffmanTree huffmantree(allcharacter[0]); // build huffmantree
    if (argc == 2) {
        file.open(argv[argc-1]);
        while (getline(file, line)) {
            for (int i = 0; i < line.length(); ++i) {
                string temp = line.substr(i, 1);
                cout << huffmantree.findPath(temp) << " ";
            }
            cout << huffmantree.findPath("\n") << " ";
        }
        file.close();
    }
    else {
        huffmantree.printTree();
    }
    delete[] allcharacter;
    return 0;
}

int findIndex(string temp, int character_num, Node** allcharacter) {
    // EFFECTS: return the index of temp, otherwise, return -1
    int flag = 0;
    int index = 0;
    for (int i = 0; i < character_num; ++i) {
        if (temp == allcharacter[i]->getstr()) {
            index = i;
            flag = 1;
            break;
        }
    }
    if (flag) {
        return index;
    }
    else {
        return -1; // if not found, return -1
    }
}

void buildarry(int index, Node** allcharacter, int& character_num, string temp) {
    // MODIFIES: character_num
    // EFFECTS: build the array that contains the 28 characters
    if (index >= 0) {
        allcharacter[index]->incnum();
    }
    else {
        allcharacter[character_num] = new Node(temp, 1);
        character_num++;
    }
}

void findsmallIndex(int& min1index, int& min2index, int character_num, Node** allcharacter) {
    // MODIFES: min1index, min2index
    // EFFECTS: find the two smallest index
    int min1fre, min2fre;
    if (allcharacter[0]->getnum() < allcharacter[1]->getnum()) {
        min1fre = allcharacter[0]->getnum();
        min2fre = allcharacter[1]->getnum();
        min1index = 0;
        min2index = 1;
    }
    else if (allcharacter[0]->getnum() == allcharacter[1]->getnum()) {
        min1fre = allcharacter[0]->getnum();
        min2fre = allcharacter[1]->getnum();
        if (allcharacter[0]->getstr()[0] < allcharacter[1]->getstr()[0]) {
            min1index = 0;
            min2index = 1;
        }
        else {
            min1index = 1;
            min2index = 0;
        }
    }
    else {
        min1fre = allcharacter[1]->getnum();
        min2fre = allcharacter[0]->getnum();
        min1index = 1;
        min2index = 0;
    } // use the first two element to initialize min1fre, min2fre, min1index, min2index
    for (int i = 2; i < character_num; ++i) { // starting from the third element
        if (allcharacter[i]->getnum() < min1fre) {
            min2fre = min1fre;
            min1fre = allcharacter[i]->getnum();
            min2index = min1index;
            min1index = i;
        } // this is easy
        else if (allcharacter[i]->getnum() == min1fre) {
            if (allcharacter[i]->getstr()[0] < allcharacter[min1index]->getstr()[0]) {
                min2fre = min1fre;
                min1fre = allcharacter[i]->getnum();
                min2index = min1index;
                min1index = i;
            } // choose the one with smaller ASCII
            else {
                if (allcharacter[i]->getnum() < min2fre) {
                    min2fre = allcharacter[i]->getnum();
                    min2index = i;
                }
                else if (allcharacter[i]->getnum() == min2fre) {
                    if (allcharacter[i]->getstr()[0] < allcharacter[min2index]->getstr()[0]) {
                        min2fre = allcharacter[i]->getnum();
                        min2index = i;
                    }
                }
            } // judge for min2 and min2index
        }
        else if (allcharacter[i]->getnum() > min1fre && allcharacter[i]->getnum() < min2fre) {
            min2fre = allcharacter[i]->getnum();
            min2index = i;
        }
        else if (allcharacter[i]->getnum() == min2fre) {
            if (allcharacter[i]->getstr()[0] < allcharacter[min2index]->getstr()[0]) {
                min2fre = allcharacter[i]->getnum();
                min2index = i;
            }
        }
    }
}

void deletetwonode(int min1index, int min2index, int character_num, Node** allcharacter, Node* merge) {
    // MODIFES: min1index, min2index
    // EFFECTS: find the two smallest index
    allcharacter[min2index] = merge; // remove min2
    for (int i = min1index; i < character_num - 1; ++i) {
        allcharacter[i] = allcharacter[i + 1]; // remove min1
    }
}
