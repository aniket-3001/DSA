void search_min(struct node* root, int* min) {
    if (root == NULL)
        return;
    
    if (root->val < *min)
        *min = root->val;
    
    search_min(root->left, min);
    search_min(root->right, min);
}