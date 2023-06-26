struct node* RL(struct node* n) {
    struct node *mid = n->right;
    struct node *new_root = mid->left;
    n->right = new_root->left;
    mid->left = new_root->right;
    new_root->left = n;
    new_root->right = mid;
    set_height(n);
    set_height(mid);
    set_height(new_root);
    return new_root;
}