#include <stdio.h>
#include <stdlib.h>

struct node {
    int val;
    struct node* left;
    struct node* right;
};

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

int main() {

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
    
    root->right->left->left = calloc(1, sizeof(struct node));
    root->right->left->left->val = 9;

    struct node *deepest_node = findDeepestNode(root);
    if (deepest_node != NULL)
        printf("The value of the deepest node in the tree is: %d\n", deepest_node->val);

    return 0;
}
