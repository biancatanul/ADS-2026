#ifndef IODIALOG_H
#define IODIALOG_H

#include <iostream>
#include <sstream>
#include <list>
using namespace std;

namespace IODialog {
    void showBinomialHeapOperation() {
        cout << "\n1. Insert key" << endl
             << "2. Find minimum" << endl
             << "3. Extract minimum" << endl
             << "4. Decrease key" << endl
             << "5. Delete node" << endl
             << "6. Union with new heap" << endl
             << "7. Print heap" << endl
             << "8. Exit" << endl
             << "Enter your choice (1-8): ";
    }

    int getBinomialHeapOperation() {
        int option = 0;
        while (true) {
            showBinomialHeapOperation();
            if (!(cin >> option)) {
                cout << "Unknown option. Try again." << endl;
                cin.clear();
                cin.ignore(10000, '\n');
            } else if (option < 1 || option > 8) {
                cout << "Unknown option. Try again." << endl;
            } else {
                cout << "Proceed with selection " << option << " .." << endl;
                cin.ignore(10000, '\n');
                break;
            }
        }
        return option;
    }

    int getKey() {
        cout << "Type in the key: ";
        int k;
        cin >> k;
        cin.ignore(10000, '\n');
        return k;
    }

    void getKeys(list<int>& keys) {
        cout << "Type in the keys (space separated): " << flush;
        string line;
        if (getline(cin, line)) {
            istringstream iss(line);
            int key;
            while (iss >> key)
                keys.push_back(key);
        }
    }
}

#endif