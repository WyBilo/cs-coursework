#include "BTree.h"

BTree::BTree(const std::string& fileName, int order, int keySize) {
    this->fileName = fileName;
    this->order = order;
    this->keySize = keySize;
    this->nodeCount = 0;
}

std::string BTree::padKey(const std::string& key) const {
    if ((int)key.length() >= keySize) {
        return key.substr(0, keySize);
    }

    return key + std::string(keySize - key.length(), ' ');
}

std::string BTree::trimKey(const std::string& key) const {
    std::string result = key;

    while (!result.empty() && result[result.length() - 1] == ' ') {
        result.erase(result.length() - 1);
    }

    return result;
}

int BTree::compareKeys(const std::string& leftKey, long leftPos,
                    const std::string& rightKey, long rightPos) const {
    if (leftKey < rightKey) {
        return -1;
    }

    if (leftKey > rightKey) {
        return 1;
    }

    if (leftPos < rightPos) {
        return -1;
    }

    if (leftPos > rightPos) {
        return 1;
    }

    return 0;
}

int BTree::compareSearchKey(const std::string& searchKey,
                            const std::string& nodeKey) const {
    if (searchKey < nodeKey) {
        return -1;
    }

    if (searchKey > nodeKey) {
        return 1;
    }

    return 0;
}

bool BTree::insertIntoLeaf(long nodePosition,
                        const std::string& key,
                        long recordPosition) {
    BTreeNode node = readNode(nodePosition);

    if (!node.isLeaf) {
        return false;
    }

    if (node.keyCount >= order - 1) {
        return false;
    }

    int insertIndex = node.keyCount - 1;

    while (insertIndex >= 0 &&
        compareKeys(key, recordPosition,
                    node.keys[insertIndex],
                    node.recordPositions[insertIndex]) < 0) {
        node.keys[insertIndex + 1] = node.keys[insertIndex];
        node.recordPositions[insertIndex + 1] = node.recordPositions[insertIndex];
        insertIndex--;
    }

    node.keys[insertIndex + 1] = key;
    node.recordPositions[insertIndex + 1] = recordPosition;
    node.keyCount++;

    return writeNode(nodePosition, node);
}

int BTree::splitRootAndInsert(const std::string& key,
                            long recordPosition) {
    BTreeNode oldRoot = readNode(0);

    if (!oldRoot.isLeaf) {
        return -1;
    }

    int totalKeys = oldRoot.keyCount + 1;

    std::string* tempKeys = new std::string[totalKeys];
    long* tempRecordPositions = new long[totalKeys];

    int i = 0;
    int j = 0;
    bool inserted = false;

    while (i < oldRoot.keyCount) {
        if (!inserted &&
            compareKeys(key, recordPosition,
                        oldRoot.keys[i],
                        oldRoot.recordPositions[i]) < 0) {
            tempKeys[j] = key;
            tempRecordPositions[j] = recordPosition;
            j++;
            inserted = true;
        }

        tempKeys[j] = oldRoot.keys[i];
        tempRecordPositions[j] = oldRoot.recordPositions[i];
        i++;
        j++;
    }

    if (!inserted) {
        tempKeys[j] = key;
        tempRecordPositions[j] = recordPosition;
    }

    int promoteIndex = order / 2;

    BTreeNode newRoot(order, keySize);
    BTreeNode leftChild(order, keySize);
    BTreeNode rightChild(order, keySize);

    newRoot.clear();
    leftChild.clear();
    rightChild.clear();

    newRoot.isLeaf = false;
    newRoot.keyCount = 1;
    newRoot.keys[0] = tempKeys[promoteIndex];
    newRoot.recordPositions[0] = tempRecordPositions[promoteIndex];

    leftChild.isLeaf = true;
    rightChild.isLeaf = true;

    for (int k = 0; k < promoteIndex; k++) {
        leftChild.keys[leftChild.keyCount] = tempKeys[k];
        leftChild.recordPositions[leftChild.keyCount] = tempRecordPositions[k];
        leftChild.keyCount++;
    }

    for (int k = promoteIndex + 1; k < totalKeys; k++) {
        rightChild.keys[rightChild.keyCount] = tempKeys[k];
        rightChild.recordPositions[rightChild.keyCount] = tempRecordPositions[k];
        rightChild.keyCount++;
    }

    long leftPosition = appendNode(leftChild);
    long rightPosition = appendNode(rightChild);

    newRoot.children[0] = leftPosition;
    newRoot.children[1] = rightPosition;

    writeNode(0, newRoot);

    delete[] tempKeys;
    delete[] tempRecordPositions;

    return 1;
}

