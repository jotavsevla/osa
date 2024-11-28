//
// Created by João on 27/11/24.
//

#ifndef LAB04_OSA_BSTREENODE_H
#define LAB04_OSA_BSTREENODE_H
#include "IndexEntry.h"

class BSTreeNode {
public:
    IndexEntry data;
    BSTreeNode* left;
    BSTreeNode* right;

    BSTreeNode(IndexEntry entry) : data(entry), left(nullptr), right(nullptr) {}
};


#endif //LAB04_OSA_BSTREENODE_H
