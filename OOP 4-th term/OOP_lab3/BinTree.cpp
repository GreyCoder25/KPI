#include "BinTree.h"

BinTree::BinTree() {
    root = 0;
}

void BinTree::add(const TreeNode &node) {

    TreeNode* addNode = new TreeNode(node);
    if (root == 0)
        root = addNode;
    else {
        TreeNode* current = root;
        TreeNode* parent;

        while (current != 0) {
            parent = current;
            if (node.trainNumber <= current->trainNumber) {
                current = current->leftChild;
                if (current == 0)
                    parent->leftChild = addNode;

            }
            else {
                current = current->rightChild;
                if (current == 0)
                    parent->rightChild = addNode;
            }
        }
    }

}

TreeNode* BinTree::find(int key) {

    TreeNode* p = root;
    if (p == 0)
        return 0;

    while (p != 0) {
        if (key == p->trainNumber)
            return p;
        else if (key < p->trainNumber)
            p = p->leftChild;
        else
            p = p->rightChild;
    }
    return 0;

}

void BinTree::inOrderPrintKey(TreeNode *tree, const string &key) {

    if (tree != 0) {
        inOrderPrintKey(tree->leftChild, key);
        if (tree->destination == key)
            tree->printData();
        inOrderPrintKey(tree->rightChild, key);
    }

}

void BinTree::findAllAndPrint(const string &key) {

    inOrderPrintKey(root, key);

}

TreeNode* BinTree::findMin(TreeNode* treePtr) {

    TreeNode* p = treePtr;
    while (p->leftChild != 0)
        p = p->leftChild;

    return p;
}

bool BinTree::remove(int key) {

    if(root == 0)
        return false;

    TreeNode* current = root;
    TreeNode* parent = root;
    while (key != current->trainNumber) {
        parent = current;
        if (key <= current->trainNumber)
            current = current->leftChild;
        else
            current = current->rightChild;

        if (current == 0)
            return false;
    }

    //no child
    if(current->leftChild == 0 && current->rightChild == 0) {
        if (current == root) {
            delete root;
            root = 0;
        }
        else if (parent->leftChild == current) {
            delete parent->leftChild;
            parent->leftChild = 0;
        }
        else {
            delete parent->rightChild;
            parent->rightChild = 0;
        }
    }
    //one child
    else if(current->leftChild == 0) {
        TreeNode* temp = current;
        if (current == parent->rightChild)
            parent->rightChild = current->rightChild;
        else
            parent->leftChild = current->rightChild;
        delete temp;
    }
    else if(current->rightChild == 0) {
        TreeNode* temp = current;
        if (current == parent->rightChild)
            parent->rightChild = current->leftChild;
        else
            parent->leftChild = current->leftChild;
        delete temp;
    }
    //two children
    else {
        TreeNode* temp = findMin(current->rightChild);
        int tempNum = temp->trainNumber;
        remove(temp->trainNumber);
        current->trainNumber = tempNum;
    }


    return true;

}

void BinTree::print() {

    inOrder(root);

}

void BinTree::inOrder(TreeNode *tree) {

    if (tree != 0) {
        inOrder(tree->leftChild);
        tree->printData();
        inOrder(tree->rightChild);
    }

}
