#ifndef STAQUENODEITEM_H_
#define STAQUENODEITEM_H_

#include <QObject>
#include <QGraphicsItem>

class StaqueNodeItem : public QGraphicsRectItem {
public:
	using QGraphicsRectItem::QGraphicsRectItem;
	StaqueNodeItem(qreal w, qreal h, QGraphicsItem* item = nullptr);

protected:
	QRectF boundingRect() const override;

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr)override;
private:
	qreal m_w, m_h;
};

#endif // !STAQUENODEITEM_H_
