#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    int val;
    struct node* next;
} Node, *NodePtr;

typedef struct {
    int count;
    NodePtr top;
} Stack, *StackPtr;

void initStack(StackPtr);
int pop(StackPtr);
void push(StackPtr, int);
int peek(StackPtr);
int isEmpty(StackPtr);
void printStack(StackPtr); // Test function

int main() {
    Stack S;

    initStack(&S);

    push(&S, 5);
    push(&S, 6);
    push(&S, 7);
    push(&S, 8);

}

void initStack(StackPtr SP) {
    SP->top = NULL;
}

int pop(StackPtr SP) {
    if (SP->top == NULL) return -9999;

    NodePtr NP = (NodePtr)malloc(sizeof(Node));

    if (NP != NULL) {

        NP = SP->top;
        int v = NP->val;
        SP->top = SP->top->next;
        free(NP);

        return v;
    }
}

void push(StackPtr SP, int v) {
    NodePtr NP = (NodePtr)malloc(sizeof(Node));

    if (NP != NULL) {

        NP->val = v;
        NP->next = SP->top;
        SP->top = NP;

    }
}

int peek(StackPtr SP) {
    if (SP->top == NULL) return -9999;
    return SP->top->val;
}

int isEmpty(StackPtr SP) {
    return SP->top == NULL;
}

void printStack(StackPtr SP) {
    NodePtr NP = SP->top;
    
    for (; NP != NULL; NP = NP->next) {
        printf("%d\n", NP->val);
    }

}