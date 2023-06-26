struct node* find_max(struct node* root) {
    if (root == NULL || root->right == NULL)
        return root;

    find_max(root->right);
}