struct node* LR(struct node* n) {
    struct node *mid = n->left;
    struct node *new_root = mid->right;
    n->left = new_root->right;
    mid->right = new_root->left;
    new_root->right = n;
    new_root->left = mid;
    set_height(mid);
    set_height(n);
    set_height(new_root);
    return new_root;
}