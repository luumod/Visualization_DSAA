#include "staquenodeitem.h"
#include <QPainter>

StaqueNodeItem::StaqueNodeItem(qreal w, qreal h, QGraphicsItem* item)
    : m_w(w), m_h(h), QGraphicsRectItem(item) {

    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

QRectF StaqueNodeItem::boundingRect() const {
    qreal width = 1;
    // °üÎ§¾ØÐÎ
    return QRectF(-m_w / 2 - width / 2, -m_h / 2 - width / 2, m_w + width, m_h + width);
}

void StaqueNodeItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->save();
    painter->setPen(pen());
    painter->setBrush(brush());

    QRectF rect(-m_w / 2, -m_h / 2, m_w, m_h);
    painter->drawRect(rect);

    painter->restore();
}
