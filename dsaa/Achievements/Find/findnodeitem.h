#ifndef FIND_NODEITEM_H_
#define FIND_NODEITEM_H_

#include <QObject>
#include <QGraphicsItem>
#include <QBrush>
#include <QFont>
#include <QPen>
#include <QColor>

class QGraphicsPolygonItem;
class QGraphicsSimpleTextItem;
class QTimeLine;
class FindView;
class FindViewLog;
class FindNodeItem : public QObject, public QGraphicsRectItem {
	Q_OBJECT

public:
	using QGraphicsRectItem::QGraphicsRectItem;
	FindNodeItem(QPointF _center, qreal _r, int nameID = 0, QGraphicsItem* parent = nullptr);

	void moveTo(QPointF dst_center);

	int value() { return _value; }
	qreal getRadius() { return radius; }
	void setTextSize(int value);
	QString Text() { return nameText; }

	void showAnimation();
	void startAnimation();
	void stopAnimation();

	void onClickEffect();
	void onReleaseEffect();
	void onSearchEffect();
	void onPopEffect();

	void estConnection(FindView* view);

	void remove();
signals:
	void selected(QGraphicsItem* sel);
	void logAdded(FindViewLog* log);

public slots:
	void onMouseMove(QPointF position);
	void onLeftClick(QPointF position);
	void onRightClick(QPointF position);
	void onMouseRelease(QPointF position);

private:
	int _value;

	QBrush regBrush = QBrush(QColor(58, 143, 192));
	QBrush selBrush = QBrush(QColor(208, 90, 110));
	QBrush visitedBrush = QBrush(QColor(0, 137, 108));
	QBrush accessBrush = QBrush(QColor(152, 109, 178));

	QString nameText = "";
	static QFont nameFont;
	QString hintText = "";
	QFont hintFont = QFont("Corbel", 12);

	qreal radius;
	qreal m_w, m_h;
	QPointF center;
	QTimeLine* curAnimation = nullptr;

	QGraphicsSimpleTextItem* tag = nullptr;
	QGraphicsSimpleTextItem* nameTag = nullptr;
};

#endif // !FIND_NODEITEM_H_
