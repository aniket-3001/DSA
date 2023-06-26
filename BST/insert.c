#include <stdio.h>
#include <stdlib.h>

struct node {
    int val;
    struct node* left;
    struct node* right;
};

struct node* allocate_node(int val) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    
    return newNode;
}

struct node* insert(struct node* root, int val) {
    if (root == NULL)
        return allocate_node(val);

    if (val < root->val)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);

    return root;
}

void print_tree_in_order(struct node* root) {
    if (root == NULL)
        return;

    print_tree_in_order(root->left);
    printf("%d ", root->val);
    print_tree_in_order(root->right);
}

int main() {
    struct node* root = NULL;

    // insert some values into the binary search tree
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 3);
    root = insert(root, 7);
    root = insert(root, 6);

    // print the binary search tree in order
    print_tree_in_order(root);

    return 0;
}
