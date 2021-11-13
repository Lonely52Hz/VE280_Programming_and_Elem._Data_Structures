#include "binaryTree.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

/* ======================== Helperfunction_Decalaration ========================= */
void destructor_helper(Node* root);
// MODIFIES: root
// EFFECTIS: free the memeory recursively

string findPath_helper(Node* root, const string& s);
// EFFECTIS: the helper function of findPath

int sum_helper(Node* root);
// EFFECTIS: the helper function of sum

int depth_helper(Node* root);
// EFFECTS: the helper fucntion of depth

void preorder_num_helper(Node* root);
// EFFECTS: the helper fucntion of preorder_sum

void inorder_str_helper(Node* root);
// EFFECTS: the helper function of inorder_str

void postorder_num_helper(Node* root);
// EFFECTS: the helper function of postorder_num

int allPathSumGreater_helper(Node* root);
// EFFECTS: the helper function of allPathSumGreat, return the smallest sum

bool covered_by_helper(Node* smalltree, Node* largetree);
// EFFECTS: the helper function of cover_by

bool contained_by_helper(Node* smalltree, Node* largetree);
// EFFECTS: the helper function of contained_by

Node* copy_helper(Node* root);
// EFFECTS: the helper function of copy

/* ================================== Node =================================== */
Node::Node(const std::string& str, int num, Node* left, Node* right) {
    // TODO: implement this function.
    this->str = str;
    this->num = num;
    this->left = left;
    this->right = right;
}

Node* Node::leftSubtree() const {
    // TODO: implement this function.  
    return left;
}

void Node::setleft(Node* n) {
    // TODO: implement this function.  
    left = n;
}

Node* Node::rightSubtree() const {
    // TODO: implement this function.  
    return right;
}

void Node::setright(Node* n) {
    // TODO: implement this function.  
    right = n;
}

string Node::getstr() const {
    // TODO: implement this function.  
    return str;
}

int Node::getnum() const {
    // TODO: implement this function.  
    return num;
}

void Node::incnum() {
    // TODO: implement this function.
    num++;
}

Node* Node::mergeNodes(Node* leftNode, Node* rightNode) {
    // TODO: implement this function.
    ostringstream n_str;
    n_str << leftNode->getstr() << rightNode->getstr();
    int n_num = leftNode->getnum() + rightNode->getnum();
    Node* np = new Node(n_str.str(), n_num, leftNode, rightNode);
    return np;
}

/* =============================== Binary Tree =============================== */

BinaryTree::BinaryTree(Node* rootNode) {
    // TODO: implement this function.
    root = rootNode;
}

void destructor_helper(Node* root) {
    // MODIFIES: root
    // EFFECTIS: free the memeory recursively
    if (root == nullptr) {
        return;
    }
    destructor_helper(root->leftSubtree());
    destructor_helper(root->rightSubtree());
    delete root;
}

BinaryTree::~BinaryTree() {
    // TODO: implement this function.
    destructor_helper(root);
}

string findPath_helper(Node* root, const string& s) {
    // EFFECTIS: the helper function of findPath
    if (root == nullptr) {
        return "-1";
    }
    if (root->getstr() == s) {
        return "";
    }
    string left = findPath_helper(root->leftSubtree(), s);
    if (left != "-1") {
        return "0" + left;
    }
    string right = findPath_helper(root->rightSubtree(), s);
    if (right != "-1") {
        return "1" + right;
    }
    return "-1";
}

string BinaryTree::findPath(const string& s) const {
    // TODO: implement this function.
    return findPath_helper(root, s);
}

int sum_helper(Node* root) {
    // EFFECTIS: the helper function of sum
    if (root == nullptr) {
        return 0;
    }
    else {
        return root->getnum() + sum_helper(root->leftSubtree()) + sum_helper(root->rightSubtree());
    }
}

int BinaryTree::sum() const {
    // TODO: implement this function.
    return sum_helper(root);
}

int depth_helper(Node* root) {
    // EFFECTS: the helper fucntion of depth
    if (root == nullptr) {
        return 0;
    }
    int answer = depth_helper(root->leftSubtree());
    int temp = depth_helper(root->rightSubtree());
    if (answer < temp) {
        answer = temp;
    }
    return answer + 1;
}

