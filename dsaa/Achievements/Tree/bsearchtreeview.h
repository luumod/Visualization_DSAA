#ifndef BSEARCH_TREE_VIEW_H_
#define BSEARCH_TREE_VIEW_H_

#include "bsearchtree.h"
#include <QWidget>
#include <QVector>

class BSearchTreeView : public QWidget {
public:
    BSearchTreeView(QWidget* parent = nullptr);

    ~BSearchTreeView();

protected:
    void paintEvent(QPaintEvent*) override;

    void timerEvent(QTimerEvent* event) override;

private:
    BinarySearchTree bst;
    int timerId;

    void generateTree();

    void drawTree(QPainter& painter, int x, int y, TreeNode* node, int width);
};



#endif // !GREED_VIEW_H_
