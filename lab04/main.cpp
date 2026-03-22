#include <cstdlib>
#include "BTree.h"
#include "IODialog.h"

void startProcessing(BTree *);

int main() {
    BTree *bt = new BTree(3);
    startProcessing(bt);
    delete bt;
}

void perform(BTree *, int);

void startProcessing(BTree *bt) {
    int o;
    while (true) {
        o = IODialog::getTreeOperation();
        perform(bt, o);
    }
}

void perform(BTree *bt, int o) {
    list<int> nodeKeys;
    BTreeNode *btn;
    int skey;
    switch (o) {
        case 1: // Insert nodes
            IODialog::getNodeKeys(nodeKeys);
            for (list<int>::iterator it = nodeKeys.begin();
                 it != nodeKeys.end(); it++)
                bt->insert(*it);
            break;
        case 2: // Delete node
            skey = IODialog::getNodeKey();
            bt->deleteKey(bt->root, skey);
            cout << "BT: Node " << skey << " deleted." << endl;
            break;
        case 3: // Search for a value
            skey = IODialog::getNodeKey();
            btn = bt->search(bt->root, skey);
            if (btn != nullptr)
                cout << "BT: Key " << skey << " found!" << endl;
            else
                cout << "BT: Key " << skey << " not found." << endl;
            break;
        case 4: // Show tree
            bt->indentedDisplay();
            break;
        case 5: // Get minimum value
            cout << "Minimum value is: " << bt->getMinimum() << endl;
            break;
        case 6: // Get maximum value
            cout << "Maximum value is: " << bt->getMaximum() << endl;
            break;
        case 7: // Get predecessor of a node
            skey = IODialog::getNodeKey();
            btn = bt->search(bt->root, skey);
            if (btn != nullptr)
                cout << "BT: Predecessor is: " << bt->getPredecessor(btn) << endl;
            else
                cout << "BT: Node not found." << endl;
            break;
        case 8: // Get successor of a node
            skey = IODialog::getNodeKey();
            btn = bt->search(bt->root, skey);
            if (btn != nullptr)
                cout << "BT: Successor is: " << bt->getSuccessor(btn) << endl;
            else
                cout << "BT: Node not found." << endl;
            break;
        case 9: //Exit
            delete bt;
            cout << "Bye!" << endl;
            exit(0);
    }
}
