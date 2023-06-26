struct node* try_rotate(struct node* n) {
    int bal = get_balance(n);

    if (bal < -1) {
        bal = get_balance(n->right);
        if (bal > 0)
            n = RL(n);
        
        else
            n = RR(n);
    }

    else if (bal > 1) {
        bal = get_balance(n->left);
        if (bal < 0)
            n = LR(n);

        else
            n = LL(n);
    }
    return n;
}