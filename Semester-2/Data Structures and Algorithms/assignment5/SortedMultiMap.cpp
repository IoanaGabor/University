#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>

using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {
    //theta(treeCapacity)
    relation = r;
    treeCapacity = 2;
    treeSize = 0;
    smmSize = 0;
    nodes = new BTSNode[treeCapacity];
    root = -1;
    firstFree = 0;
    nextFree = new int[treeCapacity];
    for (int i = 0; i < treeCapacity; i++) {
        nextFree[i] = i + 1;
        nodes[i].key = NULL_TVALUE;
    }
    nextFree[treeCapacity - 1] = -1;
}

void SortedMultiMap::add(TKey c, TValue v) {
    // best case: theta(1), average case: theta(height), worst case: theta(treeSize), total: O(treeSize)
    int currentPosition = root;
    if (currentPosition == -1) {
        root = createNode();
        currentPosition = root;
    } else {
        while (true) {
            if (nodes[currentPosition].key == c) {
                break;
            }
            if (relation(c, nodes[currentPosition].key)) {
                if (nodes[currentPosition].left == -1) {
                    int created = createNode();
                    nodes[currentPosition].left = created;
                    currentPosition = nodes[currentPosition].left;
                    break;
                }
                currentPosition = nodes[currentPosition].left;
            } else {
                if (nodes[currentPosition].right == -1) {
                    int created = createNode();
                    nodes[currentPosition].right = created;
                    currentPosition = nodes[currentPosition].right;
                    break;
                }
                currentPosition = nodes[currentPosition].right;
            }
        }
    }
    if (nodes[currentPosition].valuesCapacity == nodes[currentPosition].valuesSize) {
        resizeNode(currentPosition);
    }
    nodes[currentPosition].values[nodes[currentPosition].valuesSize++] = v;
    nodes[currentPosition].key = c;
    smmSize++;
}

int SortedMultiMap::createNode() {
    ///best case: theta(1), worst case: theta(treeSize), total: O(treeSize)
    if (treeCapacity == treeSize) {
        resizeBST();
    }
    int position = firstFree;
    firstFree = nextFree[firstFree];
    nodes[position].right = nodes[position].left = -1;
    treeSize++;
    nodes[position].valuesCapacity = 4;
    nodes[position].valuesSize = 0;
    nodes[position].values = new TValue[4];
    return position;
}

void SortedMultiMap::removeNode(int position, int parentPosition) {
    // best case: theta(1), average case: theta(height), worst case: theta(treeSize), total: O(treeSize)
    int nbOfDesc = (nodes[position].left != -1) + (nodes[position].right != -1);
    if (nbOfDesc == 0) {
        removeNodeWithNoDescendants(position, parentPosition);
    } else if (nbOfDesc == 1) {
        removeNodeWithOneDescendant(position, parentPosition);
    } else if (nbOfDesc == 2) {
        removeNodeWithTwoDescendants(position, parentPosition);
    }
}

void SortedMultiMap::resizeNode(int position) {
    TValue *new_values = new TValue[nodes[position].valuesCapacity * 2];
    for (int i = 0; i < nodes[position].valuesCapacity; i++) {
        new_values[i] = nodes[position].values[i];
    }
    nodes[position].valuesCapacity *= 2;
    delete[] nodes[position].values;
    nodes[position].values = new_values;
}

void SortedMultiMap::resizeBST() {
    ///theta(treeSize)
    auto *new_nodes = new BTSNode[treeCapacity * 2];
    int *newNextFree = new int[treeCapacity * 2];
    for (int i = 0; i < treeCapacity; i++) {
        new_nodes[i] = nodes[i];
    }
    for (int i = 0; i < treeCapacity; i++) {
        newNextFree[i] = nextFree[i];
    }
    for (int i = treeCapacity; i < 2 * treeCapacity; i++) {
        newNextFree[i] = i + 1;
        new_nodes[i].key = NULL_TVALUE;
    }
    newNextFree[2 * treeCapacity - 1] = -1;
    firstFree = treeCapacity;
    treeCapacity *= 2;
    delete[] nodes;
    delete[] nextFree;
    nodes = new_nodes;
    nextFree = newNextFree;
}

vector<TValue> SortedMultiMap::search(TKey c) const {
    // best case: theta(1), average case: theta(height), worst case: theta(treeSize), total: O(treeSize)
    vector<TValue> foundValues = vector<TValue>();
    int currentNode = root;
    bool found = false;
    while (currentNode != -1 && !found) {
        if (nodes[currentNode].key == c) {
            found = true;
        } else if (relation(c, nodes[currentNode].key)) {
            currentNode = nodes[currentNode].left;
        } else {
            currentNode = nodes[currentNode].right;
        }
    }
    if (found) {
        for (int i = 0; i < nodes[currentNode].valuesSize; i++) {
            foundValues.push_back(nodes[currentNode].values[i]);
        }
    }
    return foundValues;
}