int BTree::findChildIndex(const BTreeNode& node,
                        const std::string& key,
                        long recordPosition) const {
    int index = 0;

    while (index < node.keyCount &&
        compareKeys(key, recordPosition,
                    node.keys[index],
                    node.recordPositions[index]) > 0) {
        index++;
    }

    return index;
}

bool BTree::splitChild(long parentPosition, int childIndex) {
    BTreeNode parent = readNode(parentPosition);

    long childPosition = parent.children[childIndex];

    if (childPosition == NULL_CHILD) {
        return false;
    }

    BTreeNode child = readNode(childPosition);

    if (child.keyCount < order - 1) {
        return false;
    }

    int promoteIndex = order / 2;

    BTreeNode rightChild(order, keySize);
    rightChild.clear();
    rightChild.isLeaf = child.isLeaf;

    std::string promotedKey = child.keys[promoteIndex];
    long promotedRecordPosition = child.recordPositions[promoteIndex];

    for (int i = promoteIndex + 1; i < child.keyCount; i++) {
        rightChild.keys[rightChild.keyCount] = child.keys[i];
        rightChild.recordPositions[rightChild.keyCount] = child.recordPositions[i];
        rightChild.keyCount++;
    }

    if (!child.isLeaf) {
        int rightChildIndex = 0;

        for (int i = promoteIndex + 1; i <= child.keyCount; i++) {
            rightChild.children[rightChildIndex] = child.children[i];
            rightChildIndex++;
        }
    }

    for (int i = promoteIndex; i < child.keyCount; i++) {
        child.keys[i] = "";
        child.recordPositions[i] = -1;
    }

    if (!child.isLeaf) {
        for (int i = promoteIndex + 1; i <= child.keyCount; i++) {
            child.children[i] = -1;
        }
    }

    child.keyCount = promoteIndex;

    long rightChildPosition = appendNode(rightChild);

    for (int i = parent.keyCount; i > childIndex; i--) {
        parent.keys[i] = parent.keys[i - 1];
        parent.recordPositions[i] = parent.recordPositions[i - 1];
    }

    for (int i = parent.keyCount + 1; i > childIndex + 1; i--) {
        parent.children[i] = parent.children[i - 1];
    }

    parent.keys[childIndex] = promotedKey;
    parent.recordPositions[childIndex] = promotedRecordPosition;
    parent.children[childIndex + 1] = rightChildPosition;
    parent.keyCount++;

    writeNode(childPosition, child);
    writeNode(parentPosition, parent);

    return true;
}

int BTree::splitInternalRoot() {
    BTreeNode oldRoot = readNode(0);

    if (oldRoot.keyCount < order - 1) {
        return 0;
    }

    long oldRootCopyPosition = appendNode(oldRoot);

    BTreeNode newRoot(order, keySize);
    newRoot.clear();
    newRoot.isLeaf = false;
    newRoot.keyCount = 0;
    newRoot.children[0] = oldRootCopyPosition;

    writeNode(0, newRoot);

    bool success = splitChild(0, 0);

    if (!success) {
        return -1;
    }

    return 1;
}

int BTree::insertRecursive(long nodePosition,
                        const std::string& key,
                        long recordPosition) {
    BTreeNode node = readNode(nodePosition);
    int splitCount = 0;

    if (node.isLeaf) {
        if (node.keyCount >= order - 1) {
            return -1;
        }

        bool success = insertIntoLeaf(nodePosition, key, recordPosition);

        if (!success) {
            return -1;
        }

        return splitCount;
    }

    int childIndex = findChildIndex(node, key, recordPosition);
    long childPosition = node.children[childIndex];

    if (childPosition == NULL_CHILD) {
        return -1;
    }

    BTreeNode child = readNode(childPosition);

    if (child.keyCount >= order - 1) {
        bool splitSuccess = splitChild(nodePosition, childIndex);

        if (!splitSuccess) {
            return -1;
        }

        splitCount++;

        node = readNode(nodePosition);

        if (compareKeys(key, recordPosition,
                        node.keys[childIndex],
                        node.recordPositions[childIndex]) > 0) {
            childIndex++;
        }
    }

    int result = insertRecursive(node.children[childIndex], key, recordPosition);

    if (result == -1) {
        return -1;
    }

    splitCount += result;

    return splitCount;
}

