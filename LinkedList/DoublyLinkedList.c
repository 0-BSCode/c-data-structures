#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    int key;
    struct node* prev;
    struct node* next;
} Node, *NodePtr;

typedef struct {
    NodePtr head;
} LinkedList, *LinkedListPtr;

void initList(LinkedListPtr);
NodePtr listSearch(LinkedListPtr, int);
void listInsert(LinkedListPtr, int);
void listDelete(LinkedListPtr, int);
void printList(LinkedListPtr);

int main() {
    LinkedList LL;
    initList(&LL);

    listInsert(&LL, 5);
    listInsert(&LL, 6);
    listInsert(&LL, 7);
    listInsert(&LL, 8);
    listInsert(&LL, 9);

    listDelete(&LL, 7);
    printList(&LL);
    return 0;
}

void initList(LinkedListPtr LP) {
    LP->head = NULL;
}

NodePtr listSearch(LinkedListPtr LP, int k) {
    NodePtr x = LP->head;
    while (x != NULL) {
        if (x->key == k) break;
        x = x->next;
    }
    return x;
}

void listInsert(LinkedListPtr LP, int k) {
    NodePtr NP = (NodePtr)malloc(sizeof(Node));

    if (NP != NULL) {
        NP->key = k;
        NP->prev = NULL;
        NP->next = LP->head;
        if (LP->head != NULL) LP->head->prev = NP;
        LP->head = NP;
    }
}

void listDelete(LinkedListPtr LP, int k) {
    NodePtr x = listSearch(LP, k);
    
    if (x != NULL) {
        if (x->next != NULL) {
            x->next->prev = x->prev;
        }
        
        if (x->prev != NULL) {
            x->prev->next = x->next;
        } else {
            LP->head = x->next;
        }
    }
}

void printList(LinkedListPtr LP) {
    NodePtr trav = LP->head;

    while (trav != NULL) {
        printf("%d\n", trav->key);
        trav = trav->next;
    }
}