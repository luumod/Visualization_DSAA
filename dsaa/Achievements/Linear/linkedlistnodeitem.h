#ifndef LinkedListNodeItem_H_
#define LinkedListNodeItem_H_

#include <QObject>
#include <QGraphicsItem>
#include <QBrush>
#include <QFont>
#include <QPen>
#include <QColor>

class LinkedListNodeLine;
class QGraphicsSimpleTextItem;
class QTimeLine;
class LinkedListView;
class LinkedListViewLog;
class LinkedListNodeItem : public QObject, public QGraphicsRectItem {
	Q_OBJECT

public:
	using QGraphicsRectItem::QGraphicsRectItem;
	LinkedListNodeItem(QPointF _center, qreal _r, int nameID = 0, QGraphicsItem* parent = nullptr);

	void move(QPointF position);

	qreal getRadius() { return radius; }
	QString Text() { return nameText; }

	void showAnimation();
	void startAnimation();
	void stopAnimation();

	void onClickEffect();
	void onReleaseEffect();

	void onPopEffect();

	void estConnection(LinkedListView* view);

	void remove();
	//void addStartLine(LinkedListNodeLine* line) { linesStartWith.push_back(line); }
	//void addEndLine(LinkedListNodeLine* line) { linesEndWith.push_back(line); }
	//void removeStartLine(LinkedListNodeLine* line) { linesStartWith.remove(linesStartWith.indexOf(line)); }
	//void removeEndLine(LinkedListNodeLine* line) { linesEndWith.remove(linesEndWith.indexOf(line)); }
signals:
	void selected(QGraphicsItem* sel);
	void logAdded(LinkedListViewLog* log);

public slots:
	void onMouseMove(QPointF position);
	void onLeftClick(QPointF position);
	void onRightClick(QPointF position);
	void onMouseRelease();

private:
	int id;

	static unsigned int internalID;
	QBrush regBrush = QBrush(QColor(58, 143, 192));
	QBrush selBrush = QBrush(QColor(208, 90, 110));
	QBrush visitedBrush = QBrush(QColor(0, 137, 108));
	QBrush accessBrush = QBrush(QColor(152, 109, 178));

	QString nameText = "";
	QFont nameFont = QFont("Corbel", 13, QFont::Normal, true);
	QString hintText = "";
	QFont hintFont = QFont("Corbel", 12);

	qreal radius;
	qreal m_w, m_h;
	QPointF center;
	QTimeLine* curAnimation = nullptr;

	QGraphicsSimpleTextItem* tag = nullptr;
	QGraphicsSimpleTextItem* nameTag = nullptr;
};

class LinkedListNodeLine : public QObject, public QGraphicsLineItem
{
	Q_OBJECT

public:
	LinkedListNodeLine(LinkedListNodeItem* start, LinkedListNodeItem* end, QGraphicsItem* parent = nullptr);

	void moveStart(LinkedListNodeItem* start);
	void moveEnd(LinkedListNodeItem* end);

	void remove();
	void drawText();
	void drawLine();
	void delArrow();
	void drawArrow();
	void refrshLine();
	void setLengthRate(qreal r = 1);
	LinkedListNodeItem* stVex() { return startVex; }
	LinkedListNodeItem* edVex() { return endVex; }
signals:
	void logAdded(LinkedListViewLog* log);
private:
	LinkedListNodeItem* startVex;
	LinkedListNodeItem* endVex;
	QGraphicsLineItem* line1 = nullptr;
	QGraphicsLineItem* line2 = nullptr;
	QGraphicsPathItem* arrow = nullptr;
	QGraphicsSimpleTextItem* textItem = nullptr;
	QString text = "";

	bool hasDirection;
	qreal angle = 0;
	QPointF center;
	QPointF sP, eP, dP;

	/* detail of the line */
	qreal lineWidth = 3;
	qreal arrowLength = 20;
	Qt::PenStyle lineStyle = Qt::SolidLine;
	Qt::PenCapStyle capStyle = Qt::RoundCap;
	QColor defaultColor = QColor(125, 185, 222);
	QColor hoverColor = QColor(0, 98, 132);
	QColor selColor = QColor(208, 90, 110);
	QColor visitColor = QColor(0, 137, 108);
	QColor accessColor = QColor(178, 143, 206);
	QPen defaultPen;
	QPen curPen;
	QFont textFont = QFont("Corbel", 12);
	QColor textColor = QColor(0, 0, 0);
};

#endif // !LinkedListNodeItem_H_
