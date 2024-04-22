#ifndef GRAPH_VIEW_H
#define GRAPH_VIEW_H

#include <QGraphicsView>
#include "stack.h"
#include "queue.h"

class QGraphicsScene;
class StaqueNodeItem;
class StaqueView : public QGraphicsView {
	Q_OBJECT

private:
	enum mouseStates {
		NORMAL = 0b00000000,
		ON_HOVER = 0b00010000,
		ON_SELECTED = 0b00100000,
		ON_MOVING = 0b01000000
	};
	QGraphicsScene* scene;
	int type;
	int nodeID = 0;
	int mouseState = NORMAL;
	bool onRightPress = false;
	bool onMiddlePress = false;
	QPointF lastPos;

	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void wheelEvent(QWheelEvent* event);
	void resizeEvent(QResizeEvent* event) { this->setSceneRect(this->rect()); }
	void changeCursor();
public:
	int vexNum = 0;
	QVector<StaqueNodeItem*> nodes;
	bool hasVisitedItem = false;
	StaqueView(QWidget* parent = nullptr);
signals:
	void mouseMoved(QPointF position);
	void mouseLeftClicked(QPointF position);
	void mouseRightClicked(QPointF position);
	void mouseReleased();
};
#endif // GRAPH_VIEW_H