bool BTree::createEmpty() {
    std::ofstream outFile(fileName.c_str(), std::ios::binary | std::ios::trunc);

    if (!outFile) {
        return false;
    }

    BTreeNode root(order, keySize);
    root.clear();
    root.isLeaf = true;
    root.keyCount = 0;

    outFile.close();

    nodeCount = 0;

    long rootPosition = appendNode(root);

    return rootPosition == 0;
}

BTreeNode BTree::readNode(long nodePosition) {
    BTreeNode node(order, keySize);

    std::ifstream inFile(fileName.c_str(), std::ios::binary);

    if (!inFile) {
        return node;
    }

    inFile.seekg(nodePosition, std::ios::beg);

    int storedKeyCount = 0;
    int storedIsLeaf = 1;

    inFile.read(reinterpret_cast<char*>(&storedKeyCount), sizeof(int));
    inFile.read(reinterpret_cast<char*>(&storedIsLeaf), sizeof(int));

    node.keyCount = storedKeyCount;
    node.isLeaf = storedIsLeaf == 1;

    char* keyBuffer = new char[keySize + 1];

    for (int i = 0; i < order; i++) {
        inFile.read(keyBuffer, keySize);
        keyBuffer[keySize] = '\0';
        node.keys[i] = trimKey(std::string(keyBuffer, keySize));
    }

    delete[] keyBuffer;

    for (int i = 0; i < order; i++) {
        inFile.read(reinterpret_cast<char*>(&node.recordPositions[i]), sizeof(long));
    }

    for (int i = 0; i < order + 1; i++) {
        inFile.read(reinterpret_cast<char*>(&node.children[i]), sizeof(long));
    }

    inFile.close();

    return node;
}

bool BTree::writeNode(long nodePosition, const BTreeNode& node) {
    std::fstream file(fileName.c_str(), std::ios::binary | std::ios::in | std::ios::out);

    if (!file) {
        return false;
    }

    file.seekp(nodePosition, std::ios::beg);

    int storedKeyCount = node.keyCount;
    int storedIsLeaf = node.isLeaf ? 1 : 0;

    file.write(reinterpret_cast<const char*>(&storedKeyCount), sizeof(int));
    file.write(reinterpret_cast<const char*>(&storedIsLeaf), sizeof(int));

    for (int i = 0; i < order; i++) {
        std::string fixedKey = padKey(node.keys[i]);
        file.write(fixedKey.c_str(), keySize);
    }

    for (int i = 0; i < order; i++) {
        file.write(reinterpret_cast<const char*>(&node.recordPositions[i]), sizeof(long));
    }

    for (int i = 0; i < order + 1; i++) {
        file.write(reinterpret_cast<const char*>(&node.children[i]), sizeof(long));
    }

    file.close();

    return true;
}

long BTree::appendNode(const BTreeNode& node) {
    std::ofstream outFile(fileName.c_str(), std::ios::binary | std::ios::app);

    if (!outFile) {
        return -1;
    }

    long nodePosition = nodeCount * getNodeSize();

    int storedKeyCount = node.keyCount;
    int storedIsLeaf = node.isLeaf ? 1 : 0;

    outFile.write(reinterpret_cast<const char*>(&storedKeyCount), sizeof(int));
    outFile.write(reinterpret_cast<const char*>(&storedIsLeaf), sizeof(int));

    for (int i = 0; i < order; i++) {
        std::string fixedKey = padKey(node.keys[i]);
        outFile.write(fixedKey.c_str(), keySize);
    }

    for (int i = 0; i < order; i++) {
        outFile.write(reinterpret_cast<const char*>(&node.recordPositions[i]), sizeof(long));
    }

    for (int i = 0; i < order + 1; i++) {
        outFile.write(reinterpret_cast<const char*>(&node.children[i]), sizeof(long));
    }

    outFile.close();

    nodeCount++;

    return nodePosition;
}

