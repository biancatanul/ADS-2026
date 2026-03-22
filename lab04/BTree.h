/*B-tree implementation*/

#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <vector>
using namespace std;

struct BTreeNode {
    int keysNr;
    std::vector<BTreeNode *> children;
    std::vector<int> keys;
    bool isLeaf;

    BTreeNode(int t, bool isLeaf) : keysNr(0), isLeaf(isLeaf) {
        keys.reserve(2 * t - 1);
        children.reserve(2 * t);
    };
};

struct BTree {
    int t;
    BTreeNode *root;

    BTree(int t) : t(t) {
        root = nullptr;
    }

    BTreeNode *search(BTreeNode *x, int key) {
        int i = 0;
        while (i < x->keysNr && key > x->keys[i]) {
            i = i + 1;
        }
        if (i < x->keysNr && key == x->keys[i]) {
            return x;
        } else if (x->isLeaf) return nullptr;
        else {
            return BTree::search(x->children.at(i), key);
        }
    }

    BTreeNode *search(int key) {
        return search(root, key);
    }

    void splitChild(BTreeNode *x, int i, BTreeNode *y) {
        BTreeNode *z = new BTreeNode(t, y->isLeaf);
        z->keysNr = t - 1;
        for (int j = 0; j < t - 1; j++) {
            z->keys.push_back(y->keys[j + t]);
        }
        if (!(y->isLeaf)) {
            for (int j = 0; j < t; j++) {
                z->children.push_back(y->children.at(j + t));
            }
        }
        y->keysNr = t - 1;

        x->keys.insert(x->keys.begin() + i, y->keys[t - 1]);
        x->children.insert(x->children.begin() + i + 1, z);
        x->keysNr += 1;
    }

    void insertNonFull(BTreeNode *x, int key) {
        int i = x->keysNr - 1;
        if (x->isLeaf) {
            x->keys.insert(x->keys.begin() + i + 1, key);
            x->keysNr += 1;
        } else {
            while (i >= 0 && key < x->keys[i]) {
                i -= 1;
            }
            i += 1;
            if (x->children.at(i)->keysNr == (2 * t - 1)) {
                splitChild(x, i, x->children.at(i));
                if (key > x->keys[i]) {
                    i += 1;
                }
            }
            insertNonFull(x->children.at(i), key);
        }
    }

    void insert(int key) {
        if (root == nullptr) {
            root = new BTreeNode(t, true);
            root->keys.push_back(key);
            root->keysNr = 1;
            return;
        }
        BTreeNode *r = root;
        if (r->keysNr == (2 * t) - 1) {
            BTreeNode *s = new BTreeNode(t, false);
            root = s;
            s->children.push_back(r);
            splitChild(s, 0, r);
            insertNonFull(s, key);
        } else insertNonFull(r, key);
    }

    int getPredecessor(BTreeNode *x) {
        while (!x->isLeaf)
            x = x->children.back();
        return x->keys.back();
    }

    int getSuccessor(BTreeNode *x) {
        while (!x->isLeaf)
            x = x->children.front();
        return x->keys.front();
    }

    void merge(BTreeNode *x, int i) {
        BTreeNode *y = x->children[i];
        BTreeNode *z = x->children[i + 1];
        y->keys.push_back(x->keys[i]);
        y->keysNr++;
        for (int j = 0; j < z->keysNr; j++) {
            y->keys.push_back(z->keys[j]);
            y->keysNr++;
        }
        for (int j = 0; j < z->children.size(); j++)
            y->children.push_back(z->children[j]);
        x->keys.erase(x->keys.begin() + i);
        x->keysNr--;
        x->children.erase(x->children.begin() + i + 1);
        delete z;
    }

    void deleteKey(BTreeNode *x, int key) {
        int i = 0;
        while (i < x->keysNr && key > x->keys[i])
            i++;

        if (i < x->keysNr && key == x->keys[i]) {
            if (x->isLeaf) {
                x->keys.erase(x->keys.begin() + i);
                x->keysNr--;
            } else {
                BTreeNode *y = x->children[i];
                BTreeNode *z = x->children[i + 1];
                if (y->keysNr >= t) {
                    int pred = getPredecessor(y);
                    x->keys[i] = pred;
                    deleteKey(y, pred);
                } else if (z->keysNr >= t) {
                    int succ = getSuccessor(z);
                    x->keys[i] = succ;
                    deleteKey(z, succ);
                } else {
                    merge(x, i);
                    deleteKey(y, key);
                }
            }
        } else {
            if (x->isLeaf) return;
            BTreeNode *c = x->children[i];
            if (c->keysNr == t - 1) {
                if (i > 0 && x->children[i - 1]->keysNr >= t) {
                    BTreeNode *leftSibling = x->children[i - 1];
                    c->keys.insert(c->keys.begin(), x->keys[i - 1]);
                    c->keysNr++;
                    x->keys[i - 1] = leftSibling->keys.back();
                    leftSibling->keys.pop_back();
                    leftSibling->keysNr--;
                    if (!leftSibling->isLeaf) {
                        c->children.insert(c->children.begin(), leftSibling->children.back());
                        leftSibling->children.pop_back();
                    }
                } else if (i < x->keysNr && x->children[i + 1]->keysNr >= t) {
                    BTreeNode *rightSibling = x->children[i + 1];
                    c->keys.push_back(x->keys[i]);
                    c->keysNr++;
                    x->keys[i] = rightSibling->keys.front();
                    rightSibling->keys.erase(rightSibling->keys.begin());
                    rightSibling->keysNr--;
                    if (!rightSibling->isLeaf) {
                        c->children.push_back(rightSibling->children.front());
                        rightSibling->children.erase(rightSibling->children.begin());
                    }
                } else {
                    if (i < x->keysNr)
                        merge(x, i);
                    else
                        merge(x, i - 1);
                    if (i < x->keysNr + 1)
                        c = x->children[i];
                    else
                        c = x->children[i - 1];
                }
            }
            deleteKey(c, key);
        }
    }

    int getMinimum() {
        return getSuccessor(root);
    }

    int getMaximum() {
        return getPredecessor(root);
    }

    void printNode(BTreeNode *x, int depth) {
        if (x == nullptr) return;

        for (int i = 0; i < depth; i++)
            cout << "    ";

        cout << "[";
        for (int i = 0; i < x->keysNr; i++) {
            cout << x->keys[i];
            if (i < x->keysNr - 1) cout << ", ";
        }
        cout << "]" << endl;

        for (int i = 0; i < x->children.size(); i++)
            printNode(x->children[i], depth + 1);
    }

    void indentedDisplay() {
        if (root == nullptr) {
            cout << "BT: Tree is empty." << endl;
            return;
        }
        printNode(root, 0);
    }
};


#endif //BTREE_H
