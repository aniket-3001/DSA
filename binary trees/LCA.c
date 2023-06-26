#include <stdio.h>

struct node
{
    int val;
    struct node *left;
    struct node *right;
};

int lca(struct node *root, int v1, int v2)
{
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