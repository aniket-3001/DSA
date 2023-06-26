#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node.
struct node {
    int val;
    struct node* left;
    struct node* right;
};

// Function to find the value of LCA of two nodes in a BST.
int lca(struct node* root, int v1, int v2) {
    if (root == NULL) {
        return -1; // indicate that there is no LCA
    }

    if (v1 < root->val && v2 < root->val) {
        return lca(root->left, v1, v2);
    }

    if (v1 > root->val && v2 > root->val) {
        return lca(root->right, v1, v2);
    }

    // for any other case
    return root->val;
}



// Function to create a new node.
struct node* newNode(int val) {
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to insert a new node with a given value into a BST.
struct node* insertNode(struct node* root, int val) {
    if (root == NULL)
        return newNode(val);

    if (val < root->val) {
        root->left = insertNode(root->left, val);
    } else if (val > root->val) {
        root->right = insertNode(root->right, val);
    }

    return root;
}

int main() {
    // Create a binary search tree.
    struct node* root = NULL;
    root = insertNode(root, 50);
    insertNode(root, 30);
    insertNode(root, 70);
    insertNode(root, 20);
    insertNode(root, 40);
    insertNode(root, 60);
    insertNode(root, 80);
    insertNode(root, 10);
    insertNode(root, 25);
    insertNode(root, 65);
    insertNode(root, 90);
    insertNode(root, 55);
    insertNode(root, 67);

//            50
//          /  \
//        30    70
//       /  \   / \
//     20   40 60  80
//    / \        \   \
//  10  25       65  90
//               / \
//              55  67

    // Find the LCA of nodes with values 55 and 65.
    int v1 = 55, v2 = 65;
    int lca_val = lca(root, v1, v2);
    if (lca_val == -1)
        printf("No LCA found for values %d and %d\n", v1, v2);
    else
        printf("LCA of %d and %d is %d\n", v1, v2, lca_val);

    return 0;
}
