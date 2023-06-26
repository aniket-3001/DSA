#include <stdio.h>
#include <stdlib.h>

struct node {
    int val;
    struct node* left;
    struct node* right;
};

struct node* search(struct node* root, int val) {
    if (root == NULL)
        return NULL; // Return NULL when the root is NULL
    
    if (root->val == val)
        return root;
    
    struct node* left = search(root->left, val); // Recursively search left subtree
    if (left != NULL)
        return left;
    
    return search(root->right, val); // Recursively search right subtree
}

int cnt_nodes(struct node* root) {
    if (root == NULL)
        return 0;

    int cnt = 1; // start with 1 for the root node

    cnt += cnt_nodes(root->left);
    cnt += cnt_nodes(root->right);
    
    return cnt;
}

void search_min(struct node* root, int* min) {
    if (root == NULL)
        return;
    
    if (root->val < *min)
        *min = root->val;
    
    search_min(root->left, min);
    search_min(root->right, min);
}

void search_max(struct node* root, int* max) { // Changed function name to search_max
    if (root == NULL)
        return;
    
    if (root->val > *max)
        *max = root->val;
    
    search_max(root->left, max);
    search_max(root->right, max);
}

int compute_height(struct node* root) { // height(root) = max(height(root->left), height(root->right))+1
    if (root == NULL)
        return 0;

    int ht = 0;
    int ht_left_subtree = compute_height(root->left);
    int ht_right_subtree = compute_height(root->right);

    if (ht_left_subtree > ht_right_subtree)
        ht = ht_left_subtree + 1;
    else
        ht = ht_right_subtree + 1;

    return ht;
}

struct node* findDeepestNode(struct node* root) {
    if (root == NULL)
        return NULL;

    struct node* leftDeepest = findDeepestNode(root->left);
    struct node* rightDeepest = findDeepestNode(root->right);

    if (leftDeepest == NULL && rightDeepest == NULL)
        return root;

    if (leftDeepest == NULL)
        return rightDeepest;

    if (rightDeepest == NULL)
        return leftDeepest;

    if (compute_height(leftDeepest) > compute_height(rightDeepest))
        return leftDeepest;
    else
        return rightDeepest;
}

int cnt_leaves(struct node* root) {
    if (root -> left == NULL && root -> right == NULL)
        return 1;
    
    int cnt = 0;

    cnt += cnt_leaves(root -> left);
    cnt += cnt_leaves(root -> right);

    return cnt;
}

int lca(struct node* root, int v1, int v2) {
    if (root == NULL)
        return -1;
    
    if (root->val == v1 || root->val == v2)
        return root->val;
    
    int left = lca(root->left, v1, v2);
    int right = lca(root->right, v1, v2);

    if (left == -1)
        return right;

    else if (right == -1)
        return left;

    else
        return root->val;
}

void del_tree(struct node* root) {
    if (root == NULL)
        return;
    
    del_tree(root->left);
    del_tree(root->right);
    
    free(root);
}

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
    
    int min = root->val;
    int max = root->val;
    search_min(root, &min);
    search_max(root, &max);
    struct node *node = search(root, 2);
    int no_of_nodes = cnt_nodes(root);
    int height = compute_height(root);
    int lca_val = lca(root, 10, 14);
    
    printf("The minimum value in the tree is: %d\n", min);
    printf("The maximum value in the tree is: %d\n", max);

    if (node != NULL)
        printf("The left child of node with value 2 is: %d\n", node->left->val);

    printf("no. of nodes is %d\n", no_of_nodes);
    printf("height of the subtree is %d\n", height);

    struct node *deepest_node = findDeepestNode(root);
    if (deepest_node != NULL)
        printf("The value of the deepest node in the tree is: %d\n", deepest_node->val);

    int num_leaves = cnt_leaves(root);
    printf("The number of leaf nodes in the binary tree = %d", num_leaves);

    printf("common ancestor = %d", lca_val);
    
    // Free memory
    del_tree(root);
    
    return 0;
}

