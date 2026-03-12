#include <iostream>
#include <stdlib.h>

struct Node {
    int key;
    Node* left;
    Node* right;
    Node* parent;
    Node(int value): key(value), left(nullptr), right(nullptr), parent(nullptr) {}
};

class BSTree {
    private:
        Node* root;
        Node* del(Node* node);
        Node* successor(Node* node);
        void insert(Node* node);

    public:
        BSTree(): root(nullptr) {}
        void insert(int value);
        Node* search(int value);
        void del(int value);
        Node* min_value();
        Node* max_value();
};

Node* BSTree::successor(Node* z) {
    if (z->right != nullptr) {
        Node* temp = z->right;
        while (temp->left != nullptr) temp = temp->left;
        return temp;
    }
    Node* y = z->parent;
    while(y != nullptr && z == y->right) {
        z = y;
        y = y->parent;
    }
    return y;
}

void BSTree::insert (Node* z) {
    if (z == nullptr) return;

    Node* y = nullptr;
    Node* x = root;

    while (x != nullptr) {
        y = x;
        if (z->key < x->key) x = x->left;
        else x = x->right;
    }
    z->parent = y;
    if(y == nullptr) root = z;
    else if (z->key < y->key) y->left = z;
    else y->right = z;
}

void BSTree::insert(int value) {
    Node* z = new Node(value);
    insert(z);
}

Node* BSTree::search(int k) {
    Node* temp = root;
    while (temp != nullptr) {
        if (k == temp->key) {
            return temp;
        } else if (k<temp->key) {
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }
    return nullptr;
}

Node* BSTree::del(Node* z) {
    Node* y;
    Node* x;

    if (z->left == nullptr || z->right == nullptr) y = z;
    else y = successor(z);

    if(y->left != nullptr) x = y->left;
    else x = y->right;

    if(x!= nullptr) x->parent = y->parent;

    if(y->parent == nullptr) root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;

    if (y!=z) z->key = y->key;

    return y;
}

void BSTree::del(int value) {
    Node* z = search(value);
    if (z != nullptr) del(z);
}

Node* BSTree::min_value() {
    if (root == nullptr) return nullptr;
    Node* temp = root;
    while (temp->left != nullptr) temp = temp->left;
    return temp;
}

Node* BSTree::max_value() {
    if (root == nullptr) return nullptr;
    Node* temp = root;
    while (temp->right != nullptr) temp = temp->right;
    return temp;
}

int main() {
    BSTree bst;

    for (int i = 1; i <= 5; i++) {
        int val;
        std::cout << "Enter value for element " << i << ": ";
        std::cin >> val;
        bst.insert(val);
    }

    std::cout << "Min value = " << bst.min_value()->key << std::endl;
    std::cout << "Max value = " << bst.max_value()->key << std::endl;

    int x = 0;
    std::cout << "Enter value to search for and delete: ";
    std::cin >> x;

    Node* found = bst.search(x);

    if (found != nullptr) {
        std::cout << "Found x = " << found->key << ", deleting" << std::endl;
        bst.del(found->key);
    }

    std::cout << "Min value = " << bst.min_value()->key << std::endl;
    std::cout << "Max value = " << bst.max_value()->key << std::endl;

    return 0;
}