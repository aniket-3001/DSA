#include <stdio.h>
#include <stdlib.h>

// Definition of a binary tree node
struct node {
    int val;
    struct node* left;
    struct node* right;
};

// Function to find the path to a specified node in a binary tree
int findPath(struct node* root, int path[], int index, int key) {
    // Base case: root is null
    if (root == NULL)
        return 0;
    
    // Store the current node's val in the path array
    path[index] = root->val;
    index++;
    
    // If the key is found, return the index
    if (root->val == key)
        return index;
    
    // Recur on the left and right subtrees
    int leftIndex = findPath(root->left, path, index, key);
    int rightIndex = findPath(root->right, path, index, key);
    
    // If the key is found in the left subtree, return its index
    if (leftIndex)
        return leftIndex;
    
    // If the key is found in the right subtree, return its index
    if (rightIndex)
        return rightIndex;
    
    // If the key is not found in the tree, return 0
    return 0;
}

// Function to create a new binary tree node
struct node* newNode(int val) {
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Driver function
int main() {
    // Create a binary tree with the following structure:
    //                 1
    //              /     \
    //            2         3
    //          /   \     /   \
    //         4     5   6     7
    //        / \         \     \
    //       8   9        10    11
    //           / \            / \
    //         12   13        14   15
    
struct node* root = calloc(1, sizeof(struct node));
    root->val = 1;
    
    root->left = calloc(1, sizeof(struct node));
    root->left->val = 2;
    
    root->right = calloc(1, sizeof(struct node));
    root->right->val = 3;
    
    root->left->left = calloc(1, sizeof(struct node));
    root->left->left->val = 4;
    
    root->left->right = calloc(1, sizeof(struct node));
    root->left->right->val = 5;
    
    root->right->left = calloc(1, sizeof(struct node));
    root->right->left->val = 6;
    
    root->right->right = calloc(1, sizeof(struct node));
    root->right->right->val = 7;
    
    root->left->left->left = calloc(1, sizeof(struct node));
    root->left->left->left->val = 8;
    
    root->left->left->right = calloc(1, sizeof(struct node));
    root->left->left->right->val = 9;
    
    root->right->left->right = calloc(1, sizeof(struct node));
    root->right->left->right->val = 10;
    
    root->right->right->right = calloc(1, sizeof(struct node));
    root->right->right->right->val = 11;
    
    root->left->left->right->left = calloc(1, sizeof(struct node));
    root->left->left->right->left->val = 12;
    
    root->left->left->right->right = calloc(1, sizeof(struct node));
    root->left->left->right->right->val = 13;
    
    root->right->right->right->left = calloc(1, sizeof(struct node));
    root->right->right->right->left->val = 14;
    
    root->right->right->right->right = calloc(1, sizeof(struct node));
    root->right->right->right->right->val = 15;
    
    int path[100];
    int index = 0;
    int key = 11;
    
    int pathLength = findPath(root, path, index, key);
    
    if (pathLength) {
        printf("Path to node %d: ", key);
        for (int i = 0; i < pathLength - 1; i++) {
            printf("%d -> ", path[i]);
        }
        printf("%d", path[pathLength - 1]);
    } else {
        printf("node not found");
    }
    
    return 0;
}
