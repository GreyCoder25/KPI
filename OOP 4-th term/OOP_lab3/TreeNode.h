#ifndef TREENODE_H
#define TREENODE_H

#include <string>
#include <iostream>

using std::cout;
using std::endl;

using std::string;

struct Time{
    int hours;
    int minutes;

    Time(int h, int m) {
        hours = (h >= 0 && h <= 23) ? h : 0;
        minutes = (m >= 0 && m <= 59) ? m : 0;
    }
    Time() {
        hours = 0;
        minutes = 0;
    }
    void print() {
        if (hours < 10)
            cout << "0";
        cout << hours << ":";
        if (minutes < 10)
            cout << "0";
        cout << minutes;

    }
};

class TreeNode {
    friend class BinTree;
public:
    TreeNode();
    TreeNode(int, const string&, const Time&);
    TreeNode(const TreeNode&);
    void printData();

private:
    int trainNumber;
    string destination;
    Time arrivalTime;

    TreeNode* leftChild;
    TreeNode* rightChild;
};

#endif // TREENODE_H
