#include "staqueview.h"
#include "logger.h"
#include "common.h"
#include <QPaintEvent>
#include <QScrollArea>
#include <QPainter>
#include <QVBoxLayout>

StaqueView::StaqueView(QWidget* parent)
    :QWidget(parent)
{
    setMinimumSize(500, 500);  // 设置LinkedListView的最小尺寸
}

StaqueView::~StaqueView()
{
}

void StaqueView::updateColors(const QString& node, const QString& arrow, const QString& text) {
    // TODO... 
    update();
}

void StaqueView::updateSettings(int nodeWidth, int nodeHeight, int arrowSize, int textSpace, int maxNodesPerRow, int row_spacing) {
    // TODO...
    
    update();
}

void StaqueView::resetSettings() {
    // TODO...

    update();
}

void StaqueView::paintEvent(QPaintEvent* event) {
    event->accept();
    if (!painter) {
        painter = new QPainter(this);
    }
    painter->begin(this);

    Logger::debug("stack.draw(painter,20,20);");
    stack.draw(painter, (width() / 2 - stack.node_width) / 2, 20);
    queue.draw(painter, (width() / 2 + (width() / 2 - stack.node_width) / 2), 20);

    painter->end();
    //setMinimumHeight(std::min(stack.getHeight()));  // 根据节点数量动态设置LinkedListView的高度
}