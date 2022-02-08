#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 5
#define MAX_STRING 10

typedef struct {
    char arr[MAX][MAX_STRING];
} Table, *TablePtr;

void initTable(TablePtr);
void insertTable(TablePtr, char*);
int searchTable(TablePtr, char*);
void deleteTable(TablePtr, char*);
int hashFunctionLP(char*, int);
void printTable(TablePtr);

int main() {
    Table T;
    initTable(&T);

    insertTable(&T, "Hi");
    insertTable(&T, "Hello");
    insertTable(&T, "World");
    insertTable(&T, "Boi");
    insertTable(&T, "Biiii");
    insertTable(&T, "Biiiitch");

    deleteTable(&T, "World");
    deleteTable(&T, "World");

    int res = searchTable(&T, "HI");
    if (res != -1) {
        printf("Index: %d\n", res);
    }
    printTable(&T);

    return 0;
}

void initTable(TablePtr TP) {
    int ctr = 0;
    for (; ctr < MAX; ctr++) {
        strcpy(TP->arr[ctr], "NULL");
    }
}

int hashFunctionLP(char* str, int offset) {
    int k = 0;
    for (int i = 0; i < strlen(str); i++) {
        k += (int) str[i];
    }
    k += offset;
    return k % MAX;
}

void insertTable(TablePtr TP, char* str) {
    int ctr = 0;
    int index;

    do {
        index = hashFunctionLP(str, ctr);
        ctr++;
    } while (strcmp(TP->arr[index], "NULL") && ctr != MAX - 1);
    
    if (!strcmp(TP->arr[index], "NULL")) {
        strcpy(TP->arr[index], str);
    } else {
        printf("Table is full!\n");
    }
}

int searchTable(TablePtr TP, char* str) {
    int ctr = 0;
    int index;

    do {
        index = hashFunctionLP(str, ctr);
        ctr++;
        if (!strcmp(TP->arr[index], str)) {
            return index;
        }
    } while (strcmp(TP->arr[index], "NULL") && ctr != MAX - 1);
    
    printf("%s not in list\n", str);
    return -1;
}

void deleteTable(TablePtr TP, char* str) {
    int index = searchTable(TP, str);
    if (index != -1) {
        strcpy(TP->arr[index], "DELETED");
    }
}

void printTable(TablePtr TP) {
    int ctr = 0;
    for (; ctr < MAX; ctr++) {
        printf("%d: %s\n", ctr, TP->arr[ctr]);
    }
}