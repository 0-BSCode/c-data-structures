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
void treeDelete(RBTPtr, treeNodePtr);
void treeDeleteFixup(RBTPtr, treeNodePtr);

int main() {
    RBT RB;
    initRBT(&RB);

    treeInsert(&RB, 11);
    treeInsert(&RB, 2);
    treeInsert(&RB, 14);
    treeInsert(&RB, 1);
    treeInsert(&RB, 7);
    treeInsert(&RB, 15);
    treeInsert(&RB, 5);
    treeInsert(&RB, 8);
    treeInsert(&RB, 4);

    printf("\n----- IN ORDER WALK -----\n");
    inOrderWalk(&RB, RB.root);
    printf("\n");

    treeNodePtr res = treeSearch(&RB, 8);
    treeDelete(&RB, res);

    printf("\n----- IN ORDER WALK -----\n");
    inOrderWalk(&RB, RB.root);

    return 0;
}

// Initialize red-black tree
void initRBT(RBTPtr RP) {
    // RP = pointer to RBT

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

        // Set its root to nothing
        RP->root = RP->nil;
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

    if (TP->parent == RP->nil) { // If TP's parent is nil, then TP is the root
        RP->root = TPr;
    } else if (TP == TP->parent->left) { // If TP is a left child
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
    if (TP->parent == RP->nil) {
        RP->root = TPl;
    } else if (TP == TP->parent->left) {
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

        if (trav->key == k) {
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
        if (TP->parent == RP->nil) {
            printf("ROOT: ");
        } else if (TP == TP->parent->left) {
            printf("LC OF %d: ", TP->parent->key);
        } else {
            printf("RC OF %d: ", TP->parent->key);
        }
        printf("%d %c\n", TP->key, TP->color); // Print current node
        inOrderWalk(RP, TP->right); // Print right nodes
    }
}

void transplant(RBTPtr RP, treeNodePtr TP1, treeNodePtr TP2) {
    // TP1 = node we want to replace
    // TP2 = node we want to replace TP1 with

    // Make TP1's parent point to TP2 as its new child depending on its nature
    if (TP1->parent == RP->nil) {
        RP->root = TP2;
    } else if (TP1 == TP1->parent->left) {
        TP1->parent->left = TP2;
    } else {
        TP1->parent->right = TP2;
    }

    // Set TP2's new parent to be TP1's parent
    TP2->parent = TP1->parent;
}

void treeInsert(RBTPtr RP, int k) {
    // RP = RBT we want to insert to
    // k = key of node we'll insert

    // Create temporary node pointer to point to a newly created node
    treeNodePtr temp = (treeNodePtr)malloc(sizeof(treeNode));

    if (temp != NULL) {

        // Initialize new node
        temp->key = k;
        temp->left = RP->nil;
        temp->right = RP->nil;
        temp->color = 'R'; // Color new node red

        // Create pointers to traverse down the tree
        treeNodePtr trail = RP->nil; // Ends at parent of temp
        treeNodePtr trav = RP->root; // Ends at RP->nil

        // Traverse down the tree
        while (trav != RP->nil) {
            trail = trav;

            if (k > trav->key) {
                trav = trav->right;
            } else {
                trav = trav->left;
            }
        }

        temp->parent = trail;

        // Set temp's parent to point to temp depending on nature of the parent
        if (trail == RP->nil) {
            RP->root = temp;
        } else if (k > trail->key) {
            trail->right = temp;
        } else {
            trail->left = temp;
        }

        // Call auxiliary procedure to restore any violated RBT properties
        treeInsertFixup(RP, temp);
    }
}

void treeInsertFixup(RBTPtr RP, treeNodePtr TP) {
    // RP = RBT we want to fix
    // TP = pointer to a newly inserted node

    /*
        Possible violations
        1. Node + node's parent = red
            - Can only be violated by TP and its parent since rest of tree isn't touched by operation
            and was consistent w/ RB properties before the insertion
        2. Root = red
    */
   
   // Keep executing loop while current node's parent is red
   // bc node is assumed to be red already
    while (TP->parent->color == 'R') {

       // If node's parent = its grandparent's left child
        if (TP->parent == TP->parent->parent->left) {
           treeNodePtr uncle = TP->parent->parent->right;

            // Case 1: Uncle is red
            if (uncle->color == 'R') {

                // Switch colors of parent and uncle w/ grandparent
                TP->parent->color = 'B';
                uncle->color = 'B';
                TP->parent->parent->color = 'R';

                // Grandparent becomes new node and loop = repeated
                TP = TP->parent->parent;

            } 
            
            // Cases 2 and 3 assume that uncle is black
            else {
                
                // Case 2: Current node is its parent's right child
                if (TP == TP->parent->right) {

                    // Make TP point to node's parent (moves up on level)
                    TP = TP->parent;

                    // Left Rotate TP (TP moves down one level)
                    // Makes TP point to left child, transforming case 2 to case 3
                    leftRotate(RP, TP);
                } 

                // Case 3: Current node is its parent's left child

                // Switch out parent's color w/ grandparent's color
                TP->parent->color = 'B';
                TP->parent->parent->color = 'R';

                // Right Rotate TP's grandparent
                rightRotate(RP, TP->parent->parent);

            }
        } 
       
       // If node's parent = its grandparent's right child
       // Symmetric to previous condition but with 'right' and 'left' exchanged
        else {
           treeNodePtr uncle = TP->parent->parent->left;

            if (uncle->color == 'R') {
                uncle->color = 'B';
                TP->parent->color = 'B';
                TP->parent->parent->color = 'R';
                TP = TP->parent->parent;
            } else {
                if (TP == TP->parent->left) {
                    TP = TP->parent;
                    rightRotate(RP, TP);
                }
                TP->parent->color = 'B';
                TP->parent->parent->color = 'R';
                leftRotate(RP, TP->parent->parent);
            }
        }
    }

   // Set root to black to restore RB property
   // in case root was turned red due to while loop operations
   RP->root->color = 'B';
}

// Delete a node from an RBT
void treeDelete(RBTPtr RP, treeNodePtr TP) {
    // RP = RBT we want to delete from
    // TP = node we want to delete

    // Create variables to track some other node in case it violates RB properties
    // when TP gets deleted
    treeNodePtr newTP = NULL;
    char newTPcol;

    // Keep track of newTP's child bc it'll take newTP's place in RBT after deletion
    treeNodePtr newTPchild = NULL;

    // Initially set newTP to TP and keep track of its original color
    newTP = TP;
    newTPcol = newTP->color;

    // If TP has no left child, its right child replaces it
    if (TP->left == RP->nil) {
        printf("Left child is empty!\n");
        newTPchild = TP->right;
        transplant(RP, TP, TP->right);
    } 
    // If TP has no right child, its left child replaces lit
    else if (TP->right == RP->nil) {
        printf("Right child is empty!\n");
        newTPchild = TP->left;
        transplant(RP, TP, TP->left);
    } 
    // If TP has two children, its successor replaces it
    else {
        printf("Node has two kids\n");

        // Reinitialize newTP, newTPcol, and newTPchild
        newTP = treeMin(RP, TP->right);
        newTPcol = newTP->color;
        newTPchild = newTP->right;

        // If newTP isn't a child of TP, transplant it w/ its right child
        // and start making TP's right subtree newTP's right subtree
        if (newTP->parent != TP) {
            transplant(RP, newTP, newTP->right);
            newTP->right = TP->right;
            newTP->right->parent = newTP;
        }

        // If newTP is a child of TP, above statement isn't necessary since
        // Transplanting TP with newTP will already do the trick

        // Replace TP w/ newTP
        transplant(RP, TP, newTP);
        newTP->left = TP->left;
        newTP->left->parent = newTP;

        // Have newTP inherit color of TP
        // RB properties = preserved in TP's region bc no colors change
        newTP->color = TP->color;
    }

    // If newTP was originally black, there may be violations of RB properties
    // so we call a fixup procedure to restore the properties
    if (newTPcol == 'B') {
        treeDeleteFixup(RP, newTPchild);
    }
}

void treeDeleteFixup(RBTPtr RP, treeNodePtr TP) {
    // RP = pointer to RBT we want to fix
    // TP = pointer to node that might be violating RB properties

    /*
        Problems if newTP was black
        1. If newTP = root (which should be black) and red child of y became new root
            - Violates property 2 (root should be black)
        2. If both newTPchild and newTPchild's new parent (not newTP anymore) are red
            - Violates property 4 (no two red nodes should be adjacent to each other)
        3. Moving newTP within tree causes any simple path that used to contain newTP to have one less black node
            - Any ancestor of newTP in tree violates property 5
            - Property 5 = for any node, all simple paths from node to descendant leaves should have same number of black nodes
                - Take a node -> all paths from that node (left or right subtree) down to leaf should have equal number of black nodes
    */

    // Fix = whatever node TP (which is newTPchild) points to has an extra black
    // newTP (original parent of newTPchild) passes its "blackness" onto newTPchild,
    // preserving property 5
    // Node pointed to by TP (aka newChildTP) is either red-and-black (if color = 'R') 
    // or doubly black (if color = 'B')

    // TP should always point to a nonroot doubly black node
    while (TP != RP->root && TP->color == 'B') {

        if (TP == TP->parent->left) {

            // Take note of TP's sibling + color of its children
            treeNodePtr sibling = TP->parent->right;
    
            // Case 1: Sibling's color is red
            if (sibling->color == 'R') {

                // Switch colors of parent and sibling
                sibling->color = 'B';
                TP->parent->color = 'R';

                // Left rotate parent with sibling
                leftRotate(RP, TP->parent);

                // Reset sibling (same relationship but node is now different due to rotation)
                sibling = TP->parent->right;

                // Case 1 is transformed into either case 2, 3, or 4
            }

            // Cases 2, 3, and 4 assume sibling is black

            // Case 2: Both sibling's kids are black
            else if (sibling->left->color == 'B' && sibling->right->color == 'B') {
                // Take one black off of TP and its sibling,
                // making TP singly black and sibling red
                // Compensate removal of black from them by moving 'blackness' to their parent
                // by making TP point to it

                sibling->color = 'R';
                TP = TP->parent;
            }

            // Cases 3 and 4 assume sibling's left child is red
            else {
                // Case 3: Sibling's left child is red and right child is black
                if (sibling->right->color == 'B') {
                    // Switch colors of sibling and its left child
                    sibling->left->color = 'B';
                    sibling->color = 'R';

                    // Right rotate sibling w/ its left child
                    rightRotate(RP, sibling);

                    // Reset sibling (same relationship but points to different node)
                    sibling = TP->parent->right;

                    // Transforms case 3 into case 4
                }

                // Case 4: Sibling's right child is red

                // Make some color changes + rotation to preserve RB properties
                sibling->color = TP->parent->color;
                TP->parent->color = 'B';
                sibling->right->color = 'B';
                leftRotate(RP, TP->parent);

                // Once color changes + rotations are made, extra black can be removed
                // by setting TP to point to the root of the tree (terminates the loop)
                TP = RP->root;
            }

        }

        // Assuming TP is its parent's right child
        else {
            treeNodePtr sibling = TP->parent->left;
            
            // Case 1
            if (sibling->color == 'R') {
                TP->parent->color = 'R';
                sibling->color = 'B';
                rightRotate(RP, TP->parent);
                sibling = TP->parent->left;
            }

            // Case 2
            else if (sibling->left->color == 'B' && sibling->right->color == 'B') {
                sibling->color = 'R';
                TP = TP->parent;
            }

            // Cases 3 and 4
            else {
                // Case 3
                if (sibling->left->color == 'B') {
                    sibling->right->color = 'B';
                    sibling->color = 'R';
                    leftRotate(RP, sibling);
                    sibling = TP->parent->left;
                }

                // Case 4
                sibling->color = TP->parent->color;
                TP->parent->color = 'B';
                sibling->left->color = 'B';
                rightRotate(RP, TP->parent);
                TP = RP->root;
            }
        }
    }
}
