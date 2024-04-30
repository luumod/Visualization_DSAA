#include "bsearchtree.h"
#include <iostream>

BSearchTree::BSearchTree() : root(nullptr) {}

void BSearchTree::insert(int value) {
    if (!root) {
        root = new TreeNode(value);
        return;
    }
    TreeNode* current = root;
    while (current) {
        if (value < current->value) {
            if (current->left)
                current = current->left;
            else {
                current->left = new TreeNode(value, current);
                updateDepth(current->left);
                break;
            }
        }
        else {
            if (current->right)
                current = current->right;
            else {
                current->right = new TreeNode(value, current);
                updateDepth(current->right);
                break;
            }
        }
    }
}
TreeNode* BSearchTree::getRoot() const {
    return root;
}

void BSearchTree::updateDepth(TreeNode* node) {
    while (node) {
        int leftDepth = node->left ? node->left->depth : 0;
        int rightDepth = node->right ? node->right->depth : 0;
        node->depth = std::max(leftDepth, rightDepth) + 1;
        node = node->parent;
    }
}

