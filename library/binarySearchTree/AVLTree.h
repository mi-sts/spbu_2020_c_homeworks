#ifndef SPBU_2020_C_HOMEWORKS_BST_H
#define SPBU_2020_C_HOMEWORKS_BST_H

#include <stdbool.h>

typedef struct AVLTree AVLTree;

AVLTree* createTree();

void removeTree(AVLTree* tree);

bool isExists(AVLTree* tree, long long value);

bool addValueInAVL(AVLTree* tree, long long value);

bool removeValueFromAVL(AVLTree* tree, long long value);

void printTreeInAscendingOrder(AVLTree* tree);

void printTreeInDescendingOrder(AVLTree* tree);

void printTreeInDirectOrder(AVLTree* tree);

#endif
