#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node* next;
} Node, *NodePtr;

typedef struct {
    NodePtr head;
} LinkedList, *LinkedListPtr;

void initList(LinkedListPtr);
void listInsert(LinkedListPtr, int);
NodePtr listSearch(LinkedListPtr, int);
int listDelete(LinkedListPtr, NodePtr);

int main() {
    LinkedList LL;

    initList(&LL);
    listInsert(&LL, 5);
    listInsert(&LL, 6);
    listInsert(&LL, 8);
    listInsert(&LL, 9);

    NodePtr res = listSearch(&LL, 8);
    if (res) {
        printf("FOUND\n");
    } else {
        printf("NOT FOUND\n");
    }

    int x = listDelete(&LL, res);
    printf("Deleted %d\n", x);

    res = listSearch(&LL, 8);
    if (res) {
        printf("FOUND\n");
    } else {
        printf("NOT FOUND\n");
    }
    return 0;
}

void initList(LinkedListPtr llp) {
    llp->head = NULL;
}

void listInsert(LinkedListPtr llp, int key) {
    NodePtr NP = (NodePtr)malloc(sizeof(Node));

    if (NP != NULL) {
        NP->val = key;
        NP->next = llp->head;
        llp->head = NP;
    }
}

NodePtr listSearch(LinkedListPtr llp, int key) {
    NodePtr trav = llp->head;
    while (trav != NULL) {
        if (trav->val == key) {
            return trav;
        }
        trav = trav->next;
    }
}

int listDelete(LinkedListPtr llp, NodePtr NP) {
    if (listSearch(llp, NP)) {
        NodePtr trav = llp->head;
        while (trav->next != NP) {
            trav = trav->next;
        }

        int x = NP->val;
        trav->next = NP->next;
        free(NP);
        return x;
    }
}