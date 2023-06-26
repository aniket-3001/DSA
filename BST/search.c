struct node* search(struct node* root, int val) {
    if (root == NULL)
        return root;

    if (root->val < val)
        return search(root->right, val);
    else if (root->val > val)
        return search(root->left, val);
    else
        return root;
}
