int checkAVL(Node* t) {
    if (t == nullptr)
        return -1;

    int leftHeight = checkAVL(t->left);
    if (leftHeight == -2)
        return -2;

    int rightHeight = checkAVL(t->right);
    if (rightHeight == -2)
        return -2;

    int correctHeight = 1 + max(leftHeight, rightHeight);

    if (t->height != correctHeight)
        return -2;

    if (abs(leftHeight - rightHeight) > 1)
        return -2;

    return correctHeight;
}