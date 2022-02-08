#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    int val;
    struct node* next;
} Node, *NodePtr;

typedef struct {
    int count;
    NodePtr head;
    NodePtr tail;
} Queue, *QueuePtr;

void initialize(QueuePtr);
void enqueue(QueuePtr, int);
int dequeue(QueuePtr);
void printQueue(QueuePtr); // Test function

int main() {
    Queue Q;
    initialize(&Q);
    // enqueue(&Q, 5);
    // enqueue(&Q, 6);
    // enqueue(&Q, 7);
    // enqueue(&Q, 8);
    int res = dequeue(&Q);

    printf("Dequeued %d\n", res);
    printQueue(&Q);
    return 0;
}

void initialize(QueuePtr QP) {
    QP->count = 0;
    QP->head = NULL;
    QP->tail = NULL;
}

void enqueue(QueuePtr QP, int v) {
    NodePtr NP = (NodePtr)malloc(sizeof(Node));

    if (NP != NULL) {

        NP->val = v;
        NP->next = NULL;

        if (QP->head == NULL) {
            QP->head = NP;
            QP->tail = NP;
        } else {
            QP->tail->next = NP;
            QP->tail = NP;
        }

        QP->count++;
    }
}

int dequeue(QueuePtr QP) {
    if (QP->head == NULL) return -9999;

    NodePtr NP = (NodePtr)malloc(sizeof(Node));
    int v;

    if (NP != NULL) {
        NP = QP->head;
        v = QP->head->val;
        QP->head = QP->head->next;
        QP->count--;
        free(NP);

        return v;
    }
}

void printQueue(QueuePtr QP) {
    NodePtr trav = QP->head;

    while (trav != NULL) {
        printf("%d\n", trav->val);
        trav = trav->next;
    }
}


