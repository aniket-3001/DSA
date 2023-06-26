// Give an algorithm to find the LCA (as discussed in the previous question) of
// two given nodes in a binary tree of integers. You can assume that all the nodes contain
// distinct values. You can add additional fields (e.g., a pointer to the parent, or a status
// field, etc.) in a node of the binary tree to compute LCA efficiently.
// The prototype of the lca routine is as follows:
// lca(root, v1, v2)
// root : is the root of the binary tree
// v1: the integer value stored in the first node
// v2: the integer value stored in the second node
// the return value is the integer value stored in the LCA

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
        root->status = 0;
    reset_status(root->left);
    reset_status(root->right);
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
    // this function sets the status of an ancestor of the node we are searching for
    // to one if it is zero; otherwise, if the status is one then it’s the LCA,
    // which is returned to the caller
    // the return type is struct ret_info

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
        return r;
    }

    return r;
}

int lca(struct node *root, int v1, int v2)
{
    // root: is the root of the binary tree
    // v1: the integer value stored in the first node
    // v2: the integer value stored in the second node
    // the return value is the integer value stored in the LCA

    reset_status(root);
    struct ret_info r = mark_ancestors(root, v1);
    if (r.status == 1)
    {
        r = mark_ancestors(root, v2);
        if (r.status == 2)
        {
            return r.lca;
        }
    }

    perror("LCA not found");
    return -1; // or any suitable default value
}