void SortedMultiMap::removeNodeWithNoDescendants(int position, int parentPosition) {
    //theta(1)
    if (parentPosition == -1) {
        root = -1;
    } else {
        if (nodes[parentPosition].left == position) {
            nodes[parentPosition].left = -1;
        } else {
            nodes[parentPosition].right = -1;
        }
    }
    nodes[position].valuesCapacity = nodes[position].valuesSize = 0;
    delete[] nodes[position].values;
    nodes[position].key = NULL_TVALUE;
    nextFree[position] = firstFree;
    firstFree = position;
    nodes[position].left = nodes[position].right = -1;
    if (position == root) {
        root = -1;
    }
    treeSize--;
}


void SortedMultiMap::removeNodeWithOneDescendant(int position, int parentPosition) {
    // theta(1)
    int descendantPosition = -1;
    if (nodes[position].left != -1) {
        descendantPosition = nodes[position].left;
    } else {
        descendantPosition = nodes[position].right;
    }
    if (parentPosition == -1) {
        root = descendantPosition;
    } else {
        if (nodes[parentPosition].left == position) {
            nodes[parentPosition].left = descendantPosition;
        } else {
            nodes[parentPosition].right = descendantPosition;
        }
    }
    nodes[position].valuesCapacity = nodes[position].valuesSize = 0;
    delete[] nodes[position].values;
    nodes[position].key = NULL_TVALUE;
    nextFree[position] = firstFree;
    firstFree = position;
    nodes[position].left = nodes[position].right = -1;
    if (position == root) {
        root = -1;
    }
    treeSize--;
}

void SortedMultiMap::removeNodeWithTwoDescendants(int position, int parentPosition) {
    // best case: theta(1), average case: theta(height), worst case: theta(treeSize), total: O(treeSize)
    int descendantPosition = nodes[position].left;
    int prev = position;
    while (nodes[descendantPosition].right != -1) {
        prev = descendantPosition;
        descendantPosition = nodes[descendantPosition].right;
    }
    nodes[position].key = nodes[descendantPosition].key;
    nodes[position].values = nodes[descendantPosition].values;
    nodes[position].valuesSize = nodes[descendantPosition].valuesSize;
    nodes[position].valuesCapacity = nodes[descendantPosition].valuesCapacity;
    removeNode(descendantPosition, prev);
}

bool SortedMultiMap::remove(TKey c, TValue v) {
    // best case: theta(1), average case: theta(height), worst case: theta(treeSize), total: O(treeSize)
    int currentNode = root;
    bool foundKey = false;
    int parent = -1;
    while (currentNode != -1 && !foundKey) {
        if (nodes[currentNode].key == c) {
            foundKey = true;
        } else if (relation(c, nodes[currentNode].key)) {
            parent = currentNode;
            currentNode = nodes[currentNode].left;
        } else {
            parent = currentNode;
            currentNode = nodes[currentNode].right;
        }
    }
    if (foundKey) {
        int foundPos = -1;
        for (int i = 0; i < nodes[currentNode].valuesSize; i++) {
            if (nodes[currentNode].values[i] == v) {
                foundPos = i;
                break;
            }
        }
        if (foundPos != -1) {
            for (int i = foundPos; i < nodes[currentNode].valuesSize; i++) {
                nodes[currentNode].values[i] = nodes[currentNode].values[i + 1];
            }
            nodes[currentNode].valuesSize--;

            if (nodes[currentNode].valuesSize == 0) {
                removeNode(currentNode, parent);
            }
            smmSize--;
            return true;
        } else {
            return false;
        }
    }
    return false;
}


int SortedMultiMap::size() const {
    //theta(1)
    return smmSize;
}

bool SortedMultiMap::isEmpty() const {
    //theta(1)
    return smmSize == 0;
}

SMMIterator SortedMultiMap::iterator() const {
    return SMMIterator(*this);
}

void SortedMultiMap::dealocateRecursively(int node) {
    //theta(treeSize)
    if (node == -1) {
        return;
    }
    dealocateRecursively(nodes[node].left);
    dealocateRecursively(nodes[node].right);
    delete[] nodes[node].values;
}

SortedMultiMap::~SortedMultiMap() {
    //theta(treeSize)
    dealocateRecursively(root);
    delete[] nodes;
    delete[] nextFree;
}

vector<TKey> SortedMultiMap::keySet() const {
    ///theta(treeSize)
    vector<TKey> allKeys = vector<TKey>();
    int *stack;
    stack = new int[this->treeSize];
    int top = 0;
    int currentNode = this->root;
    while (currentNode != -1) {
        stack[top] = currentNode;
        top++;
        currentNode = nodes[currentNode].left;
    }
    while (top) {
        top--;
        currentNode = stack[top];
        allKeys.push_back(nodes[currentNode].key);
        currentNode = nodes[currentNode].right;
        while (currentNode != -1) {
            stack[top++] = currentNode;
            currentNode = nodes[currentNode].left;
        }
    }
    delete[] stack;
    return allKeys;
}
