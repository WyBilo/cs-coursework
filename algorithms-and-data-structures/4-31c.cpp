int countFullNodes(Node* t) {
    if (t == nullptr)
        return 0;

    int count = 0;

    if (t->left != nullptr && t->right != nullptr)
        count = 1;

    return count + countFullNodes(t->left) + countFullNodes(t->right);
}