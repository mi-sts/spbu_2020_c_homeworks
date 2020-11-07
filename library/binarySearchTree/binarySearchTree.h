#ifndef SPBU_2020_C_HOMEWORKS_BST_H
#define SPBU_2020_C_HOMEWORKS_BST_H

#include <stdbool.h>

typedef struct BinarySearchTree BinarySearchTree;

BinarySearchTree* createTree();

void removeTree(BinarySearchTree* tree);

bool isExists(BinarySearchTree* tree, long long value);

bool addValue(BinarySearchTree* tree, long long value);

bool removeValue(BinarySearchTree* tree, long long value);

void printTreeInAscendingOrder(BinarySearchTree* tree);

void printTreeInDescendingOrder(BinarySearchTree* tree);

void printTreeInDirectOrder(BinarySearchTree* tree);

#endif //SPBU_2020_C_HOMEWORKS_BST_H

