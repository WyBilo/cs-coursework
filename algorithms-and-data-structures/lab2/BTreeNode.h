#ifndef BTREE_NODE_H
#define BTREE_NODE_H

#include <string>

class BTreeNode {
private:
    int order;
    int keySize;

public:
    int keyCount;
    bool isLeaf;

    std::string* keys;
    long* recordPositions;
    long* children;

    BTreeNode(int order, int keySize);
    BTreeNode(const BTreeNode& other);
    BTreeNode& operator=(const BTreeNode& other);
    ~BTreeNode();

    void clear();

    int getOrder() const;
    int getKeySize() const;
};

#endif