#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10
#define MAX_STRING 10

typedef struct node {
    char str[MAX_STRING];
    struct node* prev;
    struct node* next;
} Node, *NodePtr;

typedef struct {
    NodePtr arr[MAX_SIZE];
} Hash, *HashPtr;

void initHash(HashPtr);
void insertHash(HashPtr, char*);
void deleteHash(HashPtr, char*);
NodePtr searchHash(HashPtr, char*);
int hashFunction(char*);
void printTable(HashPtr);

int main() {
    Hash T;

    initHash(&T);
    insertHash(&T, "Hello");
    insertHash(&T, "Bye");
    insertHash(&T, "Hi");
    deleteHash(&T, "Hi");
    deleteHash(&T, "Bye");

    printTable(&T);

    return 0;
}

void initHash(HashPtr HP) {
    int ctr = 0;
    for (;ctr < MAX_SIZE; ctr++) {
        HP->arr[ctr] = NULL;
    }
}

int hashFunction(char* str) {
    int ctr = 0;
    int sum = 0;
    for (; ctr < MAX_STRING; ctr++) {
        sum += (int) str[ctr];
    }

    return sum % MAX_SIZE;
}

NodePtr searchHash(HashPtr HP, char* str) {
    int index = hashFunction(str);
    NodePtr trav = (NodePtr)malloc(sizeof(Node));

    if (trav != NULL) {
        trav = HP->arr[index];
        while (trav != NULL) {
            if (!strcmp(trav->str, str)) {
                return trav;
            }
            trav = trav->next;
        }
    }

    return NULL;
    
}

void insertHash(HashPtr HP, char* str) {
    NodePtr temp = searchHash(HP, str);

    if (temp == NULL) {
        int index = hashFunction(str);
        temp = (NodePtr)malloc(sizeof(Node));

        if (temp != NULL) {
            strcpy(temp->str, str);
            temp->next = HP->arr[index];
            temp->prev = NULL;

            HP->arr[index] = temp;
        }
    } else {
        printf("'%s' already in list!\n", str);
    }
}

void deleteHash(HashPtr HP, char* str) {
    NodePtr temp = searchHash(HP, str);

    if (temp != NULL) {
        printf("Deleting %s\n", str);
        if (temp->prev == NULL) {
            int index = hashFunction(str);
            HP->arr[index] = temp->next;
        } else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }
    } else {
        printf("'%s' not in list!\n", str);
    }
}

void printTable(HashPtr HP) {
    int ctr = 0;
    NodePtr trav = (NodePtr)malloc(sizeof(Node));

    for (; ctr < MAX_SIZE; ctr++) {
        printf("%d: ", ctr);
        trav = HP->arr[ctr];
        while (trav != NULL) {
            printf("%s <-> ", trav->str);
            trav = trav->next;
        }
        printf("END\n");
    }
}