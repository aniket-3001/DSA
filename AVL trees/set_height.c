void set_height(struct node* n) {
    int l_height = (n->left) ? n->left->height: -1;
    int r_height = (n->right) ? n->right->height: -1;
    n -> height = (l_height > r_height) ? l_height + 1: r_height + 1;
}