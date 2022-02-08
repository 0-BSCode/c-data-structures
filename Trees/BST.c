#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode {
    int key;
    struct treeNode* parent;
    struct treeNode* left;
    struct treeNode* right;
} TreeNode, *TreeNodePtr;

typedef struct {
    TreeNodePtr root;
} BST, *BSTPtr;

void initBST(BSTPtr);
void treeInsert(BSTPtr, int);
TreeNodePtr treeSearch(BSTPtr, int);
void transplant(BSTPtr, TreeNodePtr, TreeNodePtr);
void treeDelete(BSTPtr, TreeNodePtr);
void inOrderWalk(TreeNodePtr);
void postOrderWalk(TreeNodePtr);
void preOrderWalk(TreeNodePtr);
TreeNodePtr treeMin(TreeNodePtr);
TreeNodePtr treeMax(TreeNodePtr);
TreeNodePtr treeSuccessor(TreeNodePtr);
TreeNodePtr treePredecessor(TreeNodePtr);

int main() {
    BST B;
    initBST(&B);

    treeMax(B.root);
    treeInsert(&B, 5);
    treeInsert(&B, 4);
    treeInsert(&B, 9);
    treeInsert(&B, 1);
    treeInsert(&B, 2);
    treeInsert(&B, 3);
    treeInsert(&B, 6);
    treeInsert(&B, 10);

    TreeNodePtr res1 = treeSearch(&B, 3);
    TreeNodePtr res2 = treeSearch(&B, 6);

    treeSuccessor(res1);
    treePredecessor(res2);

    printf("\n---- IN ORDER -----\n");
    inOrderWalk(B.root);
    printf("\n");

    printf("\n---- POST ORDER -----\n");
    postOrderWalk(B.root);
    printf("\n");

    printf("\n---- PRE ORDER -----\n");
    preOrderWalk(B.root);
    printf("\n");
    // treeDelete(&B, res2);
    // treeDelete(&B, res1);

    // printf("\n---- AFTER DELETE -----\n");
    // printf("ROOT: %d\n", B.root->key);


    return 0;
}

void initBST(BSTPtr BP) {
    BP->root = NULL; // Make root (TreeNode Ptr) point to nothing
}

void treeInsert(BSTPtr BP, int val) {
    // BP = pointer to BST we want to manipulate; val = value we want to insert

    TreeNodePtr temp = (TreeNodePtr)malloc(sizeof(TreeNode)); // Create pointer to a tree node that will be the new node
    TreeNodePtr trav = (TreeNodePtr)malloc(sizeof(TreeNode)); // Create pointer to traverse BST (ends on a NULL where node will be inserted)
    TreeNodePtr trail = (TreeNodePtr)malloc(sizeof(TreeNode)); // Create pointer to trail behind travelling pointer (ends on parent of new node)

    if (temp != NULL && trav != NULL && trail != NULL) { // If temp, trav, and trail have been allocated

        // Initialize temp 
        temp->key = val;
        temp->right = NULL;
        temp->left = NULL;

        if (BP->root == NULL) { // If tree is empty
            BP->root = temp;
            temp->parent = NULL;
        } else {
            trav = BP->root;
            while (trav != NULL) {
                trail = trav; // Set trail equal to trav before changing trav (becomes trav's parent)
                
                // Check which path trav will have to take down the tree
                // Equal elements are placed to the right
                if (val >= trav->key) {
                    trav = trav->right;
                } else {
                    trav = trav->left;
                }
            
            }
            temp->parent = trail; // New node's parent is just the trail pointer

            // Decide if temp is trail's left child or right child
            if (val >= trail->key) {
                trail->right = temp;
            } else {
                trail->left = temp;
            }
        }
    }
}

TreeNodePtr treeSearch(BSTPtr BP, int val) {
    // BP = pointer to BST we want to manipulate; val = value we want to search

    TreeNodePtr trav = (TreeNodePtr)malloc(sizeof(TreeNode)); // Create a pointer to traverse the tree

    if (trav != NULL) {
        trav = BP->root; // Initialize trav

        while (trav != NULL) { // Keep traversing until trav is NULL (which means val isn't in the list)

            if (trav->key == val) {
                printf("%d in list\n", val);
                return trav;
            } else if (trav->key > val) { // If current node's key is greater than val, go left
                trav = trav->left;
            } else { // If current node's key is less than val, go right
                trav = trav->right;
            }
        }
        
        if (trav == NULL) { // Print a message saying the value being searched isn't in the list
            printf("%d not in list\n", val);
        }

        return trav;
    }
}

TreeNodePtr treeMin(TreeNodePtr TP) {
    // BP = pointer to BST we want to manipulate

    TreeNodePtr trav = TP; // Initialize a traversal pointer

    if (trav != NULL) {
        while (trav->left != NULL) { // Keep going left to find tree's minimum key
            trav = trav->left;
        }

        printf("Minimum: %d\n", trav->key);
        return trav;
    } else {
        printf("Tree is empty!\n");
    }
}

TreeNodePtr treeMax(TreeNodePtr TP) { 
    // BP = pointer to BST we want to manipulate

    TreeNodePtr trav = TP; // Initialize a traversal pointer

    if (trav != NULL) {
        while (trav->right != NULL) { // Keep going right to find tree's maximum key
            trav = trav->right;
        }

        printf("Maximum: %d\n", trav->key);
        return trav;
    } else {
        printf("Tree is empty!\n");
    }
}

