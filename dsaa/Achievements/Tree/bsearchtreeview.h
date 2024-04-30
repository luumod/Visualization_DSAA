#ifndef GRAPH_VIEW_H
#define GRAPH_VIEW_H

#include "bsearchtree.h"
#include <QGraphicsView>

class QGraphicsScene;
class BSearchTreeNodeItem;
class BSearchTreeNodeLine;
class StaqueViewLog;
class BSearchTreeView : public QGraphicsView {
	Q_OBJECT

private:
	enum mouseStates {
		NORMAL = 0b00000000,
		ON_HOVER = 0b00010000,
		ON_SELECTED = 0b00100000,
		ON_MOVING = 0b01000000
	};
	enum Dir {
		LEFT,
		RIGHT
	};
	QGraphicsScene* _scene;

	int vexID = 0;

	int type;
	int mouseState = NORMAL;
	bool onRightPress = false;
	QPointF lastPos;

	QVector<BSearchTreeNodeItem*> vexes;
	QVector<BSearchTreeNodeLine*> lines;

	QGraphicsItem* selItem = nullptr;
	BSearchTreeNodeItem* strtVex = nullptr;


	BSearchTreeNodeItem* addNode(QPointF center, int value = -1, qreal radius = 50.0, BSearchTreeNodeItem* node_parent = nullptr);
	void addLine(BSearchTreeNodeItem* start, BSearchTreeNodeItem* end, Dir dir);
	void startLine(BSearchTreeNodeItem* startVex);
	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void wheelEvent(QWheelEvent* event);
	void resizeEvent(QResizeEvent* event) { this->setSceneRect(this->rect()); }
public:
	QPointF push_stackNodeScenePos = QPointF(0, 0);
	int node_spacing_rate = 1;
	qreal zValue = -1;
	int vexNum = 0;
	int arcNum = 0;
	BSearchTreeNodeItem* root{ nullptr };
	bool hasVisitedItem = false;
	void generateTree();
	void insert(int value);
	void updateDepth(BSearchTreeNodeItem* node);
	void push(int val);
	void pop();
	BSearchTreeView(QWidget* parent = nullptr);

signals:
	void logAdded(StaqueViewLog* log);

	void mouseMoved(QPointF position);
	void mouseLeftClicked(QPointF position);
	void mouseRightClicked(QPointF position);
	void mouseReleased();
public slots:
	void setSel(QGraphicsItem* sel);
	void addLog(StaqueViewLog* log) { emit logAdded(log); }
	void on_stack_push(int val);
	void on_stack_push_from_release(int val, QPointF scenePos);
	void on_stack_pop();
};
#endif // GRAPH_VIEW_H
