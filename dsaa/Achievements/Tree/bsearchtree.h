#ifndef BSEARCH_TREE_H_
#define BSEARCH_TREE_H_

#include <QObject>

class TreeNode {
public:
    TreeNode(int value, TreeNode* parent = nullptr)
        : value(value), parent(parent), left(nullptr), right(nullptr), depth(1) {}

    int value;
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;
    int depth;
};

class BSearchTree {
public:
    BSearchTree();

    void insert(int value);

    TreeNode* getRoot()const;

private:
    TreeNode* root;

    void updateDepth(TreeNode* node);
};

#endif // !BSEARCH_TREE_H_