int BinaryTree::depth() const {
    // TODO: implement this function.
    return depth_helper(root);
}

void preorder_num_helper(Node* root) {
    // EFFECTS: the helper fucntion of preorder_sum
    if (root == nullptr) {
        return;
    }
    else {
        cout << root->getnum() << " ";
        preorder_num_helper(root->leftSubtree());
        preorder_num_helper(root->rightSubtree());
    }
}

void BinaryTree::preorder_num() const {
    // TODO: implement this function.
    preorder_num_helper(root);
    cout << endl;
}

void inorder_str_helper(Node* root) {
    // EFFECTS: the helper function of inorder_str
    if (root == nullptr) {
        return;
    }
    else {
        inorder_str_helper(root->leftSubtree());
        cout << root->getstr() << " ";
        inorder_str_helper(root->rightSubtree());
    }
}

void BinaryTree::inorder_str() const {
    // TODO: implement this function.
    inorder_str_helper(root);
    cout << endl;
}

void postorder_num_helper(Node* root) {
    // EFFECTS: the helper function of postorder_num
    if (root == nullptr) {
        return;
    }
    else {
        postorder_num_helper(root->leftSubtree());
        postorder_num_helper(root->rightSubtree());
        cout << root->getnum() << " ";
    }
}

void BinaryTree::postorder_num() const {
    // TODO: implement this function.
    postorder_num_helper(root);
    cout << endl;
}

int allPathSumGreater_helper(Node* root) {
    // EFFECTS: the helper function of allPathSumGreat, return the smallest sum
    if (root == nullptr) {
        return 0;
    }
    int answer;
    if (root->leftSubtree() == nullptr && root->rightSubtree() == nullptr) {
        answer = 0;
    }
    else if (root->leftSubtree() != nullptr && root->rightSubtree() == nullptr) {
        answer = allPathSumGreater_helper(root->leftSubtree());
    }
    else if (root->leftSubtree() == nullptr && root->rightSubtree() != nullptr) {
        answer = allPathSumGreater_helper(root->rightSubtree());
    }
    else {
        answer = min(allPathSumGreater_helper(root->leftSubtree()), allPathSumGreater_helper(root->rightSubtree()));
    }
    return root->getnum() + answer;
}

bool BinaryTree::allPathSumGreater(int sum) const {
    // TODO: implement this function.
    int smallestsum = allPathSumGreater_helper(root);
    if (smallestsum > sum) {
        return true;
    }
    else {
        return false;
    }
}

bool covered_by_helper(Node* smalltree, Node* largetree) {
    // EFFECTS: the helper function of cover_by
    if (smalltree == nullptr) {
        return true;
    }
    if (smalltree != nullptr && largetree != nullptr) {
        if (smalltree->getnum() == largetree->getnum()) {
            if (covered_by_helper(smalltree->leftSubtree(), largetree->leftSubtree()) && covered_by_helper(smalltree->rightSubtree(), largetree->rightSubtree())) {
                return true;
            }
        }
    }
    return false;
}

bool BinaryTree::covered_by(const BinaryTree& tree) const {
    // TODO: implement this function.
    return covered_by_helper(root, tree.root);
}

bool contained_by_helper(Node* smalltree, Node* largetree) {
    // EFFECTS: the helper function of contained_by
    if (smalltree == nullptr) {
        return true;
    }
    if (smalltree != nullptr && largetree != nullptr) {
        return covered_by_helper(smalltree, largetree) || contained_by_helper(smalltree, largetree->leftSubtree()) || contained_by_helper(smalltree, largetree->rightSubtree());
    }
    return false;
}

bool BinaryTree::contained_by(const BinaryTree& tree) const {
    // TODO: implement this function.
    return contained_by_helper(root, tree.root);
}

Node* copy_helper(Node* root) {
    // EFFECTS: the helper function of copy
    if (root == nullptr) {
        return nullptr;
    }
    Node* np = new Node(root->getstr(), root->getnum());
    np->setleft(copy_helper(root->leftSubtree()));
    np->setright(copy_helper(root->rightSubtree()));
    return np;
}

BinaryTree BinaryTree::copy() const {
    // TODO: implement this function.
    Node* np = copy_helper(root);
    return np;
}
