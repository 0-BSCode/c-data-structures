#include <stdio.h>
#include <stdlib.h>

#define MAX 4

typedef struct {
    int next[MAX];
    int key[MAX];
    int prev[MAX];
} Array, *ArrayPtr;

typedef struct {
    int head;
} List, *ListPtr;

void initLists(ListPtr, ListPtr, ArrayPtr);
int allocateObject(ListPtr, ArrayPtr);
void freeObject(int, ListPtr, ArrayPtr);
void listInsert(ListPtr, int, ListPtr, ArrayPtr);
int listDelete(ListPtr, int, ListPtr, ArrayPtr);
void printArr(ArrayPtr);
void printList(ListPtr, ArrayPtr);

int main() {
    Array A;
    List free;
    List dll;


    initLists(&dll, &free, &A);
    printArr(&A);
    listInsert(&dll, 5, &free, &A);
    printArr(&A);
    listInsert(&dll, 69, &free, &A);
    printArr(&A);
    listInsert(&dll, 420, &free, &A);
    printArr(&A);
    listInsert(&dll, 790, &free, &A);
    printArr(&A);
    listInsert(&dll, 6, &free, &A);
    printArr(&A);

    printf("----- PRINTING LIST -----\n");
    printList(&dll, &A);

    return 0;
}

void initLists(ListPtr listP, ListPtr freeP, ArrayPtr AP) {
    int i;
    for (i = MAX-1; i >= 0; i--) {
        freeP->head = i;
        AP->next[i] = i+1;
        AP->key[i] = 0;
        AP->prev[i] = 0;
    }
    listP->head = -1;
}

int allocateObject(ListPtr freeP, ArrayPtr AP) {
    if (freeP->head == MAX) {
        printf("OUT OF SPACE\n");
        return -1;
    } else {
        int x = freeP->head;
        freeP->head = AP->next[freeP->head];
        return x;
    }
}

void freeObject(int index, ListPtr freeP, ArrayPtr AP) {
    AP->next[index] = freeP->head;
    freeP->head = index;
}

void listInsert(ListPtr listP, int val, ListPtr freeP, ArrayPtr AP) {
    int freeIndex = allocateObject(freeP, AP);
    if (freeIndex != -1) {
        AP->next[freeIndex] = listP->head;
        AP->key[freeIndex] = val;
        AP->prev[freeIndex] = MAX;
        AP->prev[listP->head] = freeIndex;
        listP->head = freeIndex;
    }
}

int listDelete(ListPtr listP, int index, ListPtr freeP, ArrayPtr AP) {
    int trav = listP->head;
    while (AP->key[trav] != index && trav != -1) {
        trav = AP->next[trav];
    }

    if (trav != -1) {
        int prevIndex = AP->prev[trav];
        int nextIndex = AP->next[trav];

        if (prevIndex == MAX) { // Element = list head
            AP->prev[nextIndex] = prevIndex;
            listP->head = nextIndex;
        } else if (nextIndex == -1) { // Element = list tail
            AP->next[prevIndex] = -1;
        } else {
            AP->next[prevIndex] = nextIndex;
            AP->prev[nextIndex] = prevIndex;
        }
        freeObject(trav, freeP, AP);       
    } else {
        printf("Key is not in list!\n");
    }

}

void printArr(ArrayPtr AP) {
    for (int i=0; i<MAX; i++) {
        printf("Elements at %d: ", i);
        printf("%d | ", AP->next[i]);
        printf("%d | ", AP->key[i]);
        printf("%d\n", AP->prev[i]);
    }
    printf("\n");
}

void printList(ListPtr LP, ArrayPtr AP) {
    int trav = LP->head;
    while (trav != -1) {
        printf("Next: %d | ", AP->next[trav]);
        printf("Key: %d | ", AP->key[trav]);
        printf("Prev: %d\n", AP->prev[trav]);
        trav = AP->next[trav];
    }
    printf("\n");
}