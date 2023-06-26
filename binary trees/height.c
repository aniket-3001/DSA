int compute_height(struct node* root) { // height(root) = max(height(root->left), height(root->right))+1
    if (root == NULL)
        return 0;

    int ht = 0;
    int ht_left_subtree = compute_height(root->left);
    int ht_right_subtree = compute_height(root->right);

    if (ht_left_subtree > ht_right_subtree)
        ht = ht_left_subtree + 1;
    else
        ht = ht_right_subtree + 1;

    return ht;
}