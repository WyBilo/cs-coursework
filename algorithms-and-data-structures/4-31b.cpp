int countLeaves(Node* t) {
    if (t == nullptr)
        return 0;

    if (t->left == nullptr && t->right == nullptr)
        return 1;

    return countLeaves(t->left) + countLeaves(t->right);
}