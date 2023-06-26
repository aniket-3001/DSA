int check_if_identical(struct node* h1, struct node* h2) {
    struct node *ptr1 = h1;
    struct node *ptr2 = h2;
    int ans = 1;
    while (ptr1 != NULL && ptr2 != NULL && ptr1->val == ptr2->val) {
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
        if (ptr1 == h1 && ptr2 == h2) {
            break;
        }
    }
    if (ptr1 != NULL || ptr2 != NULL) {
        ans = 0;
    }
    return ans;
}
