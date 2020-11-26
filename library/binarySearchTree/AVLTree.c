#include "AVLTree.h"
#include "../commonUtils/numericOperations.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct AVLTreeNode {
    long long value;
    int height;
    struct AVLTreeNode* leftChild;
    struct AVLTreeNode* rightChild;
} AVLTreeNode;

struct AVLTree {
    struct AVLTreeNode* root;
};

enum Direction { left,
    right,
    none };

int getNodeHeight(AVLTreeNode* node)
{
    return node == NULL ? 0 : node->height;
}

int getNodeBalanceFactor(AVLTreeNode* node)
{
    return getNodeHeight(node->rightChild) - getNodeHeight(node->leftChild);
}

bool isLeaf(AVLTreeNode* node)
{
    return node->leftChild == NULL && node->rightChild == NULL;
}

void updateNodeHeight(AVLTreeNode* node)
{
    int heightLeft = 0;
    int heightRight = 0;

    if (node->leftChild != NULL)
        heightLeft = getNodeHeight(node->leftChild);
    if (node->rightChild != NULL)
        heightRight = getNodeHeight(node->rightChild);

    node->height = max(heightLeft, heightRight) + 1;
}

AVLTreeNode* rotateRight(AVLTreeNode* root)
{
    AVLTreeNode* pivot = root->leftChild;
    root->leftChild = pivot->rightChild;
    pivot->rightChild = root;
    updateNodeHeight(root);
    updateNodeHeight(pivot);
    return pivot;
}

AVLTreeNode* rotateLeft(AVLTreeNode* root)
{
    AVLTreeNode* pivot = root->rightChild;
    root->rightChild = pivot->leftChild;
    pivot->leftChild = root;
    updateNodeHeight(root);
    updateNodeHeight(pivot);
    return pivot;
}

AVLTreeNode* balanceNode(AVLTreeNode* root)
{
    if (getNodeBalanceFactor(root) == 2) {
        if (getNodeBalanceFactor(root->rightChild) < 0)
            root->rightChild = rotateRight(root->rightChild);
        return rotateLeft(root);
    }

    if (getNodeBalanceFactor(root) == -2) {
        if (getNodeBalanceFactor(root->leftChild) > 0)
            root->leftChild = rotateLeft(root->leftChild);
        return rotateRight(root);
    }

    return root;
}

AVLTree* createTree()
{
    AVLTree* newTree = (AVLTree*)malloc(sizeof(AVLTree));
    newTree->root = NULL;
    return newTree;
}

AVLTreeNode* createNode(long long value)
{
    AVLTreeNode* node = (AVLTreeNode*)malloc(sizeof(AVLTreeNode));
    node->rightChild = NULL;
    node->leftChild = NULL;
    node->value = value;
    node->height = 0;
    return node;
}

void removeTreeRecursive(AVLTreeNode* node)
{
    if (node == NULL)
        return;

    removeTreeRecursive(node->leftChild);
    removeTreeRecursive(node->rightChild);
    free(node);
}

void removeTree(AVLTree* tree)
{
    removeTreeRecursive(tree->root);
    free(tree);
}

bool existsRecursive(AVLTreeNode* node, long long value)
{
    if (node->value == value)
        return true;

    if (value < node->value && node->leftChild != NULL)
        return existsRecursive(node->leftChild, value);

    if (value > node->value && node->rightChild != NULL)
        return existsRecursive(node->rightChild, value);

    return false;
}

bool isEmpty(AVLTree* tree)
{
    return (tree->root == NULL);
}

bool isExists(AVLTree* tree, long long value)
{
    if (isEmpty(tree))
        return false;

    return existsRecursive(tree->root, value);
}

bool addValueRecursive(AVLTreeNode* node, long long value)
{
    if (node->value == value)
        return false;

    if (value < node->value) {
        if (node->leftChild == NULL) {
            node->leftChild = createNode(value);
            node->leftChild->height = 1;
            return true;
        } else {
            return addValueRecursive(node->leftChild, value);
        }
    }

    if (value > node->value) {
        if (node->rightChild == NULL) {
            node->rightChild = createNode(value);
            node->rightChild->height = 1;
            return true;
        } else {
            return addValueRecursive(node->rightChild, value);
        }
    }
}

bool addValue(AVLTree* tree, long long value)
{
    if (isEmpty(tree)) {
        tree->root = createNode(value);
        return true;
    }

    return addValueRecursive(tree->root, value);
}

bool changeParent(AVLTree* tree, AVLTreeNode* parent, AVLTreeNode* newNode, enum Direction direction)
{
    if (direction == left)
        parent->leftChild = newNode;

    if (direction == right)
        parent->rightChild = newNode;

    if (direction == none)
        tree->root = newNode;

    return true;
}

