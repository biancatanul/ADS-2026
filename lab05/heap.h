#ifndef ADS_2026_HEAP_H
#define ADS_2026_HEAP_H

struct Heap {
    int *A;
    int length;
    int heap_size;
};

// index helpers
int parent(int i);

int left(int i);

int right(int i);

// core operations
void heapify(Heap &h, int i);

void buildHeap(Heap &h);

void heapSort(Heap &h);

// priority queue operations
int maximum(Heap &h);

int extractMax(Heap &h);

void insert(Heap &h, int key);

// utility
void printHeap(Heap &h);

#endif //ADS_2026_HEAP_H
