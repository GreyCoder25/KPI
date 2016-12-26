#include "TreeNode.h"

TreeNode::TreeNode() {

    trainNumber = 0;
    destination = "";
    leftChild = 0;
    rightChild = 0;

}

TreeNode::TreeNode(int trNum, const string &dest, const Time &arrT) {

    trainNumber = trNum;
    destination = dest;
    arrivalTime = arrT;
    leftChild = 0;
    rightChild = 0;

}

TreeNode::TreeNode(const TreeNode& tn) {

    trainNumber = tn.trainNumber;
    destination = tn.destination;
    arrivalTime = tn.arrivalTime;
    leftChild = 0;
    rightChild = 0;
}



void TreeNode::printData() {
    cout << "Train number: " << trainNumber << endl
         << "Destination: " << destination << endl
         << "Arrival time: ";
    arrivalTime.print();
    cout << endl << endl;
}
