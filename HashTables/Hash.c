#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 10
#define MAX_HASH 5

typedef struct node{
    char str[MAX_STRING];
    struct node* next;
} Node, *NodePtr;

typedef struct {
    NodePtr table[MAX_HASH];
} Hash, *HashPtr;

void initHash(HashPtr);
int hashFunction(char*);
void insertTable(HashPtr, char*);
NodePtr searchTable(HashPtr, char*);
void deleteTable(HashPtr, char*);
void printTable(HashPtr);

int main() {
    Hash HT;
    initHash(&HT);

    insertTable(&HT, "ANGELA");
    insertTable(&HT, "BEA");
    insertTable(&HT, "IMMANUEL");
    insertTable(&HT, "IMMANUEL");
    insertTable(&HT, "CD");
    insertTable(&HT, "DC");

    deleteTable(&HT, "DER");
    printTable(&HT);

    return 0;
}

void initHash(HashPtr HP) {
    int ctr;
    for (ctr = 0; ctr < MAX_HASH; ctr++) {
        HP->table[ctr] = NULL;
    }
}

int hashFunction(char* str) {
    int sum = 0;
    int ctr;
    for (ctr = 0; ctr<strlen(str); ctr++) {
        sum += (int) str[ctr];
    }

    return sum % strlen(str);
}

NodePtr searchTable(HashPtr HP, char* str) {
    int index = hashFunction(str);
    NodePtr trav = HP->table[index];
    
    while (trav != NULL) {
        if (!(strcmp(trav->str, str))) {
            break;
        }
        trav = trav->next;
    }

    return trav;
}

void insertTable(HashPtr HP, char* str) {
    NodePtr NP = searchTable(HP, str);
    if (NP == NULL) {
        int index = hashFunction(str);
        NodePtr temp = (NodePtr)malloc(sizeof(Node));

        if (temp != NULL) {
            strcpy(temp->str, str);
            temp->next = HP->table[index];
            HP->table[index] = temp;
        }
    } else {
        printf("'%s' is already present!\n", str);
    }
}

void deleteTable(HashPtr HP, char* str) {
    NodePtr NP = searchTable(HP, str);

    if (NP != NULL) {
        int index = hashFunction(str);
        NodePtr temp = (NodePtr)malloc(sizeof(Node));
        
        if (temp != NULL) {
            temp = HP->table[index];
            if (temp == NP) HP->table[index] = NP->next;
            else {
                while (temp->next != NP) temp = temp->next;
                temp->next = NP->next;
            }
            free(NP);
        }

    } else {
        printf("'%s' is not in the list!\n", str);
    }
}
void printTable(HashPtr HP) {
    int ctr;
    NodePtr trav = NULL;
    printf("\n----- PRINTING TABLE -----\n");
    for (ctr = 0; ctr < MAX_HASH; ctr++) {
        printf("%d: ", ctr);
        trav = HP->table[ctr];
        while (trav != NULL) {
            printf("%s -> ", trav->str);
            trav = trav->next;
        }
        printf("END\n");
    }
}