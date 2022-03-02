#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 15

typedef struct {
    int arr[MAX];
    int heapSize;
    int length;
} Heap, *HeapPtr;

int parent(int);
int left(int);
int right(int);
int maxHeapify(HeapPtr);
int buildMaxHeap(HeapPtr);
void initHeap(HeapPtr);
void printArr(HeapPtr);

int main() {
    Heap H;
    int index = 2;
    initHeap(&H);
    printArr(&H);
    printf("Node: %d\n", H.arr[index]);
    printf("Left: %d\n", H.arr[left(index)]);
    printf("Right: %d\n", H.arr[right(index)]);
    return 0;
}

void initHeap(HeapPtr HP) {
    int ctr = 0;
    while (ctr < MAX) {
        HP->arr[ctr] = (rand() % (MAX - 0 + 1));
        ctr++;
    }

    HP->heapSize = 0;
    HP->length = 0;
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

void printArr(HeapPtr HP) {
    int ctr = 0;
    int length = sizeof(HP->arr) / sizeof(HP->arr[0]);
    while (ctr < length) {
        printf("%d\n", *(HP->arr + ctr));
        ctr++;
    }
}