#include "linkedlistview.h"
#include <iostream>
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
#include <QEventLoop>
#include <QTimer>
#include <QRandomGenerator>

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
	on_list_pop_back();
}

void LinkedListView::pop_front()
{
	on_list_pop_front();
}

void LinkedListView::clear()
{
	while (!list->empty()) {
		on_list_pop_back();
		QEventLoop loop;
		QTimer::singleShot(500, &loop, &QEventLoop::quit);
		loop.exec();
	}
}

void LinkedListView::random_gen(int size)
{
	for (int i = 0; i < size; i++) {
		int random = QRandomGenerator::global()->bounded(0, 10000);
		on_list_push_back(random);
		QEventLoop loop;
		QTimer::singleShot(500, &loop, &QEventLoop::quit);
		loop.exec();
	}
}

void LinkedListView::remove(int pos)
{
	on_list_delete(pos);
}

void LinkedListView::insert(int pos, int value)
{
	on_list_insert(pos,value);
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

LinkedListNodeItem* LinkedListView::addNode(QPointF center, int value, Dir d, int pos, qreal radius) {
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
	else if (d == Dir::INSERT) {
		vexes.insert(pos, newNode);
	}
	
	//emit vexAdded(newNode);
	emit logAdded(new LinkedListViewLog(QString("[Vex] | Added \"" + newNode->Text() + "\"")));
	return newNode;
}

void LinkedListView::addLine(LinkedListNodeItem* start, LinkedListNodeItem* end, Dir d, int pos) {
	LinkedListNodeLine* newLine = new LinkedListNodeLine(start, end);
	_scene->addItem(newLine);
	//newLine->estConnection(this);
	newLine->refrshLine();
	newLine->setZValue(--zValue);
	//start->addStartLine(newLine);
	//end->addEndLine(newLine);
	arcNum++;
	if (d == Dir::BACK) {
		lines.push_back(newLine);
	}
	else if (d == Dir::FRONT) {
		lines.push_front(newLine);
	}
	else if (d == Dir::INSERT) {
		lines.insert(pos,newLine);
	}
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
		addLine(*(vexes.begin()),*(vexes.begin() + 1), Dir::FRONT);
	}
}

void LinkedListView::on_list_pop_back()
{
	list->pop_back();
	// delete the last node
	if (!vexes.isEmpty()) {
		vexes.back()->remove();
		vexes.pop_back();
	}
	if (!lines.isEmpty()) {
		lines.back()->remove();
		lines.pop_back();
	}
}

void LinkedListView::on_list_pop_front()
{
	list->pop_front();
	// delete the last node
	if (!vexes.isEmpty()) {
		vexes.front()->remove();
		vexes.pop_front();
	}
	if (!lines.isEmpty()) {
		lines.front()->remove();
		lines.pop_front();
	}
}

void LinkedListView::on_list_insert(int pos, int value)
{
	/*
	example:
		0 1 2 3 4
		pos = 0 -1 -2 -3 :  push_front
		pos = 4 5 6 7...	push_back
		pos = 1 2 4...		other
	*/
	if (pos <= 0) {
		on_list_push_front(value);
	}
	else if (pos + 1 >= list->size()) {
		on_list_push_back(value);
	}
	else {
		list->insert(pos,value);
		addNode(vexes[pos]->scenePos(), value, Dir::INSERT, pos);
		for (int i = pos + 1 ; i < list->size(); i++) {
			vexes[i]->movePos(QPointF(200, 0));
		}
		addLine((LinkedListNodeItem*)*(vexes.end() - 2), *(vexes.end() - 1));
	}
}

void LinkedListView::on_list_delete(int pos)
{
	if (pos <= 0) {
		on_list_pop_front();
	}
	else if (pos >= list->size() - 1) {
		on_list_pop_back();
	}
	else {
		// Begin with: 0 1 2...
		list->remove(pos);
		if (!vexes.isEmpty()) {
			vexes[pos]->remove();
			vexes.remove(pos);
		}
		if (!lines.isEmpty()) {
			lines[pos]->remove();
			lines.remove(pos);
			if (pos - 1 >=0 && lines.size() >=1 ) {
				lines[pos - 1]->remove();
				lines.remove(pos - 1);
			}
		}
		// Refine linked line.
		addLine(vexes[pos - 1], vexes[pos], Dir::INSERT, pos - 1);
	}
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