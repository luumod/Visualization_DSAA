#ifndef LinkedListNodeItem_H_
#define LinkedListNodeItem_H_

#include <QObject>
#include <QGraphicsItem>
#include <QBrush>
#include <QFont>
#include <QPen>
#include <QColor>

#define ShowEffect
#define Interface

class LinkedListNodeLine;
class QGraphicsSimpleTextItem;
class QTimeLine;
class LinkedListView;
class LinkedListViewLog;
class LinkedListNodeItem : public QObject, public QGraphicsRectItem {
	Q_OBJECT

public:
	enum {
		PREPARING = 0b10000000,
		UNDEFINED = 0b00000000,
		ON_HOVER = 0b00000001,
		ON_LEFT_CLICK = 0b00000010,
		ON_RIGHT_CLICK = 0b00000100,
		ON_SELECTED = 0b00001000,
		ON_LINING = 0b00010000,
		ON_MENU = 0b00100000,
		ON_VISIT = 0b01000000,
		ON_ACCESS = 0b10000000
	};

	LinkedListNodeItem(QPointF _center, qreal _r, int nameID = 0, QGraphicsItem* parent = nullptr);

public ShowEffect:

	/**
	 * @brief Create an animation effect for the new node to be created.
	 */
	void showAnimation();

	/**
	 * @brief Start animation effect.
	 */
	void startAnimation();

	/**
	 * @brief Stop animation effect.
	 */
	void stopAnimation();

	/**
	 * @brief When clicked the node, show the clicked effect.
	 */
	void onClickEffect();

	/**
	 * @brief When release the node, show the release effect.
	 */
	void onReleaseEffect();

	/**
	 * @brief When hover but not clicked, show the hover in effect.
	 */
	void hoverInEffect();

	/**
	 * @brief When not hover, show the normal effect.
	 */
	void hoverOutEffect();

	/**
	 * @brief When remove one node, show the remove effect.
	 */
	void onPopEffect();


public Interface:

	/**
	 * @brief The Connections to connect the view, node-item and line.
	 */
	void estConnection(LinkedListView* view);

	void remove();
	void remove_front();
	void remove_back();
	void remove_head();

	/**
	 * @brief Move the scene coordinate of the one node to the position.
	 */
	void movePos(QPointF position);
	
	/**
	 * @brief Records the connection line start from the node.
	 */
	void addStartLine(LinkedListNodeLine* line); 

	/**
	 * @brief Records the connection line that end at the node.
	 */
	void addEndLine(LinkedListNodeLine* line); 

	/**
	 * @brief When remove one node, we ought to also remove its Subordinate connection line.
	 */
	void removeStartLine();

	/**
	 * @brief When remove one node, we ought to also remove its Subordinate connection line.
	 */
	void removeEndLine();
	QString Text() { return nameText; }
	qreal getRadius() { return radius; }
signals:
	void selected(QGraphicsItem* sel);
	void logAdded(LinkedListViewLog* log);

public slots:
	void freshBrushColor();
	void onMouseMove(QPointF position);
	void onLeftClick(QPointF position);
	void onRightClick(QPointF position);
	void onMouseRelease();

public:
	static QBrush regBrush;
	static QBrush textBrush;
	static unsigned int internalID;
private:
	int id;
	int state = UNDEFINED;

	LinkedListNodeLine* linesStartWith{ nullptr };
	LinkedListNodeLine* linesEndWith{ nullptr };


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
	enum {
		UNDEFINED = 0b00000000,
		ON_HOVER = 0b00000001,
		ON_LEFT_CLICK = 0b00000010,
		ON_RIGHT_CLICK = 0b00000100,
		ON_SELECTED = 0b00001000,
		ON_MENU = 0b00100000,
		ON_VISIT = 0b01000000
	};

	LinkedListNodeLine(LinkedListNodeItem* start, LinkedListNodeItem* end, QGraphicsItem* parent = nullptr);

	void moveStart(LinkedListNodeItem* start);
	void moveEnd(LinkedListNodeItem* end);

	void estConnection(LinkedListView* view);

	void hoverInEffect(); 
	void hoverOutEffect();

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
public slots:
	void freshBrushColor();
	void onMouseMove(QPointF position);
	void onLeftClick(QPointF position);
	void onRightClick(QPointF position);
	void onMouseRelease();
public:
	static QBrush lineBrush;
private:
	 int state = UNDEFINED;
	LinkedListNodeItem* startVex;
	LinkedListNodeItem* endVex;
	QGraphicsLineItem* line1 = nullptr;
	QGraphicsLineItem* line2 = nullptr;
	QGraphicsPathItem* arrow = nullptr;
	QGraphicsSimpleTextItem* textItem = nullptr;
	QGraphicsPathItem* arrowItem = nullptr;
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
	QPen defaultPen;
	QPen curPen;
	QFont textFont = QFont("Corbel", 12);
};

#endif // !LinkedListNodeItem_H_
