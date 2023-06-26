struct node* insert(struct node* root, int val) {

    if (root == NULL) {
        root = allocate_node(val);
        return root;
    }

    if (val >= root->val)
        root->right = insert(root->right, val);

    else
        root->left = insert(root->left, val);

    set_height(root);
    root = try_rotate(root);
    return root;
}