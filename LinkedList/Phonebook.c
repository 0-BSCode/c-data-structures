#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char name[30];
    char num[15];
    struct node* next;
} Node, *NodePtr;

void listInsert(NodePtr*, char name[], char number[]);
void listDelete(NodePtr*, char name[]);
void listSearch(NodePtr*, char name[]);
void listPrint(NodePtr*);
void showMenu();

int main() {
    NodePtr LL = NULL;
    char choice, name[30], number[15];

    while (1) {
        showMenu();
        scanf("%c", &choice);
        fflush(stdin);

        if (choice == 'i') {
            printf("Name: ");
            fgets(name, 30, stdin);
            name[strlen(name) - 1] = '\0';
            printf("Number: ");
            fgets(number, 15, stdin);
            number[strlen(number) - 1] = '\0';

            listInsert(&LL, name, number);
        } 
        else if (choice == 'd') {
            printf("Name: ");
            fgets(name, 30, stdin);
            name[strlen(name) - 1] = '\0';

            listDelete(&LL, name);
        }
        else if (choice == 's') {
            printf("Name: ");
            fgets(name, 30, stdin);
            name[strlen(name) - 1] = '\0';

            listSearch(&LL, name);
        }
        else if (choice == 'p') {
            listPrint(&LL);
        }
        else if (choice == 'e') {
            break;
        } 
        else {
            printf("Invalid command!\n");
        }
        
        printf("\n");
    }

    return 0;
}

void showMenu() {
    printf("\nMENU\n");
    printf("[i]nsert\n");
    printf("[d]elete\n");
    printf("[s]earch\n");
    printf("[p]rint\n");
    printf("[e]xit\n");
    printf("Command: ");
}

void listInsert(NodePtr* NPP, char name[], char number[]) {
    if (strlen(name) == 0 || strlen(number) == 0) {
        printf("Lacking information!\n");
    } else {
        NodePtr trav = *NPP;
        NodePtr trail = NULL;

        while (trav != NULL) {
            trail = trav;
            trav = trav->next;
        }

        NodePtr temp = (NodePtr)malloc(sizeof(Node));

        if (temp != NULL) {
            strcpy(temp->name, name);
            strcpy(temp->num, number);
            temp->next = NULL;

            if (trail == NULL) (*NPP) = temp;
            else trail->next = temp;
        }
    }
}

// Issue: When deleting phonebook w/ 1 entry, gibberish gets printed
void listDelete(NodePtr* NPP, char name[]) {
    NodePtr trav = *NPP;
    NodePtr trail = (NodePtr)malloc(sizeof(Node));

    if (trail != NULL) {
        while (trav != NULL) {

            if (!strcmp(trav->name, name)) {
                trail->next = trav->next;
                free(trav);
                break;
            }

            trail = trav;
            trav = trav->next;
        }
    }
}

void listSearch(NodePtr* NPP, char name[]) {
    NodePtr trav = *NPP;

    while (trav != NULL) {
        if (!strcmp(trav->name, name)) {
            printf("\nEntry Found\n");
            printf("Name: %s\n", trav->name);
            printf("Number: %s", trav->num);
            break;
        }

        trav = trav->next;
    }

    if (trav == NULL) {
        printf("%s not in phonebook\n", name);
    }
}

void listPrint(NodePtr* NPP) {
    NodePtr trav = *NPP;

    printf("\nPhonebook\n");
    while (trav != NULL) {
        printf("%-30s\t\t%s\n", trav->name, trav->num);
        trav = trav->next;
    }
}