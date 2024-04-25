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

	void move(QPointF position);

	qreal getRadius() { return radius; }
	QString Text() { return nameText; }

	void showAnimation();
	void startAnimation();
	void stopAnimation();
	void estConnection(StaqueView* view);

	void addStartLine(StaqueNodeLine* line) { linesStartWith.push_back(line); }
	void addEndLine(StaqueNodeLine* line) { linesEndWith.push_back(line); }

signals:
	void logAdded(StaqueViewLog* log);

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

	QVector<StaqueNodeLine*> linesStartWith;
	QVector<StaqueNodeLine*> linesEndWith;

};

class StaqueNodeLine : public QObject, public QGraphicsLineItem
{
	Q_OBJECT

public:
	StaqueNodeLine(StaqueNodeItem* start, StaqueNodeItem* end, QGraphicsItem* parent = nullptr);

	void moveStart(StaqueNodeItem* start);
	void moveEnd(StaqueNodeItem* end);

	void drawText();
	void drawLine();
	void delArrow();
	void drawArrow();
	void refrshLine();
	void setLengthRate(qreal r = 1);
	StaqueNodeItem* stVex() { return startNode; }
	StaqueNodeItem* edVex() { return endNode; }
signals:
	void logAdded(StaqueViewLog* log);
private:
	StaqueNodeItem* startNode;
	StaqueNodeItem* endNode;
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

#endif // !STAQUENODEITEM_H_
