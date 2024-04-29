#ifndef LINKEDLISTVIEW_H_
#define LINKEDLISTVIEW_H_

#include <QGraphicsView>
#include "doubly_linked_list.h"

class QGraphicsScene;
class LinkedListNodeItem;
class LinkedListNodeLine;
class LinkedListViewLog;
class LinkedListView : public QGraphicsView {
	Q_OBJECT

private:
	enum mouseStates {
		NORMAL = 0b00000000,
		ON_HOVER = 0b00010000,
		ON_SELECTED = 0b00100000,
		ON_MOVING = 0b01000000
	};
	enum Dir {
		BACK,
		FRONT,
		INSERT
	};
	QGraphicsScene* _scene;

	DoublyLinkedList* list{ nullptr };

	int vexID = 0;

	int type;
	int mouseState = NORMAL;
	bool onRightPress = false;
	QPointF lastPos;

	QVector<LinkedListNodeItem*> vexes;
	QVector<LinkedListNodeLine*> lines;

	QGraphicsItem* selItem = nullptr;
	LinkedListNodeItem* strtVex = nullptr;


	LinkedListNodeItem* addNode(QPointF center, int value = -1, Dir d = Dir::BACK, int pos = -1,qreal radius = 50.0);
	LinkedListNodeLine* addLine(LinkedListNodeItem* start, LinkedListNodeItem* end, Dir d = Dir::BACK,int pos = -1);
	void startLine(LinkedListNodeItem* startVex);
	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void wheelEvent(QWheelEvent* event);
	void resizeEvent(QResizeEvent* event) { this->setSceneRect(this->rect()); }
public:
	QPointF push_defaultPos = QPointF(100, 100);
	int node_spacing_rate_back = 0;
	int node_spacing_rate_front = 0;
	int node_spacing_rate = 1;
	qreal zValue = -1;
	int vexNum = 0;
	int arcNum = 0;
	QVector<LinkedListNodeItem*> nodes;
	bool hasVisitedItem = false;
	void push_back(int val);
	void push_front(int val);
	void pop_back();
	void pop_front();
	void clear();
	void random_gen(int size);
	void remove(int pos);
	void insert(int pos, int value);

	LinkedListView(QWidget* parent = nullptr);

signals:
	void logAdded(LinkedListViewLog* log);
	void mouseMoved(QPointF position);
	void mouseLeftClicked(QPointF position);
	void mouseRightClicked(QPointF position);
	void mouseReleased();
	void brushColorChanged();
public slots:
	void freshNodeBrushColor(QColor color);
	void freshNodeLineColor(QColor color);
	void freshNodeTextColor(QColor color);
	//void freshNodeEraseColor(QColor color);

	void setSel(QGraphicsItem* sel);
	void addLog(LinkedListViewLog* log) { emit logAdded(log); }
	void on_list_push_back(int value);
	void on_list_push_front(int value);
	void on_list_pop_back();
	void on_list_pop_front();
	void on_list_insert(int pos,int value);
	void on_list_delete(int pos);
	void on_list_push_from_release(int val, QPointF scenePos);
};
#endif // GRAPH_VIEW_H
