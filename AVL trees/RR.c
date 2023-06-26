struct node* RR(struct node* n) {
    struct node *new_root = n->right;
    n->right = new_root->left;
    new_root->left = n;
    set_height(n);
    set_height(new_root);
    return new_root;
}