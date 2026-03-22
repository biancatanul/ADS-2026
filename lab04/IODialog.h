#ifndef IODIALOG_H_
#define IODIALOG_H_

#include <iostream>
#include <sstream>
#include <list>
using namespace std;

namespace IODialog {

    void showTreeOperation() {
        cout << "1. Insert nodes" << endl
             << "2. Delete node" << endl
             << "3. Search for a value" << endl
             << "4. Show tree" << endl
             << "5. Show minimum value" << endl
             << "6. Show maximum value" << endl
             << "7. Exit" << endl
             << "Enter your choice (1-7): ";
    }

    int getTreeOperation() {
        int option = 0;
        while (true) {
            showTreeOperation();
            if (!(cin >> option)) {
                cout << "Unknown option. Try again." << endl;
                cin.clear();
                cin.ignore(10000, '\n');
            } else if (option < 1 || option > 7) {
                cout << "Unknown option. Try again." << endl;
            } else {
                cout << "Proceed with selection " << option << " .." << endl;
                cin.ignore(10000, '\n');
                break;
            }
        }
        return option;
    }

    void getNodeKeys(list<int>& nodeKeys) {
        cout << "Type in the keys to insert: " << flush;
        int key;
        string line;
        if (getline(cin, line)) {
            istringstream iss(line);
            while (iss >> key)
                nodeKeys.push_back(key);
        }
    }

    int getNodeKey() {
        cout << "Type in the key: ";
        int k;
        cin >> k;
        return k;
    }
}

#endif