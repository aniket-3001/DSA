int get_balance(struct node* n) {
    int l_height = (n->left) ? n->left->height: -1;
    int r_height = (n->right) ? n->right->height: -1;
    return l_height - r_height;
}