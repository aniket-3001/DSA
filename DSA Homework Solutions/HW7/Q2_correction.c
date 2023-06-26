#include <stdio.h>

struct node
{
    int val;
    int status;
    struct node *left;
    struct node *right;
};

void reset_status(struct node *root)
{
    // root is the root of a binary tree
    // Output: reset the status in all the nodes in the binary tree
    if (root != NULL)
    {
        root->status = 0;
        reset_status(root->left);
        reset_status(root->right);
    }
}

struct ret_info
{
    int status;
    int lca;
};

struct ret_info mark_ancestors(struct node *root, int v1)
{
    // root: is the root of the binary tree
    // v1: the value we are searching for
    // This function sets the status of an ancestor of the node
    // we are searching for to one if it is zero; otherwise, if the
    // status is one then it's the LCA, which is returned to the caller
    // The return type is struct ret_info
    struct ret_info r;

    if (root == NULL)
    {
        r.status = 0;
        return r;
    }

    if (root->val == v1)
    {
        if (root->status == 1)
        {
            r.status = 2;
            r.lca = root->val;
            return r;
        }
        else
        {
            r.status = 1;
            root->status = 1;
            return r;
        }
    }

    r = mark_ancestors(root->left, v1);
    if (r.status == 2)
        return r;

    if (r.status == 1)
    {
        if (root->status == 1)
        {
            r.status = 2;
            r.lca = root->val;
        }
        else
        {
            root->status = 1;
        }
        return r;
    }

    r = mark_ancestors(root->right, v1);
    if (r.status == 1)
    {
        if (root->status == 1)
        {
            r.status = 2;
            r.lca = root->val;
        }
        else
        {
            root->status = 1;
        }
    }

    return r;
}

int lca(struct node *root, int v1, int v2)
{
    // root: is the root of the binary tree
    // v1: the integer value stored in the first node
    // v2: the integer value stored in the second node
    // The return value is the integer value stored in the LCA
    reset_status(root);

    struct ret_info r = mark_ancestors(root, v1);
    if (r.status == 1)
    {
        r = mark_ancestors(root, v2);
        if (r.status == 2)
            return r.lca;
    }

    perror("LCA not found");
    return -1; // or some other suitable value to indicate failure
}

#include <stdio.h>
#include <stdlib.h>

// Struct definitions and function declarations go here...

int main()
{
    // Create the binary tree
    struct node *root = (struct node *)malloc(sizeof(struct node));
    root->val = 1;
    root->status = 0;

    struct node *node2 = (struct node *)malloc(sizeof(struct node));
    node2->val = 2;
    node2->status = 0;

    struct node *node3 = (struct node *)malloc(sizeof(struct node));
    node3->val = 3;
    node3->status = 0;

    struct node *node4 = (struct node *)malloc(sizeof(struct node));
    node4->val = 4;
    node4->status = 0;

    struct node *node5 = (struct node *)malloc(sizeof(struct node));
    node5->val = 5;
    node5->status = 0;

    root->left = node2;
    root->right = node3;
    node2->left = node4;
    node2->right = NULL;
    node3->left = NULL;
    node3->right = node5;
    node4->left = NULL;
    node4->right = NULL;
    node5->left = NULL;
    node5->right = NULL;

    // Test the LCA function
    int v1 = 4;
    int v2 = 5;
    int lca_value = lca(root, v1, v2);

    if (lca_value != -1)
    {
        printf("LCA of %d and %d is %d\n", v1, v2, lca_value);
    }

    // Clean up the allocated memory
    free(node5);
    free(node4);
    free(node3);
    free(node2);
    free(root);

    return 0;
}
