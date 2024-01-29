#include <stdio.h>
#include <stdlib.h>

typedef struct tree {
    int data;
    struct tree* left;
    struct tree* right;
} tnode;

// --------------------------------------------------------------------------

// Function definitions
tnode* createNode(int data) {
    tnode* temp = (tnode*)malloc(sizeof(tnode));
    if (temp == NULL) {
        printf("Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

tnode* addnode(tnode* root, int data) {
    if (root == NULL) {
        tnode* temp = createNode(data);
        return temp;
    } else {
        if (data < root->data) {
            root->left = addnode(root->left, data);
        } else if (data > root->data) {
            root->right = addnode(root->right, data);
        }
    }
    return root;
}

void preorder(tnode* root) {
    if (root != NULL) {
        printf("%d, ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(tnode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d, ", root->data);
        inorder(root->right);
    }
}

void deltree(tnode* root) {
    if (root != NULL) {
        deltree(root->left);
        deltree(root->right);
        free(root);
    }
    printf("All roots deleted.\n");
}

// --------------------------------------------------------------------------


// ==========================================================================
int main(int argc, char* argv[]) {
    tnode* root = NULL;

    root = addnode(root, 3);
    root = addnode(root, 2);
    root = addnode(root, 5);
    root = addnode(root, 7);
    root = addnode(root, 6);
    root = addnode(root, 9);
    root = addnode(root, 12);
    root = addnode(root, 10);
    root = addnode(root, 15);
    
    inorder(root);
    printf("\n");
    preorder(root);

    deltree(root);

    return 0;
}
// =========================================================================