bool removeRecursive(AVLTree* tree, AVLTreeNode* node, long long value, AVLTreeNode* parent, enum Direction direction)
{
    if (node->value == value) {
        if (isLeaf(node)) {
            free(node);
            changeParent(tree, parent, NULL, direction);
            return true;
        }

        if (node->leftChild == NULL && node->rightChild != NULL) {
            changeParent(tree, parent, node->rightChild, direction);
            free(node);
            return true;
        }

        if (node->leftChild != NULL && node->rightChild == NULL) {
            changeParent(tree, parent, node->leftChild, direction);
            free(node);
            return true;
        }

        if (node->leftChild != NULL && node->rightChild != NULL) {
            AVLTreeNode* minimumRightBranchNode = node->rightChild;
            AVLTreeNode* minimumRightBranchNodeParent = NULL;

            while (minimumRightBranchNode->leftChild != NULL) {
                minimumRightBranchNodeParent = minimumRightBranchNode;
                minimumRightBranchNode = minimumRightBranchNode->leftChild;
            }

            changeParent(tree, minimumRightBranchNode, node->leftChild, left);
            if (minimumRightBranchNodeParent != NULL) { // Если минимальный элемент правой ветки - не правый потомок удаляемого элемента.
                changeParent(tree, minimumRightBranchNode, node->rightChild, right);
                minimumRightBranchNodeParent->leftChild = NULL;
            }

            changeParent(tree, parent, minimumRightBranchNode, direction);

            free(node);
            return true;
        }
    }

    if (node->value > value && node->leftChild != NULL)
        return removeRecursive(tree, node->leftChild, value, node, left);

    if (node->value < value && node->rightChild != NULL)
        return removeRecursive(tree, node->rightChild, value, node, right);

    return false;
}

bool removeValue(AVLTree* tree, long long value)
{
    if (isEmpty(tree))
        return false;

    return removeRecursive(tree, tree->root, value, NULL, none);
}

AVLTreeNode* getBalancedTreeRecursive(AVLTreeNode* node)
{
    if (isLeaf(node)) {
        updateNodeHeight(node);
        return node;
    }

    if (node->rightChild != NULL)
        node->rightChild = getBalancedTreeRecursive(node->rightChild);
    else if (node->leftChild != NULL)
        node->leftChild = getBalancedTreeRecursive(node->leftChild);

    updateNodeHeight(node);

    return balanceNode(node);
}

AVLTreeNode* getBalancedTree(AVLTree* tree)
{
    if (isEmpty(tree))
        return NULL;

    return getBalancedTreeRecursive(tree->root);
}

bool removeValueFromAVL(AVLTree* tree, long long value)
{
    if (isEmpty(tree))
        return false;

    bool isRemoved = removeValue(tree, value);
    tree->root = getBalancedTree(tree);

    return isRemoved;
}

bool addValueInAVL(AVLTree* tree, long long value)
{
    if (isEmpty(tree)) {
        tree->root = createNode(value);
        tree->root->height = 1;
        return true;
    }

    bool isAdded = addValue(tree, value);
    tree->root = getBalancedTree(tree);

    return isAdded;
}

void printTreeInAscendingOrderRecursive(AVLTreeNode* node)
{
    if (node == NULL)
        return;

    printTreeInAscendingOrderRecursive(node->leftChild);
    printf("%lld ", node->value);
    printTreeInAscendingOrderRecursive(node->rightChild);
}

void printTreeInAscendingOrder(AVLTree* tree)
{
    if (tree != NULL)
        printTreeInAscendingOrderRecursive(tree->root);
    printf("\n");
}

void printTreeInDescendingOrderRecursive(AVLTreeNode* node)
{
    if (node == NULL)
        return;

    printTreeInDescendingOrderRecursive(node->rightChild);
    printf("%lld ", node->value);
    printTreeInDescendingOrderRecursive(node->leftChild);
}

void printTreeInDescendingOrder(AVLTree* tree)
{
    if (tree != NULL)
        printTreeInDescendingOrderRecursive(tree->root);
    printf("\n");
}

void printTreeInDirectOrderRecursive(AVLTreeNode* node, enum Direction direction)
{
    if (node == NULL) {
        printf("null");
        if (direction != right)
            printf(" ");
        return;
    }

    printf("(");
    printf("%lld ", node->value);
    printTreeInDirectOrderRecursive(node->leftChild, left);
    printTreeInDirectOrderRecursive(node->rightChild, right);
    printf(")");
    if (direction != right)
        printf(" ");
}

void printTreeInDirectOrder(AVLTree* tree)
{
    if (tree != NULL)
        printTreeInDirectOrderRecursive(tree->root, none);
    printf("\n");
}
