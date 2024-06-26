#ifndef STAQUENODEITEM_H_
#define STAQUENODEITEM_H_

#include <QObject>
#include <QGraphicsItem>
#include <QBrush>
#include <QFont>
#include <QPen>
#include <QColor>

class StaqueNodeLine;
class QGraphicsSimpleTextItem;
class QTimeLine;
class StaqueView;
class StaqueViewLog;
class StaqueNodeItem : public QObject, public QGraphicsRectItem {
	Q_OBJECT

public:
	using QGraphicsRectItem::QGraphicsRectItem;
	StaqueNodeItem(QPointF _center, qreal _r, int nameID = 0, QGraphicsItem* parent = nullptr);

	int value() { return _value; }
	qreal getRadius() { return radius; }
	void setTextSize(int value);
	QString Text() { return nameText; }

	void showAnimation();
	void startAnimation();
	void stopAnimation();

	void onClickEffect();
	void onReleaseEffect();

	void onPopEffect();

	void estConnection(StaqueView* view);

	void remove();
signals:
	void selected(QGraphicsItem* sel);
	void logAdded(StaqueViewLog* log);

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

#endif // !STAQUENODEITEM_H_