int BTree::insert(const std::string& key, long recordPosition) {
    BTreeNode root = readNode(0);
    int splitCount = 0;

    if (root.isLeaf && root.keyCount < order - 1) {
        bool success = insertIntoLeaf(0, key, recordPosition);

        if (!success) {
            return -1;
        }

        return splitCount;
    }

    if (root.isLeaf && root.keyCount >= order - 1) {
        return splitRootAndInsert(key, recordPosition);
    }

    if (!root.isLeaf && root.keyCount >= order - 1) {
        int rootSplitResult = splitInternalRoot();

        if (rootSplitResult == -1) {
            return -1;
        }

        splitCount += rootSplitResult;
    }

    int recursiveResult = insertRecursive(0, key, recordPosition);

    if (recursiveResult == -1) {
        return -1;
    }

    splitCount += recursiveResult;

    return splitCount;
}

void BTree::addResult(long value,
                    long*& results,
                    int& resultCount,
                    int& capacity) {
    if (resultCount >= capacity) {
        int newCapacity = capacity * 2;
        long* newResults = new long[newCapacity];

        for (int i = 0; i < resultCount; i++) {
            newResults[i] = results[i];
        }

        delete[] results;

        results = newResults;
        capacity = newCapacity;
    }

    results[resultCount] = value;
    resultCount++;
}

long BTree::searchFirstRecursive(long nodePosition,
                                    const std::string& key) {
    if (nodePosition == NULL_CHILD) {
        return -1;
    }

    BTreeNode node = readNode(nodePosition);

    int i = 0;

    while (i < node.keyCount &&
        compareSearchKey(key, node.keys[i]) > 0) {
        i++;
    }

    if (i < node.keyCount &&
        compareSearchKey(key, node.keys[i]) == 0) {
        return node.recordPositions[i];
    }

    if (node.isLeaf) {
        return -1;
    }

    return searchFirstRecursive(node.children[i], key);
}

long BTree::searchFirst(const std::string& key) {
    return searchFirstRecursive(0, key);
}

void BTree::searchAllRecursive(long nodePosition,
                            const std::string& key,
                            long*& results,
                            int& resultCount,
                            int& capacity) {
    if (nodePosition == NULL_CHILD) {
        return;
    }

    BTreeNode node = readNode(nodePosition);

    if (node.isLeaf) {
        for (int i = 0; i < node.keyCount; i++) {
            if (compareSearchKey(key, node.keys[i]) == 0) {
                addResult(node.recordPositions[i], results, resultCount, capacity);
            }
        }

        return;
    }

    for (int i = 0; i < node.keyCount; i++) {
        searchAllRecursive(node.children[i], key, results, resultCount, capacity);

        if (compareSearchKey(key, node.keys[i]) == 0) {
            addResult(node.recordPositions[i], results, resultCount, capacity);
        }
    }

    searchAllRecursive(node.children[node.keyCount], key, results, resultCount, capacity);
}

long* BTree::searchAll(const std::string& key, int& resultCount) {
    int capacity = 10;
    resultCount = 0;

    long* results = new long[capacity];

    searchAllRecursive(0, key, results, resultCount, capacity);

    return results;
}

void BTree::dumpRecursive(long nodePosition,
                        long*& results,
                        int& resultCount,
                        int& capacity) {
    if (nodePosition == NULL_CHILD) {
        return;
    }

    BTreeNode node = readNode(nodePosition);

    if (node.isLeaf) {
        for (int i = 0; i < node.keyCount; i++) {
            addResult(node.recordPositions[i], results, resultCount, capacity);
        }

        return;
    }

    for (int i = 0; i < node.keyCount; i++) {
        dumpRecursive(node.children[i], results, resultCount, capacity);
        addResult(node.recordPositions[i], results, resultCount, capacity);
    }

    dumpRecursive(node.children[node.keyCount], results, resultCount, capacity);
}

long* BTree::dump(int& resultCount) {
    int capacity = 10;
    resultCount = 0;

    long* results = new long[capacity];

    dumpRecursive(0, results, resultCount, capacity);

    return results;
}

int BTree::getNodeCount() const {
    return nodeCount;
}

int BTree::getOrder() const {
    return order;
}

int BTree::getKeySize() const {
    return keySize;
}

std::string BTree::getFileName() const {
    return fileName;
}

int BTree::getNodeSize() const {
    return (2 * sizeof(int)) +
           (order * keySize) +
           (order * sizeof(long)) +
           ((order + 1) * sizeof(long));
}