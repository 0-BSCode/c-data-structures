#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct node {
    int key;
    char task[MAX];
    struct node* left;
    struct node* right;
    struct node* parent;
} Node, *NodePtr;

typedef struct {
    NodePtr root;
    int heapSize;
    int arrLength;
} PQueue, *PQueuePtr;

void queueInsert(NodePtr, int);
int queueGetMax(NodePtr);
NodePtr queueExtractMax(NodePtr);
void queueIncreaseKey(NodePtr, NodePtr, int);

int main() {
    int a[3] = {3, 2, 1};
    printf("Size of a: %d\n", sizeof(a) / sizeof(a[0]));
    return 0;
}