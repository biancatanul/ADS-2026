/*
Problem 2: Dynamic Median of a Data Stream
Description
You are receiving a stream of integers and must continuously report the median of the numbers seen so far.
The data structure must support:
ADD x → insert number x
REMOVE x → remove one occurrence of x
MEDIAN → output the current median
If the number of elements is even, return the lower median.
Example:
Input:
ADD 5
ADD 2
ADD 10
MEDIAN
ADD 7
MEDIAN
REMOVE 5
MEDIAN
Output:
5
5
7
*/

#include <iostream>
#include <string>
#include "RBNode.h"

using namespace std;
int count = 0;
RBTree tree;

int findMedian(RBNode *node, int target, int &current) {
    if (tree.isNil(node)) return -1;

    if (!tree.isNil(node)) {
        int left = findMedian(node->left, target, current);
        if (left != -1) return left;
        if (current == target) {
            return node->key;
        }
        current++;
        return findMedian(node->right, target, current);
    }
}

int main() {
    string command;
    while (cin >> command) {
        if (command == "ADD") {
            int x;
            cin >> x;
            tree.RBInsert(tree.createNode(x));
            count++;
        } else if (command == "REMOVE") {
            int x;
            cin >> x;
            RBNode *node = tree.search(tree.root, x);
            if (!tree.isNil(node)) {
                tree.del(node);
                count--;
            }
        } else if (command == "MEDIAN") {
            int target = (count - 1) / 2;
            int current = 0;
            cout << findMedian(tree.root, target, current) << endl;
        }
    }

    return 0;
}
