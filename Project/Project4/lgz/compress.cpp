#include "binaryTree.h"
#include "huffmanTree.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

int findNode(Node **nodes, int size, string str)
{
    for (int i = 0; i < size; i++)
    {
        if (nodes[i]->getstr() == str)
        {
            return i;
        }
    }
    return -1;
}

int *leastTwo(Node **nodes, int size)
{
    int min1 = 1e7, min2 = 1e8, index1 = 0, index2 = 0, te;
    for (int i = 0; i < size; i++)
    {
        if (nodes[i]->getnum() < min1)
        {
            min2 = min1;
            index2 = index1;
            min1 = nodes[i]->getnum();
            index1 = i;
        }
        else if (nodes[i]->getnum() == min1)
        {
            if (nodes[i]->getstr()[0] < nodes[index1]->getstr()[0])
            {
                min2 = min1;
                index2 = index1;
                min1 = nodes[i]->getnum();
                index1 = i;
            }
            else
            {
                if (nodes[i]->getnum() == min2)
                {
                    if (nodes[i]->getstr()[0] < nodes[index2]->getstr()[0])
                    {
                        min2 = nodes[i]->getnum();
                        index2 = i;
                    }
                }
                else
                {
                    min2 = nodes[i]->getnum();
                    index2 = i;
                }
            }
        }
        else if (nodes[i]->getnum() > min1 && nodes[i]->getnum() < min2)
        {
            min2 = nodes[i]->getnum();
            index2 = i;
        }
        else if (nodes[i]->getnum() == min2)
        {
            if (nodes[i]->getstr()[0] < nodes[index2]->getstr()[0])
            {
                min2 = nodes[i]->getnum();
                index2 = i;
            }
        }
    }
    int *temp = new int[2];
    temp[0] = index1;
    temp[1] = index2;
    return temp;
}

int main(int argc, char *argv[])
{
    // TODO: implement this function
    string filename, line;
    filename = argv[argc - 1];
    ifstream in(filename);
    Node **nodes = new Node *[2000];
    Node *n = new Node("\n", 0);
    nodes[0] = n;
    int size = 1;
    vector<string> content;
    while (getline(in, line))
    {
        content.push_back(line);
        for (int i = 0; i < line.length(); i++)
        {
            string str(1, line[i]);
            if (findNode(nodes, size, str) == -1)
            {
                nodes[size] = new Node(str, 1);
                size++;
            }
            else
            {
                nodes[findNode(nodes, size, str)]->incnum();
            }
        }
        nodes[0]->incnum();
    }

    int *temp;
    while (size > 1)
    {
        temp = leastTwo(nodes, size);
        Node *me = nodes[0]->mergeNodes(nodes[temp[1]], nodes[temp[0]]);
        nodes[temp[1]] = me;
        for (int i = temp[0]; i < size - 1; i++)
        {
            nodes[i] = nodes[i + 1];
        }
        nodes[--size] = NULL;
        delete[] temp;
    }
    HuffmanTree huff(nodes[0]);
    if (argc == 3)
    {
        huff.printTree();
    }
    else
    {
        for (int i = 0; i < content.size(); i++)
        {
            for (int j = 0; j < content[i].length(); j++)
            {
                string st(1, content[i][j]);
                cout << huff.findPath(st) << ' ';
            }
            cout << huff.findPath("\n") << ' ';
        }
    }
    delete[] nodes;
    return 0;
}