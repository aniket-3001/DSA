int cnt_nodes(struct node* root) {
    if (root == NULL)
        return 0;

    int cnt = 1; // start with 1 for the root node

    cnt += cnt_nodes(root->left);
    cnt += cnt_nodes(root->right);
    
    return cnt;
}