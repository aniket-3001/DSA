// In a BST, the number of operations required to search a key at depth d is
// directly proportional to d. Algorithm QuickSearch tries to reduce the number of
// operations when the same keys are frequently searched. During a search operation, if n
// is the node that contains the key, and n is not root, QuickSearch reduces the depth of n
// by one before returning it to the caller. The depths of other nodes may also change.
// QuickSearch doesn't violate the BST property during the reordering. For a successful
// search operation of a node at depth d, the time complexity should be O(d). In the
// following example, initially, the depth of 35 is 4. Let's say the application tries to search
// the following keys in the given order: 35, 35, 35, 15, 5.
// After the first search operation, the depth of 35 will be 3.
// After the second search operation, the depth of 35 will be 2.
// After the third search operation, the depth of 35 will be 1.
// After the fourth search operation, the depth of 15 will be either d-1 if d > 0 or zero, where
// d is the original depth of 15 before the search.
// After the fourth search operation, the depth of 5 will be either d-1 if d > 0 or zero, where
// d is the original depth of 5 before the search.
// The depth of other nodes may also change during a search operation.
// Give an algorithm for QuickSearch. QuickSearch returns the address of the node that
// contains the key and the root (possibly new) of the BST. If the key is not present,
// QuickSearch returns NULL and the original root of the BST.
// You are not allowed to change the type of a BST node. The type of a BST node is:

// struct Tree {
// int val;
// struct Tree *left;
// struct Tree *right;
// };

#include <stdio.h>
#include <stdlib.h>

struct Tree
{
    int val;
    struct Tree *left;
    struct Tree *right;
};

struct return_type
{
    struct Tree *address;
    struct Tree *root;
};

// Functions to perform various rotations

struct Tree *L(struct Tree *n)
{ // for levelling up a node which is on the left of its parent
    struct Tree *new_root = n->left;
    n->left = new_root->right;
    new_root->right = n;
    return new_root;
}

struct Tree *R(struct Tree *n)
{ // for levelling up a node which is on the right of its parent
    struct Tree *new_root = n->right;
    n->right = new_root->left;
    new_root->left = n;
    return new_root;
}

struct return_type QuickSearch(struct Tree *root, int key)
{
    struct return_type res;

    if (root == NULL)
    {
        res.address = NULL;
        res.root = NULL;
        return res;
    }

    if (root->left != NULL && root->left->val == key)
    {
        res.address = L(root);
        res.root = res.address;
        return res;
    }

    if (root->right != NULL && root->right->val == key)
    {
        res.address = R(root);
        res.root = res.address;
        return res;
    }

    if (root->val > key)
    {
        res = QuickSearch(root->left, key);
        if (res.address != NULL)
        {
            root->left = res.root;
            res.root = root;
        }
        return res;
    }

    if (root->val < key)
    {
        res = QuickSearch(root->right, key);
        if (res.address != NULL)
        {
            root->right = res.root;
            res.root = root;
        }
        return res;
    }

    res.address = root;
    res.root = root;
    return res;
}
