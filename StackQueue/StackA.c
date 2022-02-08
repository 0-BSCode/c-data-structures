#include <stdlib.h>
#include <stdio.h>

#define MAX 4

typedef struct {
    int top;
    int arr[MAX];
} Stack, *StackPtr;

void initStack(StackPtr);
int stackEmpty(StackPtr);
void push(StackPtr, int);
int pop(StackPtr);

int main() {
    Stack S;
    initStack(&S);

    return 0;
}

void initStack(StackPtr SP) {
    SP->top = -1;
}

int stackEmpty(StackPtr SP) {
    return SP->top == -1;
}

void push(StackPtr SP, int val) {
    if (SP->top + 1 == MAX) {
        printf("OVERFLOW\n");
    } else {
        SP->top++;
        SP->arr[SP->top] = val;
    }
}

int pop(StackPtr SP) {
    if (stackEmpty(SP)) {
        printf("UNDERFLOW\n");
        return -9999;
    } else {
        SP->top--;
        return SP->arr[SP->top + 1];
    }
}