struct node* find_min(struct node* root) {
    if (root == NULL || root->left == NULL)
        return root;

    return find_min(root->left);
}