#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node* parent;
    struct node* left;
    struct node* right;
    char color;
} treeNode, *treeNodePtr;

typedef struct {
    treeNodePtr root;
    treeNodePtr nil;
} RBT, *RBTPtr;

void initRBT(RBTPtr);
void leftRotate(RBTPtr, treeNodePtr);
void rightRotate(RBTPtr, treeNodePtr);
void inOrderWalk(RBTPtr, treeNodePtr);
treeNodePtr treeMax(RBTPtr, treeNodePtr);
treeNodePtr treeMin(RBTPtr, treeNodePtr);
treeNodePtr treeSuccessor(RBTPtr, treeNodePtr);
treeNodePtr treePredecessor(RBTPtr, treeNodePtr);
treeNodePtr treeSearch(RBTPtr, int);
void transplant(RBTPtr, treeNodePtr, treeNodePtr);
void treeInsert(RBTPtr, int);
void treeInsertFixup(RBTPtr, treeNodePtr);
void treeDelete(RBTPtr, int);
void treeDeleteFixup(RBTPtr, treeNodePtr);

int main() {
    RBT RB;
    initRBT(&RB);
    return 0;
}

// Initialize red-black tree
void initRBT(RBTPtr RP) {
    // RP = pointer to RBT

    // Set its root to nothing
    RP->root = NULL;

    // Initialize its nil node (substitute to NIL value in BST)
    // Only important initialization = setting color to black
    treeNodePtr temp = (treeNodePtr)malloc(sizeof(treeNode));
    if (temp != NULL) {
        temp->color = 'B';
        temp->parent = NULL;
        temp->left = NULL;
        temp->right = NULL;
        temp->key = 0;

        RP->nil = temp;
    }
}

// TP becomes TP left child
// TP right child becomes TP
// Left child of TP right child becomes right child of TP
void leftRotate(RBTPtr RP, treeNodePtr TP) {
    treeNodePtr TPr = TP->right; // Have pointer point to TP right child
    TP->right = TPr->left; // Turn TPr's left tree into TP's right tree
    if (TPr->left != RP->nil) TPr->left->parent = TP; // Link TP's new left tree to TP
    TPr->parent = TP->parent; // TPr's new parent is TP's parent
    if (TP->parent = RP->nil) { // If TP's parent is nil, then TP is the root
        RP->root = TPr;
    } else if (TP = TP->parent->left) { // If TP is a left child
        TP->parent->left = TPr;
    } else { // If TP is a right child
        TP->parent->right = TPr;
    }
    TPr->left = TP;
    TP->parent = TPr;
}


// TP becomes TP right child
// TP left child becomes TP
// Right child of TP left child becomes left child of TP
void rightRotate(RBTPtr RP, treeNodePtr TP) {
    treeNodePtr TPl = TP->left; // Have a pointer point to TP's left child
    TP->left = TPl->right; // Turn TPl's right tree into TP's left tree
    if (TPl->right != RP->nil) TPl->right->parent = TP; // If TPl right child isn't nil, set its parent attribute to TP
    TPl->parent = TP->parent; // Let TPl's parent be TP's parent

    // Set parent of TPl to have TPl as its child (depending on TPl parent's nature)
    if (TP->parent == RP->root) {
        RP->root = TPl;
    } else if (TP = TP->parent->left) {
        TP->parent->left = TPl;
    } else {
        TP->parent->right = TPl;
    }


    // Make TPl's right child TP and TP's parent TPl
    TPl->right = TP;
    TP->parent = TPl;
}

// Find the largest element in the tree
treeNodePtr treeMax(RBTPtr RP, treeNodePtr TP) {
    treeNodePtr trav = TP; // Initialize a pointer for traversal

    if (trav != RP->nil) { // If trav is NULL, then the tree is empty
        // Keep going to the rightmost node
        while (trav->right != RP->nil) trav = trav->right;

        printf("Maximum: %d\n", trav->key);
        return trav;
    } else {
        printf("Tree is empty\n");
    }

}

// Find the smallest element in the tree
treeNodePtr treeMin(RBTPtr RP, treeNodePtr TP) {
    treeNodePtr trav = TP; // Initialize a pointer for traversal

    if (trav != RP->nil) { // If trav is NULL, then the tree is empty
        // Keep going to the leftmost node
        while (trav->left != RP->nil) trav = trav->left;

        printf("Minimum: %d\n", trav->key);
        return trav;
    } else {
        printf("Tree is empty\n");
    }

}

// Search tree for a specific key
treeNodePtr treeSearch(RBTPtr RP, int k) {
    // RP = pointer to tree we want to search
    // k = integer value we want to search

    treeNodePtr trav = RP->root;

    while (trav != NULL) {

        if (trav->key = k) {
            printf("%d in list\n", k);
            return trav;
        } else if (trav->key > k) {
            trav = trav->left;
        } else {
            trav = trav->right;
        }
    }

}

treeNodePtr treeSuccessor(RBTPtr RP, treeNodePtr TP) {
    // RP = pointer to RBT
    // TP = pointer to node

    // Go down tree to find minimum if possible
    if (TP->right != RP->nil) {
        return treeMin(RP, TP->right);
    }

    // Go up the tree to find minimum if possible
    treeNodePtr child = TP;
    treeNodePtr par = TP->parent;

    while (par != RP->nil && child == par->right) {
        child = par;
        par = par->parent;
    }

    if (par != RP->nil) {
        printf("Successor of %d: %d\n", TP->key, par->key);
    } else {
        printf("%d has no successor\n", TP->key);
    }

    return par;
}

treeNodePtr treePredecessor(RBTPtr RP, treeNodePtr TP) {
    // RP = pointer to RBT
    // TP = pointer to node

    // Go down tree to find minimum if possible
    if (TP->left != RP->nil) {
        return treeMax(RP, TP->left);
    }

    // Go up the tree to find minimum if possible
    treeNodePtr child = TP;
    treeNodePtr par = TP->parent;

    while (par != RP->nil && child == par->left) {
        child = par;
        par = par->parent;
    }

    if (par != RP->nil) {
        printf("Predecesor of %d: %d\n", TP->key, par->key);
    } else {
        printf("%d has no predecessor\n", TP->key);
    }

    return par;
}

void inOrderWalk(RBTPtr RP, treeNodePtr TP) {
    if (TP != RP->nil) {
        inOrderWalk(RP, TP->left); // Print left nodes
        printf("%d\n", TP->key); // Print current node
        inOrderWalk(RP, TP->right); // Print right nodes
    }
}

void transplant(RBTPtr RP, treeNodePtr TP1, treeNodePtr TP2) {
    // TP1 = node we want to replace
    // TP2 = node we want to replace TP1 with

    // Make TP1's parent point to TP2 as its new child depending on its nature
    if (TP1->parent == RP->nil) {
        RP->root = TP2;
    } else if (TP1 = TP1->parent->left) {
        TP1->parent->left = TP2;
    } else {
        TP1->parent->right = TP2;
    }

    // Set TP2's new parent to be TP1's parent
    TP2->parent = TP1->parent;
}

// void treeInsert(RBTPtr, int);
// void treeInsertFixup(RBTPtr, treeNodePtr);
// void treeDelete(RBTPtr, int);
// void treeDeleteFixup(RBTPtr, treeNodePtr);
