#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node* prev;
    struct node* next;
} Node;

typedef struct {
    int count;
    Node* linkedList;
} ll, *llp;

void makeNULL(llp LLP);
void insertFirst(llp LLP, int v);
void insertLast(llp LLP, int v);
void insertAtPos(llp LLP, int v, int p);
void deleteFirst(llp LLP);
void deleteLast(llp LLP);
void deleteAtPos(llp LLP, int p);
void printList(llp LLP);

int main() {
    ll A;
    makeNULL(&A);
    insertLast(&A, 69);
    insertLast(&A, 70);
    insertLast(&A, 71);
    insertAtPos(&A, 72, 3);
    insertAtPos(&A, 42, 2);
    deleteAtPos(&A, 4);

    printList(&A);
    return 0;
}

void makeNULL(llp LLP) {
    LLP->linkedList = NULL;
    LLP->count = 0;
}

void insertFirst(llp LLP, int v) {
    Node* temp = (Node*)malloc(sizeof(Node));
    if (temp != NULL) {
        temp->prev = NULL;
        temp->val = v;
        temp->next = LLP->linkedList;

        if (LLP->linkedList !=  NULL) {
            LLP->linkedList->prev = temp;
        }
        
        LLP->linkedList = temp;
        LLP->count++;
    }
}

void insertLast(llp LLP, int v) {
    Node* temp = (Node*)malloc(sizeof(Node));
    Node* trav = LLP->linkedList;

    if (temp != NULL) {
        temp->val = v;
        temp->next = NULL;
        if (LLP->linkedList != NULL) {
            for (;trav->next != NULL; trav=trav->next);
            trav->next = temp;
        } else {
            LLP->linkedList = temp;
        }
        temp->prev = trav;
        LLP->count++;
    }
}

void insertAtPos(llp LLP, int v, int p) {
    Node* temp = (Node*)malloc(sizeof(Node));
    Node* trav = LLP->linkedList;

    if (temp != NULL && p > 0 && p <= LLP->count) {
        if (p == 1) {
            insertFirst(LLP, v);
        } else if (p == LLP->count) {
            insertLast(LLP, v);
        } else {
            for (int i=1; i<p; i++) trav = trav->next;
            temp->prev = trav->prev;
            temp->val = v;
            temp->next = trav;
            trav->prev->next = temp;
            trav->prev = temp;
            LLP->count++;
        }
    }
}

void deleteFirst(llp LLP) {
    Node* temp = (Node*)malloc(sizeof(Node));

    if (temp != NULL && LLP->linkedList != NULL) {
        temp = LLP->linkedList;
        if (LLP->linkedList->next != NULL) {
            LLP->linkedList = LLP->linkedList->next;
            LLP->linkedList->prev = NULL;

        } else {
            LLP->linkedList = NULL;
        }
        free(temp);
        LLP->count--;
    }
}

void deleteLast(llp LLP) {
    Node* temp = (Node*)malloc(sizeof(Node));
    Node* trav = LLP->linkedList;

    if (temp != NULL && trav != NULL) {
        for (;trav->next !=NULL; trav=trav->next);
        if (trav->prev != NULL) {
            trav->prev->next = NULL;
        } else {
            LLP->linkedList = NULL;
        }
        free(temp);
        LLP->count--;
    }
}

void deleteAtPos(llp LLP, int p) {
    Node* temp = (Node*)malloc(sizeof(Node));
    Node* trav = LLP->linkedList;

    if (temp != NULL && p > 0 && p <= LLP->count) {
        if (p == 1) {
            deleteFirst(LLP);
        } else if (p == LLP->count) {
            deleteLast(LLP);
        } else {
            for (int i=1;i<p; i++) trav = trav->next;
            trav->next->prev = trav->prev;
            trav->prev->next = trav->next;
            free(temp);
            LLP->count--;
        }
    }
}

void printList(llp LLP) {
    Node* NP = LLP->linkedList;
    
    printf("\n---- LIST -----\n");
    for (;NP->next != NULL; NP=NP->next) {
        printf("%d <-> ", NP->val);
    }
    printf("%d\n", NP->val);
    printf("Elements: %d\n", LLP->count);
}