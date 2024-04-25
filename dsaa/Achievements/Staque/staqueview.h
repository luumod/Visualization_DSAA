#ifndef GRAPH_VIEW_H
#define GRAPH_VIEW_H

#include <QGraphicsView>
#include "stack.h"
#include "queue.h"

class QGraphicsScene;
class StaqueNodeItem;
class StaqueNodeLine;
class StaqueViewLog;
class StaqueView : public QGraphicsView {
	Q_OBJECT

private:
	enum mouseStates {
		NORMAL = 0b00000000,
		ON_HOVER = 0b00010000,
		ON_SELECTED = 0b00100000,
		ON_MOVING = 0b01000000
	};
	QGraphicsScene* _scene;

	int vexID = 0;

	int type;
	int mouseState = NORMAL;
	bool onRightPress = false;
	QPointF lastPos;

	QVector<StaqueNodeItem*> vexes;
	QVector<StaqueNodeLine*> lines;

	QGraphicsItem* selItem = nullptr;
	StaqueNodeItem* strtVex = nullptr;


	StaqueNodeItem* addNode(QPointF center, int value = -1, qreal radius = 50.0);
	void addLine(StaqueNodeItem* start, StaqueNodeItem* end);
	void startLine(StaqueNodeItem* startVex);
	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void wheelEvent(QWheelEvent* event);
	void resizeEvent(QResizeEvent* event) { this->setSceneRect(this->rect()); }
public:
	qreal zValue = -1;
	int vexNum = 0;
	int arcNum = 0;
	QVector<StaqueNodeItem*> nodes;
	Stack stack;
	Queue queue;
	bool hasVisitedItem = false;

	void push_back(int value);
	StaqueView(QWidget* parent = nullptr);

signals:
	void logAdded(StaqueViewLog* log);

	void mouseMoved(QPointF position);
	void mouseLeftClicked(QPointF position);
	void mouseRightClicked(QPointF position);
	void mouseReleased();
public slots:
	void addLog(StaqueViewLog* log) { emit logAdded(log); }
};
#endif // GRAPH_VIEW_H