void transplant(BSTPtr BP, TreeNodePtr TP1, TreeNodePtr TP2) { 
    // BP = pointer to BST we want to manipulate; TP1 = pointer to node we want to replace; TP2 = pointer to node we replace TP1 with
    printf("Transplanting %d\n", TP1->key);

    if (TP1->parent == NULL) { // TP1 is the root;
        printf("%d is root\n", TP1->key);
        BP->root = TP2;
    } else if (TP1 == TP1->parent->left) { // TP1 is its parent's left child
        printf("%d is left child\n", TP1->key);
        TP1->parent->left = TP2;
    } else { // TP1 is its parent's right child
        printf("%d is right child\n", TP1->key);
        TP1->parent->right = TP2;
    }

    if (TP2 != NULL) { // If TP2 isn't null, change it's parent attribute (if it was null, there's no attribute to set)
        TP2->parent = TP1->parent;
    } else {
        printf("TP2 is null!\n");
    }
}

// FIX!!! Entire tree ends up deleted for some reason
void treeDelete(BSTPtr BP, TreeNodePtr TP) { 
    // BP = pointer BST we want to manipulate; TP = pointer to node that we want to delete

    if (TP->left == NULL) { // If node has no left child, transplant it w/ its right child (possible for right child to not exist too)
        printf("%d has no left child!\n", TP->key);
        transplant(BP, TP, TP->right);
    } else if (TP->right == NULL) { // If node has no right child, transplant it w/ its left child (possible for left child to not exist too)
        printf("%d has no right child!\n", TP->key);
        transplant(BP, TP, TP->left);
    } else {
        TreeNodePtr temp = (TreeNodePtr)malloc(sizeof(TreeNode));
        if (temp != NULL) {
            temp = treeMin(TP->right);
            printf("%d's successor: %d\n", TP->key, temp->key);
            if (temp->parent != TP) { // If successor isn't TP's child (it's somewhere in the right subtree)
                printf("TP is not temp's parent!\n");
                transplant(BP, temp, temp->right); // Transplant temp out w/ its right child
                temp->right = TP->right; // temp's right child is TP's right child
                temp->right->parent = temp; // Set the parent of temp's right child to temp (originally pointed to TP)
            }

            transplant(BP, TP, temp); // Whether or not temp is TP's right child, replace TP with temp
            temp->left = TP->left; // Set temp's left child to be TP's left child;
            temp->left->parent = temp; // Set the parent of temp's left child to be temp (originally pointed to TP)
            free(TP); // Delete node pointed to by TP
        }
    }
}

void inOrderWalk(TreeNodePtr TP) {
    // TP = pointer to node we want to manipulate

    if (TP != NULL) { // If current node pointer isn't null
        inOrderWalk(TP->left); // Print current node's left child
        printf("%d\n", TP->key); // Print current node
        inOrderWalk(TP->right); // Print current node's right child
    }
}

void postOrderWalk(TreeNodePtr TP) {
    // TP = pointer to node we want to manipulate

    if (TP != NULL) { // If current node pointer isn't null
        postOrderWalk(TP->left); // Print current node's left child
        postOrderWalk(TP->right); // Print current node's right child
        printf("%d\n", TP->key); // Print current node

    }
}

void preOrderWalk(TreeNodePtr TP) {
    // TP = pointer to node we want to manipulate

    if (TP != NULL) { // If current node pointer isn't null
        printf("%d\n", TP->key); // Print current node
        preOrderWalk(TP->left); // Print current node's left child
        preOrderWalk(TP->right); // Print current node's right child
    }
}

// Get node with minimum key that's greater than the current node's key
TreeNodePtr treeSuccessor(TreeNodePtr TP) {
    // TP = pointer to node

    // Go down the tree to look for successor
    // If right child isn't empty, get the minimum element in its left subtree
    if (TP->right != NULL) { 
        return treeMin(TP->right);
    }

    // Go up the tree to look for successor
    // Create pointers that point to current node and its parent
    TreeNodePtr child = TP;
    TreeNodePtr par = TP->parent;

    // While node's parent isn't NULL (not at the root yet) and
    // while node is its parent's right child
    while (par != NULL && child == par->right) {

        // Move up the tree
        child = par;
        par = par->parent;
    }

    if (par != NULL) {
        printf("Successor of %d: %d\n", TP->key, par->key);
    } else {
        printf("Successor of %d doesn't exist\n", TP->key);
    }
    return par;
}

TreeNodePtr treePredecessor(TreeNodePtr TP) {
    // TP = pointer to node

    // Go down the tree
    // Check TP's left child's right subtree if TP's left child isn't NULL
    if (TP->left != NULL) {
        return treeMax(TP->left);
    }

    // Go up the tree
    // Create pointers to point to current node and its parent
    TreeNodePtr child = TP;
    TreeNodePtr par = TP->parent;

    // While parent isn't NULL (current node isn't root yet) and
    // child is still its parent's left child
    while (par != NULL && child == par->left) {

        // Move up the tree
        child = par;
        par = par->parent;
    }

    if (par != NULL) {
        printf("Precessor of %d: %d\n", TP->key, par->key);
    } else {
        printf("Precessor of %d doesn't exist\n", TP->key);
    }

    return par;
}
