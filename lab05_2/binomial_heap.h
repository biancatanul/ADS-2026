#ifndef BINOMIAL_HEAP_H
#define BINOMIAL_HEAP_H

#include <climits>

struct Node {
    int key;
    int degree;
    Node* parent;
    Node* child;
    Node* sibling;
};

struct BinomialHeap {
    Node* head;
};

Node* makeNode(int key);
void link(Node* y, Node* z);
Node* mergeRootLists(BinomialHeap& h1, BinomialHeap& h2);
BinomialHeap unionHeaps(BinomialHeap& h1, BinomialHeap& h2);
void insert(BinomialHeap& h, int key);
int findMin(BinomialHeap& h);
int extractMin(BinomialHeap& h);
void decreaseKey(BinomialHeap& h, Node* x, int newKey);
void deleteNode(BinomialHeap& h, Node* x);
Node* findInSubtree(Node* x, int key);
Node* findNode(BinomialHeap& h, int key);
void printTree(Node* node, int depth);
void printHeap(BinomialHeap& h);

#endif