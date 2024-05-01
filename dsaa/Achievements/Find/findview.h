#ifndef FIND_VIEW_H
#define FIND_VIEW_H

#include <QGraphicsView>

class QGraphicsScene;
class FindNodeItem;
class FindNodeLine;
class FindViewLog;
class FindView : public QGraphicsView {
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

	QVector<FindNodeItem*> vec;

	FindNodeItem* addNode(QPointF center, int value = -1, qreal radius = 30.0);
	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void wheelEvent(QWheelEvent* event);
	void resizeEvent(QResizeEvent* event) { this->setSceneRect(this->rect()); }
public:
	QGraphicsSimpleTextItem* stack_info{ nullptr };
	QGraphicsSimpleTextItem* queue_info{ nullptr };
	QPointF push_stackNodeScenePos = QPointF(0,0);
	int radius = 30;
	qreal zValue = -1;
	FindView(QWidget* parent = nullptr);

signals:
	void logAdded(FindViewLog* log);
	void mouseMoved(QPointF position);
	void mouseLeftClicked(QPointF position);
	void mouseRightClicked(QPointF position);
	void mouseReleased();
public slots:
	void updateTextSize(int value);
	void addLog(FindViewLog* log) { emit logAdded(log); }
	void on_push_back(int value);
	void on_push_front(int value);
	int on_pop_back();
	int on_pop_front();
	void clear();
};
#endif // FIND_VIEW_H
