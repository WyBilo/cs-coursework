#ifndef BTREE_H
#define BTREE_H

#include <string>
#include <fstream>
#include "BTreeNode.h"

class BTree {
private:
    std::string fileName;
    int order;
    int keySize;
    int nodeCount;

    static const long NULL_CHILD = -1;

    std::string padKey(const std::string& key) const;
    std::string trimKey(const std::string& key) const;

    int compareKeys(const std::string& leftKey, long leftPos,
                    const std::string& rightKey, long rightPos) const;

    int compareSearchKey(const std::string& searchKey,
                        const std::string& nodeKey) const;

    bool insertIntoLeaf(long nodePosition,
                        const std::string& key,
                        long recordPosition);

    int splitRootAndInsert(const std::string& key,
                        long recordPosition);

    int splitInternalRoot();

    int insertRecursive(long nodePosition,
                        const std::string& key,
                        long recordPosition);

    int findChildIndex(const BTreeNode& node,
                    const std::string& key,
                    long recordPosition) const;

    bool splitChild(long parentPosition, int childIndex);

    long searchFirstRecursive(long nodePosition,
                            const std::string& key);

    void searchAllRecursive(long nodePosition,
                            const std::string& key,
                            long*& results,
                            int& resultCount,
                            int& capacity);

    void dumpRecursive(long nodePosition,
                    long*& results,
                    int& resultCount,
                    int& capacity);

    void addResult(long value,
                long*& results,
                int& resultCount,
                int& capacity);

public:
    BTree(const std::string& fileName, int order, int keySize);

    bool createEmpty();

    BTreeNode readNode(long nodePosition);
    bool writeNode(long nodePosition, const BTreeNode& node);
    long appendNode(const BTreeNode& node);

    int insert(const std::string& key, long recordPosition);

    long searchFirst(const std::string& key);
    long* searchAll(const std::string& key, int& resultCount);
    long* dump(int& resultCount);

    int getNodeCount() const;
    int getOrder() const;
    int getKeySize() const;
    std::string getFileName() const;

    int getNodeSize() const;
};

#endif