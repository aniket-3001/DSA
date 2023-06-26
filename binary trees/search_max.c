void search_max(struct node* root, int* max) { // Changed function name to search_max
    if (root == NULL)
        return;
    
    if (root->val > *max)
        *max = root->val;
    
    search_max(root->left, max);
    search_max(root->right, max);
}