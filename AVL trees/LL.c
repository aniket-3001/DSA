struct node* LL(struct node* n) {
    struct node *new_root = n->left;
    n->left = new_root->right;
    new_root->right = n;
    set_height(n);
    set_height(new_root);
    return new_root;
}