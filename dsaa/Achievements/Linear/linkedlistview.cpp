#include "linkedlistview.h"
#include "linkedlistnodeitem.h"
#include "LinkedListViewlog.h"
#include "logger.h"
#include "common.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QScrollBar>
#include <QHBoxLayout>
#include <QToolButton>
#include <QSignalMapper>

void LinkedListView::push_back(int value)
{
	on_list_push_back(value);
}

void LinkedListView::push_front(int value)
{
	on_list_push_front(value);
}

void LinkedListView::pop_back()
{
}

void LinkedListView::pop_front()
{
}

LinkedListView::LinkedListView(QWidget* parent) :
	QGraphicsView(parent) {
	this->setMouseTracking(true);
	this->setRenderHint(QPainter::Antialiasing);
	this->setCursor(Qt::CrossCursor);
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	setResizeAnchor(QGraphicsView::AnchorUnderMouse);

	_scene = new QGraphicsScene;
	_scene->setBackgroundBrush(QColor(255, 255, 255));
	this->setScene(_scene);

	list = new DoublyLinkedList(this);
}

LinkedListNodeItem* LinkedListView::addNode(QPointF center, int value, Dir d, qreal radius) {
	LinkedListNodeItem* newNode = new LinkedListNodeItem(center, radius, value);
	_scene->addItem(newNode);
	newNode->estConnection(this);
	newNode->showAnimation();
	vexNum++;
	if (d == Dir::BACK) {
		vexes.push_back(newNode);
	}
	else if (d == Dir::FRONT) {
		vexes.push_front(newNode);
	}
	//emit vexAdded(newNode);
	emit logAdded(new LinkedListViewLog(QString("[Vex] | Added \"" + newNode->Text() + "\"")));
	return newNode;
}

void LinkedListView::addLine(LinkedListNodeItem* start, LinkedListNodeItem* end) {
	LinkedListNodeLine* newLine = new LinkedListNodeLine(start, end);
	_scene->addItem(newLine);
	//newLine->estConnection(this);
	newLine->refrshLine();
	newLine->setZValue(--zValue);
	//start->addStartLine(newLine);
	//end->addEndLine(newLine);
	arcNum++;
	lines.push_back(newLine);
	//emit arcAdded(newLine);
	emit logAdded(new LinkedListViewLog(QString("[Arc] | Added \"" + newLine->stVex()->Text() + "\" -> \"" + newLine->edVex()->Text() + "\"")));
}

void LinkedListView::mousePressEvent(QMouseEvent* event) {
	if (event->button() == Qt::RightButton) {
		onRightPress = true;
		lastPos = mapToScene(event->pos());
		return;
	}

	emit mouseLeftClicked(mapToScene(event->pos()));
}

void LinkedListView::mouseReleaseEvent(QMouseEvent* event) {
	if (onRightPress) {
		onRightPress = false;
		return;
	}

	bool containsItem = false;
	QPointF releasePos = mapToScene(event->pos());
	QList<QGraphicsItem*> itemsAtReleasePos = scene()->items(releasePos);
	for (QGraphicsItem* item : itemsAtReleasePos) {
		if (item->contains(item->mapFromScene(releasePos))) {
			// The position contains other node.
			containsItem = true;
			break;
		}
	}

	if (!containsItem) {
		//on_stack_push_from_release(111, releasePos);
	}

	emit mouseReleased();
}

void LinkedListView::mouseMoveEvent(QMouseEvent* event) {
	if (onRightPress) {
		QPointF dp = mapToScene(event->pos()) - lastPos;
		setSceneRect(sceneRect().x() - dp.x(), sceneRect().y() - dp.y(), sceneRect().width(), sceneRect().height());
		lastPos = mapToScene(event->pos());
	}
	emit mouseMoved(mapToScene(event->pos()));
}

void LinkedListView::wheelEvent(QWheelEvent* event) {
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
	QPointF cursorPoint = event->position();
#else
	QPointF cursorPoint = event->posF();
#endif
	QPointF scenePos = this->mapToScene(QPoint(cursorPoint.x(), cursorPoint.y()));

	qreal viewWidth = this->viewport()->width();
	qreal viewHeight = this->viewport()->height();

	qreal hScale = cursorPoint.x() / viewWidth;
	qreal vScale = cursorPoint.y() / viewHeight;

	qreal scaleFactor = this->transform().m11();
	int wheelDeltaValue = event->angleDelta().y();
	if (wheelDeltaValue > 0)
	{
		if (scaleFactor > 2) return;
		this->scale(1.1, 1.1);
	}
	else
	{
		if (scaleFactor < 0.5) return;
		this->scale(1.0 / 1.1, 1.0 / 1.1);
	}
	QPointF viewPoint = this->transform().map(scenePos);
	horizontalScrollBar()->setValue(int(viewPoint.x() - viewWidth * hScale));
	verticalScrollBar()->setValue(int(viewPoint.y() - viewHeight * vScale));
}

void LinkedListView::startLine(LinkedListNodeItem* startVex)
{
	strtVex = startVex;
}

void LinkedListView::setSel(QGraphicsItem* sel) {

}


void LinkedListView::on_list_push_back(int value) {
	list->push_back(value);
	if (list->size() == 1) {
		// Head node.
		addNode(push_stackNodeScenePos, value);
	}
	else {
		addNode(vexes.last()->scenePos() + QPointF(100,0), value);
		addLine((LinkedListNodeItem*)*(vexes.end() - 2), *(vexes.end() - 1));
	}
	node_spacing_rate_back++;
}

void LinkedListView::on_list_push_front(int value)
{
	list->push_front(value);
	if (list->size() == 1) {
		// Head node.
		addNode(push_stackNodeScenePos, value,Dir::FRONT);
	}
	else {
		auto node = addNode(vexes.first()->scenePos() + QPointF(-100, 0), value,Dir::FRONT);
		addLine(*(vexes.begin()),*(vexes.begin() + 1));
	}
	node_spacing_rate_front++;
}

void LinkedListView::on_list_push_from_release(int value, QPointF scenePos) {
	//list->push_back(value);
	//if (list->size() == 1) {
	//	// head node.
	//	addNode(scenepos, value);
	//}
	//else {
	//	addNode(scenepos, value);
	//	addLine((linkedlistnodeitem*)*(vexes.end() - 2), *(vexes.end() - 1));
	//}
	//push_stacknodescenepos = scenepos;
	//node_spacing_rate = 1;
}

void LinkedListView::on_list_pop() {
	//stack.pop();
	//// delete the last node
	//if (!vexes.isEmpty()) {
	//	vexes.back()->remove();
	//	vexes.pop_back();
	//}
	//if (!lines.isEmpty()) {
	//	lines.back()->remove();
	//	lines.pop_back();
	//}
	//node_spacing_rate == 1 ? node_spacing_rate = 1 : node_spacing_rate--;
}
