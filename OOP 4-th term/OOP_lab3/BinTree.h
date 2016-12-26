#ifndef BINTREE_H
#define BINTREE_H

#include "TreeNode.h"
#include <iostream>

class BinTree {
    //friend class TreeNode;
public:
    BinTree();
    void print();
    void add(const TreeNode&);
    TreeNode* find(int key);
    void findAllAndPrint(const string& key);
    bool remove(int key);

private:
    TreeNode* root;

    TreeNode* findMin(TreeNode*);
    void inOrder(TreeNode* );
    void inOrderPrintKey(TreeNode*, const string& key);
};



#endif // BINTREE_H
