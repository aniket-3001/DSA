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