#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 6

typedef struct {
    int arr[MAX];
    int heapSize;
    int length;
} Heap, *HeapPtr;

int parent(int);
int left(int);
int right(int);
void maxHeapify(HeapPtr, int);
int buildMaxHeap(HeapPtr);
void initHeap(HeapPtr);
void printArr(HeapPtr);
void heapSort(HeapPtr);

int main() {
    Heap H;
    int index = 0;
    initHeap(&H);
    printArr(&H);
    printf("\n");
    // buildMaxHeap(&H);
    // maxHeapify(&H, index);
    heapSort(&H);
    printArr(&H);
    return 0;
}

void initHeap(HeapPtr HP) {
    int ctr = 0;
    while (ctr < MAX) {
        HP->arr[ctr] = (rand() % (MAX - 0 + 1));
        ctr++;
    }

    HP->heapSize = ctr;
    HP->length = ctr;
}

int parent(int index) {
    return floor(index / 2);
}

int left(int index) {
    return 2*(index+1)-1;
}

int right(int index) {
    return 2*(index+1);
}

void maxHeapify(HeapPtr HP, int index) {
    // Maintains heap property

    // Get indices for left and right child of current index
    int l = left(index);
    int r = right(index);

    // Index to store the largest value among the node and its children
    int largest;

    // Check if curent node is greater than its left child
    // Use l <= HP->heapSize so that no element that's part of the heap is checked
    // which also prevents using indices that are greater than the array's length
    if (l <= HP->heapSize && HP->arr[l] > HP->arr[index]) largest = l;
    else largest = index;

    // Check if right child is greater than the greatest value between
    // the current node and its left child
    if (r <= HP->heapSize && HP->arr[r] > HP->arr[index]) largest = r;

    // If current node doesn't have the largest value, swap it out w/ the node
    // that has the largest value and repeat procedure on that node
    if (largest != index) {
        int temp = HP->arr[largest];
        HP->arr[largest] = HP->arr[index];
        HP->arr[index] = temp;

        maxHeapify(HP, largest);
    }
}

int buildMaxHeap(HeapPtr HP) {
    // Set heap size to match the length of the input array
    HP->heapSize = HP->length;

    // Make index start at the halfpoint of the array
    // since the second half of the array = leaves
    // and so are already max-heaps
    int index = floor(HP->length / 2) - 1;
    while (index >= 0) {
        maxHeapify(HP, index);
        index--;
    }
}

void heapSort(HeapPtr HP) {

    // Build a max heap from the array
    buildMaxHeap(HP);

    // Start from the last node in the heap
    int ctr = HP->length - 1;
    while (ctr > 0) {

        // Swapm out root with last node
        int temp = HP->arr[ctr];
        HP->arr[ctr] = HP->arr[0];
        HP->arr[0] = temp;

        // Disregard last node of the heap
        HP->heapSize--;

        // Re-establish max heap property w/ node
        // since swapping it out may have violated it
        maxHeapify(HP, 0);
        ctr--;
    }
}

void printArr(HeapPtr HP) {
    int ctr = 0;
    int length = sizeof(HP->arr) / sizeof(HP->arr[0]);
    while (ctr < length) {
        printf("%d\n", *(HP->arr + ctr));
        ctr++;
    }
}