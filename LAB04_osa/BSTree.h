// BSTree.h
#ifndef BSTREE_H
#define BSTREE_H

#include "IndexEntry.h"

class BSTreeNode {
public:
    IndexEntry data;
    BSTreeNode* left;
    BSTreeNode* right;

    BSTreeNode(IndexEntry entry) : data(entry), left(nullptr), right(nullptr) {}
};

#endif