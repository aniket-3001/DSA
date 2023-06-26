#include <stdio.h>
#include <stdlib.h>

struct node {
    int val;
    struct node* left;
    struct node* right;
};

struct return_type {
    struct node* root;
    struct node* deleted_node;
};

struct node* allocate_node(int val) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    
    return newNode;
}
struct node* find_min(struct node* root) {
    if (root == NULL || root->left == NULL)
        return root;

    return find_min(root->left);
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

struct return_type delete(struct node* root, int val) {
    struct return_type result;

    if (root == NULL) {
        result.root = NULL;
        result.deleted_node = NULL;
        return result;
    }

    if (root->val == val) {
        if (root->left == NULL) {
            result.root = root->right;
            result.deleted_node = root;
            return result;
        }

        else if (root->right == NULL) {
            result.root = root->left;
            result.deleted_node = root;
            return result;
        }

        else if (root->right != NULL && root->left != NULL) {
            struct node *min_node = find_min(root->right);
            root->val = min_node->val;
            struct return_type right_result = delete(root->right, min_node->val);
            root->right = right_result.root;
            result.root = root;
            result.deleted_node = right_result.deleted_node;
            return result;
        }
    }

    else if (val > root->val) {
        struct return_type right_result = delete(root->right, val);
        root->right = right_result.root;
        result.root = root;
        result.deleted_node = right_result.deleted_node;
        return result;
    }

    else {
        struct return_type left_result = delete(root->left, val);
        root->left = left_result.root;
        result.root = root;
        result.deleted_node = left_result.deleted_node;
        return result;
    }
}

void print_inorder(struct node *node) {
    if (node == NULL)
        return;

    print_inorder(node->left);
    printf("%d ", node->val);
    print_inorder(node->right);
}


int main() {
    struct node *root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("Before deletion:\n");
    print_inorder(root);

    struct return_type result = delete(root, 20);

    printf("\nAfter deletion:\n");
    printf("Deleted node value: %d\n", result.deleted_node->val);
    print_inorder(result.root);

    return 0;
}
