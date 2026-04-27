#include <iostream>
#include "binomial_heap.h"
#include "IODialog.h"
using namespace std;

Node* makeNode(int key) {
    Node* x = new Node();
    x->key = key;
    x->degree = 0;
    x->parent = nullptr;
    x->child = nullptr;
    x->sibling = nullptr;
    return x;
}

// Makes y a child of z. Caller ensures y->key >= z->key (min-heap property)
void link(Node* y, Node* z) {
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree++;
}

// Merges two root lists in non-decreasing order of degree
Node* mergeRootLists(BinomialHeap& h1, BinomialHeap& h2) {
    if (!h1.head) return h2.head;
    if (!h2.head) return h1.head;

    Node* head = nullptr;
    Node* tail = nullptr;
    Node* a = h1.head;
    Node* b = h2.head;

    if (a->degree <= b->degree) { head = a; a = a->sibling; }
    else                        { head = b; b = b->sibling; }
    tail = head;

    while (a && b) {
        if (a->degree <= b->degree) { tail->sibling = a; a = a->sibling; }
        else                        { tail->sibling = b; b = b->sibling; }
        tail = tail->sibling;
    }
    tail->sibling = a ? a : b;
    return head;
}

// Full union: merge root lists then consolidate trees of equal degree
BinomialHeap unionHeaps(BinomialHeap& h1, BinomialHeap& h2) {
    BinomialHeap h;
    h.head = mergeRootLists(h1, h2);
    if (!h.head) return h;

    Node* prev = nullptr;
    Node* x    = h.head;
    Node* next = x->sibling;

    while (next) {
        // Case 1: degrees differ -> advance
        // Case 2: three consecutive equal degrees -> advance, handle trailing pair next iteration
        if (x->degree != next->degree ||
            (next->sibling && next->sibling->degree == x->degree)) {
            prev = x;
            x = next;
        }
        // Case 3: x.key <= next.key -> link next under x
        else if (x->key <= next->key) {
            x->sibling = next->sibling;
            link(next, x);
        }
        // Case 4: next.key < x.key -> link x under next
        else {
            if (!prev) h.head = next;
            else       prev->sibling = next;
            link(x, next);
            x = next;
        }
        next = x->sibling;
    }
    return h;
}

void insert(BinomialHeap& h, int key) {
    BinomialHeap h2;
    h2.head = makeNode(key);
    h = unionHeaps(h, h2);
}

int findMin(BinomialHeap& h) {
    if (!h.head) {
        cout << "Heap is empty." << endl;
        return -1;
    }
    Node* x = h.head;
    int min = x->key;
    while (x) {
        if (x->key < min) min = x->key;
        x = x->sibling;
    }
    return min;
}

int extractMin(BinomialHeap& h) {
    if (!h.head) {
        cout << "Heap is empty." << endl;
        return -1;
    }

    // Find the root with minimum key and its predecessor
    Node* minPrev = nullptr;
    Node* minNode = h.head;
    Node* prev    = nullptr;
    Node* x       = h.head;

    while (x) {
        if (x->key < minNode->key) {
            minNode = x;
            minPrev = prev;
        }
        prev = x;
        x = x->sibling;
    }

    // Remove minNode from root list
    if (minPrev) minPrev->sibling = minNode->sibling;
    else         h.head = minNode->sibling;

    // Children are in decreasing degree order; reverse to get increasing order for union
    Node* child = minNode->child;
    Node* reversedHead = nullptr;
    while (child) {
        Node* next = child->sibling;
        child->parent = nullptr;
        child->sibling = reversedHead;
        reversedHead = child;
        child = next;
    }

    BinomialHeap childHeap;
    childHeap.head = reversedHead;

    int minKey = minNode->key;
    delete minNode;

    h = unionHeaps(h, childHeap);
    return minKey;
}

// Reduces x's key to newKey and bubbles it up by swapping keys with parent
// (same idea as binary heap bubble-up, but here the tree is pointer-based)
void decreaseKey(BinomialHeap& h, Node* x, int newKey) {
    if (newKey > x->key) {
        cout << "New key is greater than current key." << endl;
        return;
    }
    x->key = newKey;
    Node* y = x;
    Node* z = y->parent;
    while (z && y->key < z->key) {
        swap(y->key, z->key);
        y = z;
        z = y->parent;
    }
}

// Set key to INT_MIN (bubbles to root), then extractMin removes it
void deleteNode(BinomialHeap& h, Node* x) {
    decreaseKey(h, x, INT_MIN);
    extractMin(h);
}

// Search within a single binomial tree (node + all descendants)
Node* findInSubtree(Node* x, int key) {
    if (!x) return nullptr;
    if (x->key == key) return x;
    Node* child = x->child;
    while (child) {
        Node* found = findInSubtree(child, key);
        if (found) return found;
        child = child->sibling;
    }
    return nullptr;
}

// Search across all trees in the heap, return first node with matching key
Node* findNode(BinomialHeap& h, int key) {
    Node* x = h.head;
    while (x) {
        Node* found = findInSubtree(x, key);
        if (found) return found;
        x = x->sibling;
    }
    return nullptr;
}

void printTree(Node* node, int depth) {
    while (node) {
        for (int i = 0; i < depth; i++) cout << "  ";
        cout << node->key << " (deg " << node->degree << ")" << endl;
        printTree(node->child, depth + 1);
        node = node->sibling;
    }
}

void printHeap(BinomialHeap& h) {
    if (!h.head) {
        cout << "Heap is empty." << endl;
        return;
    }
    Node* x = h.head;
    while (x) {
        cout << "B" << x->degree << " root: " << x->key << endl;
        printTree(x->child, 1);
        x = x->sibling;
    }
}

int main() {
    BinomialHeap h;
    h.head = nullptr;

    int option;
    do {
        option = IODialog::getBinomialHeapOperation();
        switch (option) {
            case 1: {
                int key = IODialog::getKey();
                insert(h, key);
                cout << "Inserted " << key << ". Heap now:" << endl;
                printHeap(h);
                break;
            }
            case 2: {
                cout << "Minimum: " << findMin(h) << endl;
                break;
            }
            case 3: {
                cout << "Extracted min: " << extractMin(h) << endl;
                cout << "Heap now:" << endl;
                printHeap(h);
                break;
            }
            case 4: {
                cout << "Current key to find: ";
                int cur = IODialog::getKey();
                Node* node = findNode(h, cur);
                if (!node) { cout << "Key " << cur << " not found." << endl; break; }
                cout << "New (smaller) key: ";
                int newKey = IODialog::getKey();
                decreaseKey(h, node, newKey);
                cout << "Heap now:" << endl;
                printHeap(h);
                break;
            }
            case 5: {
                cout << "Key of node to delete: ";
                int key = IODialog::getKey();
                Node* node = findNode(h, key);
                if (!node) { cout << "Key " << key << " not found." << endl; break; }
                deleteNode(h, node);
                cout << "Deleted " << key << ". Heap now:" << endl;
                printHeap(h);
                break;
            }
            case 6: {
                BinomialHeap h2;
                h2.head = nullptr;
                list<int> keys;
                IODialog::getKeys(keys);
                for (int k : keys)
                    insert(h2, k);
                h = unionHeaps(h, h2);
                cout << "After union. Heap now:" << endl;
                printHeap(h);
                break;
            }
            case 7: {
                printHeap(h);
                break;
            }
            case 8:
                cout << "Bye!" << endl;
                break;
        }
    } while (option != 8);

    return 0;
}