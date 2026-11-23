#include "BTreeNode.h"

BTreeNode::BTreeNode(int order, int keySize) {
    this->order = order;
    this->keySize = keySize;

    keyCount = 0;
    isLeaf = true;

    keys = new std::string[order];
    recordPositions = new long[order];
    children = new long[order + 1];

    clear();
}

BTreeNode::BTreeNode(const BTreeNode& other) {
    order = other.order;
    keySize = other.keySize;
    keyCount = other.keyCount;
    isLeaf = other.isLeaf;

    keys = new std::string[order];
    recordPositions = new long[order];
    children = new long[order + 1];

    for (int i = 0; i < order; i++) {
        keys[i] = other.keys[i];
        recordPositions[i] = other.recordPositions[i];
    }

    for (int i = 0; i < order + 1; i++) {
        children[i] = other.children[i];
    }
}

BTreeNode& BTreeNode::operator=(const BTreeNode& other) {
    if (this == &other) {
        return *this;
    }

    delete[] keys;
    delete[] recordPositions;
    delete[] children;

    order = other.order;
    keySize = other.keySize;
    keyCount = other.keyCount;
    isLeaf = other.isLeaf;

    keys = new std::string[order];
    recordPositions = new long[order];
    children = new long[order + 1];

    for (int i = 0; i < order; i++) {
        keys[i] = other.keys[i];
        recordPositions[i] = other.recordPositions[i];
    }

    for (int i = 0; i < order + 1; i++) {
        children[i] = other.children[i];
    }

    return *this;
}

BTreeNode::~BTreeNode() {
    delete[] keys;
    delete[] recordPositions;
    delete[] children;
}

void BTreeNode::clear() {
    keyCount = 0;
    isLeaf = true;

    for (int i = 0; i < order; i++) {
        keys[i] = "";
        recordPositions[i] = -1;
    }

    for (int i = 0; i < order + 1; i++) {
        children[i] = -1;
    }
}

int BTreeNode::getOrder() const {
    return order;
}

int BTreeNode::getKeySize() const {
    return keySize;
}