bool similar(Node* t1, Node* t2) {
    if (t1 == nullptr && t2 == nullptr)
        return true;

    if (t1 == nullptr || t2 == nullptr)
        return false;

    return similar(t1->left, t2->left) &&
        similar(t1->right, t2->right);
}