struct node* delete(struct node* root, int val) {
    if (root == NULL)
        return NULL;

    if (root->val == val) {
        if (root->left == NULL) {
            struct node *ret = root->right;
            free(root);
            return ret;
        }

        else if (root->right == NULL) {
            struct node *ret = root->left;
            free(root);
            return ret;
        }

        else if (root->left != NULL && root->right != NULL) {
            struct node *min_node = find_min(root->right);
            root->val = min_node->val;
            root->right = delete(root->right, min_node->val);
        }
    }

    else if (val > root->val)
        root->right = delete(root->right, val);
    
    else
        root->left = delete(root->left, val);

    set_height(root);
    struct node *n = try_rotate(root);
    return n;
}