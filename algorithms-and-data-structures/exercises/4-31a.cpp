int countNodes(Node* t) {
    if (t == nullptr)
        return 0;

    return 1 + countNodes(t->left) + countNodes(t->right);
}