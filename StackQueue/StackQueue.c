#include <stdio.h>
#include <stdlib.h>

#define ARR_SIZE 4

typedef struct {
    int arr[ARR_SIZE];
    int top;
} Stack;

typedef struct {
    int arr[ARR_SIZE];
    int head;
    int tail;
} Queue;

void initStack(Stack*);
void push(Stack*, int);
int pop(Stack*);

void initQueue(Queue*);
void enqueue(Queue*, int);
int dequeue(Queue*);
void printQueue(Queue*);

int main() {
    Stack S;
    initStack(&S);
    push(&S, 5);
    push(&S, 8);
    push(&S, 6);
    push(&S, 9);

    // int res = pop(&S);
    // printf("Popped %d\n", res);

    Queue Q;
    initQueue(&Q);
    // enqueue(&Q, 5);
    // enqueue(&Q, 6);
    // enqueue(&Q, 7);
    // enqueue(&Q, 8);
    // enqueue(&Q, 9);
    // enqueue(&Q, 10);
    // enqueue(&Q, 12);

    int res = dequeue(&Q);
    printf("res: %d\n", res);
    res = dequeue(&Q);
    printf("res: %d\n", res);
    printQueue(&Q);
    return 0;
}

void initStack(Stack* SP) {
    SP->top = -1;
}

void push(Stack* SP, int val) {
    if (SP->top < ARR_SIZE) {
        SP->top++;
        SP->arr[SP->top] = val;
    }
}

int pop(Stack* SP) {
    SP->top--;
    if (SP->top > -1) {
        return SP->arr[SP->top + 1];
    }
}

void initQueue(Queue* QP) {
    QP->head = -1;
    QP->tail = -1;
}

void enqueue(Queue* QP, int val) {
    if (QP->head == QP->tail + 1 || (QP->head == 0 && QP->tail == ARR_SIZE)) {
        printf("QUEUE FULL!\n");
    } else {
        if (QP->head == -1) {
            QP->head++;
            QP->tail++;
        }
        QP->arr[QP->tail] = val;
        QP->tail = (QP->tail + 1) % (ARR_SIZE+1);
    }
}

int dequeue(Queue* QP) {
    if (QP->tail == QP->head) {
        printf("QUEUE EMPTY!\n");
        return -9999;
    } else {
        int val = QP->arr[QP->head];
        QP->head = (QP->head + 1) % ARR_SIZE;
        return val;
    }
}

void printQueue(Queue* QP) {
    for (int i=0; i<ARR_SIZE; i++) {
        printf("%d\n", QP->arr[i]);
    }
}