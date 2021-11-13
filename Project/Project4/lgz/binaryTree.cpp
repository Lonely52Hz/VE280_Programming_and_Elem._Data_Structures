#include "binaryTree.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

/* ================================== Node =================================== */
Node::Node(const std::string &str, int num, Node *left, Node *right)
{
    // TODO: implement this function.
    this->str = str;
    this->num = num;
    this->left = left;
    this->right = right;
}

Node *Node::leftSubtree() const
{
    // TODO: implement this function.
    return left;
}

void Node::setleft(Node *n)
{
    // TODO: implement this function.
    left = n;
}

Node *Node::rightSubtree() const
{
    // TODO: implement this function.
    return right;
}

void Node::setright(Node *n)
{
    // TODO: implement this function.
    right = n;
}

string Node::getstr() const
{
    // TODO: implement this function.
    return str;
}

int Node::getnum() const
{
    // TODO: implement this function.
    return num;
}

void Node::incnum()
{
    // TODO: implement this function.
    num++;
}

Node *Node::mergeNodes(Node *leftNode, Node *rightNode)
{
    // TODO: implement this function.
    Node *a = new Node(leftNode->str + rightNode->str, leftNode->num + rightNode->num, leftNode, rightNode);
    return a;
}

/* =============================== Binary Tree =============================== */

BinaryTree::BinaryTree(Node *rootNode)
{
    // TODO: implement this function.
    root = rootNode;
}

void remove(Node *me)
{
    if (me == NULL)
    {
        return;
    }
    remove(me->leftSubtree());
    remove(me->rightSubtree());
    delete me;
}

BinaryTree::~BinaryTree()
{
    // TODO: implement this function.
    remove(root);
}

string findPath_helper(const string &s, Node *me, string result)
{
    if (me->getstr() == s)
    {
        return result;
    }
    string ans = "";
    if (me->leftSubtree() != nullptr)
    {
        ans += findPath_helper(s, me->leftSubtree(), result + '0');
    }
    if (me->rightSubtree() != nullptr)
    {
        ans += findPath_helper(s, me->rightSubtree(), result + '1');
    }
    return ans;
}

string BinaryTree::findPath(const string &s) const
{
    // TODO: implement this function.
    if (root->getstr() == s)
    {
        return "";
    }
    string result = findPath_helper(s, root, "");
    if (result == "")
    {
        return "-1";
    }
    return result;
}

int sum_helper(Node *me, int sum)
{
    int temp = sum;
    if (me->leftSubtree() != nullptr)
    {
        sum += sum_helper(me->leftSubtree(), temp);
    }
    if (me->rightSubtree() != nullptr)
    {
        sum += sum_helper(me->rightSubtree(), temp);
    }
    sum += me->getnum();
    return sum;
}

int BinaryTree::sum() const
{
    // TODO: implement this function.
    return sum_helper(root, 0);
}

int depth_helper(Node *me)
{
    if (me == NULL)
    {
        return 0;
    }
    return max(depth_helper(me->leftSubtree()), depth_helper(me->rightSubtree())) + 1;
}

int BinaryTree::depth() const
{
    // TODO: implement this function.
    return depth_helper(root);
}

void pre_helper(Node *me)
{
    if (me == NULL)
    {
        return;
    }
    else
    {
        std::cout << me->getnum() << ' ';
        pre_helper(me->leftSubtree());
        pre_helper(me->rightSubtree());
    }
}

void BinaryTree::preorder_num() const
{
    // TODO: implement this function.
    pre_helper(root);
    std::cout << std::endl;
}

void in_helper(Node *me)
{
    if (me == NULL)
    {
        return;
    }
    else
    {
        in_helper(me->leftSubtree());
        std::cout << me->getstr() << ' ';
        in_helper(me->rightSubtree());
    }
}

void BinaryTree::inorder_str() const
{
    // TODO: implement this function.
    in_helper(root);
    std::cout << std::endl;
}

void post_helper(Node *me)
{
    if (me == NULL)
    {
        return;
    }
    else
    {
        post_helper(me->leftSubtree());
        post_helper(me->rightSubtree());
        std::cout << me->getnum() << ' ';
    }
}

void BinaryTree::postorder_num() const
{
    // TODO: implement this function.
    post_helper(root);
    std::cout << std::endl;
}

int shortestPath(Node *me)
{
    if (me == NULL)
    {
        return 0;
    }
    return min(shortestPath(me->leftSubtree()), shortestPath(me->rightSubtree())) + me->getnum();
}

bool BinaryTree::allPathSumGreater(int sum) const
{
    // TODO: implement this function.
    //std::cout << shortestPath(root) << std::endl;
    return shortestPath(root) > sum;
}

bool cover_helper(Node *me, Node *tree)
{
    if (me == nullptr)
    {
        return true;
    }
    else if (tree != nullptr)
    {
        return (me->getnum() == tree->getnum()) && cover_helper(me->leftSubtree(), tree->leftSubtree()) && cover_helper(me->rightSubtree(), tree->rightSubtree());
    }
    else
    {
        return false;
    }
}

bool BinaryTree::covered_by(const BinaryTree &tree) const
{
    // TODO: implement this function.
    return cover_helper(this->root, tree.root);
}

bool contain_helper(Node *me, Node *tree)
{
    if (me == nullptr)
    {
        return true;
    }
    else if (tree != nullptr)
    {
        return cover_helper(me, tree) || contain_helper(me, tree->leftSubtree()) || contain_helper(me, tree->rightSubtree());
    }
    else
    {
        return false;
    }
}

bool BinaryTree::contained_by(const BinaryTree &tree) const
{
    // TODO: implement this function.
    return contain_helper(this->root, tree.root);
}

Node *copy_helper(Node *me)
{
    if (me == NULL)
    {
        return NULL;
    }
    Node *a = new Node(me->getstr(), me->getnum());
    a->setleft(copy_helper(me->leftSubtree()));
    a->setright(copy_helper(me->rightSubtree()));
    return a;
}

BinaryTree BinaryTree::copy() const
{
    // TODO: implement this function.
    Node *newroot = copy_helper(root);
    return BinaryTree(newroot);
}
