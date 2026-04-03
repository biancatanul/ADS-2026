#ifndef ADS_2026_IODIALOG_H
#define ADS_2026_IODIALOG_H

#include <iostream>
#include <sstream>
#include <list>
using namespace std;

namespace IODialog {
    void showHeapOperation() {
        cout << "\n1. Build heap from input" << endl
                << "2. Heapify at index" << endl
                << "3. Insert key" << endl
                << "4. Extract max" << endl
                << "5. Show maximum" << endl
                << "6. Show minimum" << endl
                << "7. Heap sort" << endl
                << "8. Print heap" << endl
                << "9. Exit" << endl
                << "Enter your choice (1-9): ";
    }

    int getHeapOperation() {
        int option = 0;
        while (true) {
            showHeapOperation();
            if (!(cin >> option)) {
                cout << "Unknown option. Try again." << endl;
                cin.clear();
                cin.ignore(10000, '\n');
            } else if (option < 1 || option > 9) {
                cout << "Unknown option. Try again." << endl;
            } else {
                cout << "Proceed with selection " << option << " .." << endl;
                cin.ignore(10000, '\n');
                break;
            }
        }
        return option;
    }

    void getKeys(list<int> &keys) {
        cout << "Type in the keys (space separated): " << flush;
        int key;
        string line;
        if (getline(cin, line)) {
            istringstream iss(line);
            while (iss >> key)
                keys.push_back(key);
        }
    }

    int getKey() {
        cout << "Type in the key: ";
        int k;
        cin >> k;
        cin.ignore(10000, '\n');
        return k;
    }

    int getIndex() {
        cout << "Type in the index: ";
        int i;
        cin >> i;
        cin.ignore(10000, '\n');
        return i;
    }
}

#endif //ADS_2026_IODIALOG_H
