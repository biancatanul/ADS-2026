#include <iostream>
#include "heap.h"
#include "iodialog.h"
using namespace std;

int parent(int i) { return (i - 1) / 2; }
int left(int i) { return 2 * i + 1; }
int right(int i) { return 2 * i + 2; }

void printHeap(Heap &h) {
    for (int i = 0; i < h.heap_size; i++)
        cout << h.A[i] << " ";
    cout << endl;
}

void heapify(Heap &h, int i) {
    int l = left(i);
    int r = right(i);
    int largest;

    if (l < h.heap_size && h.A[l] > h.A[i])
        largest = l;
    else
        largest = i;

    if (r < h.heap_size && h.A[r] > h.A[largest])
        largest = r;

    if (largest != i) {
        swap(h.A[i], h.A[largest]);
        heapify(h, largest);
    }
}

void buildHeap(Heap &h) {
    h.heap_size = h.length;
    for (int i = (h.length - 1) / 2; i >= 0; i--)
        heapify(h, i);
}

void heapSort(Heap &h) {
    for (int i = h.length - 1; i >= 1; i--) {
        swap(h.A[0], h.A[i]); // move current max to its final position
        h.heap_size--; // shrink the heap
        heapify(h, 0); // fix the new root
    }
}

int maximum(Heap &h) {
    if (h.heap_size < 1) {
        cout << "Heap is empty." << endl;
        return -1;
    }
    return h.A[0]; //maximum is always the root
}

int minimum(Heap &h) {
    if (h.heap_size < 1) {
        cout << "Heap is empty." << endl;
        return -1;
    }

    int min = h.A[h.heap_size / 2]; // leaves start at heap size/2
    for (int i = h.heap_size / 2 + 1; i < h.heap_size; i++)
        if (h.A[i] < min)
            min = h.A[i];
    return min;
}

int extractMax(Heap &h) {
    if (h.heap_size < 1) {
        cout << "Heap underflow." << endl;
        return -1;
    }

    int max = h.A[0]; // save the max
    h.A[0] = h.A[h.heap_size - 1]; // move last element to root
    h.heap_size--; // shrink heap
    h.length--;
    heapify(h, 0); // fix the root

    return max;
}

void insert(Heap &h, int key) {
    // resize array to fit one more element
    int *newA = new int[h.length + 1];
    for (int i = 0; i < h.length; i++)
        newA[i] = h.A[i];
    delete[] h.A;
    h.A = newA;
    h.length++;

    // place new key at the end
    h.heap_size++;
    int i = h.heap_size - 1;

    // bubble up
    while (i > 0 && h.A[parent(i)] < key) {
        h.A[i] = h.A[parent(i)]; // shift parent down
        i = parent(i);
    }
    h.A[i] = key; // place key in its correct spot
}

int main() {
    Heap h;
    h.A = nullptr;
    h.length = 0;
    h.heap_size = 0;

    int option;
    do {
        option = IODialog::getHeapOperation();
        switch (option) {
            case 1: {
                delete[] h.A;

                list<int> keys;
                IODialog::getKeys(keys);

                h.length = keys.size();
                h.heap_size = h.length;
                h.A = new int[h.length];

                int idx = 0;
                for (int k: keys)
                    h.A[idx++] = k;

                buildHeap(h);
                cout << "Heap built: ";
                printHeap(h);
                break;
            }
            case 2: {
                if (h.A == nullptr) {
                    cout << "Build a heap first." << endl;
                    break;
                }
                int i = IODialog::getIndex();
                if (i < 0 || i >= h.heap_size) {
                    cout << "Invalid index." << endl;
                    break;
                }
                heapify(h, i);
                cout << "After heapify at " << i << ": ";
                printHeap(h);
                break;
            }
            case 3: {
                if (h.A == nullptr) {
                    cout << "Build a heap first." << endl;
                    break;
                }
                int key = IODialog::getKey();
                insert(h, key);
                cout << "After insert: ";
                printHeap(h);
                break;
            }
            case 4: {
                if (h.A == nullptr) {
                    cout << "Build a heap first." << endl;
                    break;
                }
                cout << "Extracted max: " << extractMax(h) << endl;
                cout << "Heap now: ";
                printHeap(h);
                break;
            }
            case 5: {
                if (h.A == nullptr) {
                    cout << "Build a heap first." << endl;
                    break;
                }
                cout << "Maximum: " << maximum(h) << endl;
                break;
            }
            case 6: {
                if (h.A == nullptr) {
                    cout << "Build a heap first." << endl;
                    break;
                }
                cout << "Minimum: " << minimum(h) << endl;
                break;
            }
            case 7: {
                if (h.A == nullptr) {
                    cout << "Build a heap first." << endl;
                    break;
                }
                int originalSize = h.heap_size;
                buildHeap(h); // ensure valid heap
                heapSort(h);
                cout << "Sorted: ";
                for (int i = 0; i < originalSize; i++)
                    cout << h.A[i] << " ";
                cout << endl;
                break;
            }
            case 8: {
                if (h.A == nullptr) {
                    cout << "Nothing to print." << endl;
                    break;
                }
                printHeap(h);
                break;
            }
            case 9:
                cout << "Bye!" << endl;
                break;
        }
    } while (option != 9);

    delete[] h.A;
    return 0;
}
