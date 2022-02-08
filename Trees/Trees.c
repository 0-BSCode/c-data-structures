#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode {
    int val;
    struct treeNode* parent;
    struct treeNode* left;
    struct treeNode* right;
} TreeNode;

void treeInsert(TreeNode** TPP, int v);
void inorderTreeWalk(TreeNode* TP);
void treeSearch(TreeNode* TP, int v);

int main() {
    TreeNode* firstTP = NULL;

    treeInsert(&firstTP, 5);
    treeInsert(&firstTP, 6);
    treeInsert(&firstTP, 4);
    treeInsert(&firstTP, 2);
    treeInsert(&firstTP, 8);
    treeInsert(&firstTP, 9);
    treeInsert(&firstTP, 7);
    treeInsert(&firstTP, 5);

    // inorderTreeWalk(firstTP);
    treeSearch(firstTP, 10);
}

void treeInsert(TreeNode** TPP, int v) {
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode* trav = *TPP;
    TreeNode* trav2 = NULL;

    if (temp != NULL) {
        while (trav != NULL) {
            trav2 = trav;
            if (v < trav->val) {
                trav = trav->left;
            } else {
                trav = trav->right;
            }
        }

        temp->val = v;
        temp->parent = trav2;
        temp->left = NULL;
        temp->right = NULL;
    
        if (trav2 == NULL) {
            *TPP = temp;
        } else if (v < trav2->val) {
            trav2->left = temp;
        } else {
            trav2->right = temp;
        }
    }
}

void inorderTreeWalk(TreeNode* TP) {
    TreeNode* trav = TP;
    if (trav != NULL) {
        inorderTreeWalk(trav->left);
        printf("%d", trav->val);
        inorderTreeWalk(trav->right);
    }
}

void treeSearch(TreeNode* TP, int v) {
    int present = 0;

    while (TP != NULL) {
        if (v == TP->val) {
            present = 1;
            break;
        } else if (v < TP->val) {
            TP = TP->left;
        } else {
            TP = TP->right;
        }
    }

    if (present) {
        printf("%d is present!\n", v);
    } else {
        printf("%d is absent!\n", v);
    }
}