#include <stdlib.h>
#include <stdio.h>

#define MAX 4

typedef struct {
    int arr[MAX];
    int head;
    int tail;
} Queue, *QueuePtr;

void initQueue(QueuePtr);
void enqueue(QueuePtr, int);
int dequeue(QueuePtr);

int main() {
    Queue Q;
    initQueue(&Q);

    return 0;
}

void initQueue(QueuePtr QP) {
    QP->head = 0;
    QP->tail = 0;
}

void enqueue(QueuePtr QP, int val) {
    if (QP->head == (QP->tail + 1) % MAX) {
        printf("OVERFLOW\n");
    } else {
        QP->arr[QP->tail] = val;
        QP->tail = (QP->tail + 1) % MAX;
    }
}

int dequeue(QueuePtr QP) {
    if (QP->head == QP->tail) {
        printf("UNDERFLOW\n");
        return -9999;
    } else {
        int val = QP->arr[QP->head];
        QP->head = (QP->head + 1) % MAX;
        return val;
    }
}