#include "findview.h"
#include "findnodeitem.h"
#include "findviewlog.h"
#include "logger.h"
#include "common.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QScrollBar>
#include <QHBoxLayout>
#include <QToolButton>
#include <QSignalMapper>

FindView::FindView(QWidget* parent) :
	QGraphicsView(parent){
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


	//QFont font = QFont("Corbel", 13, QFont::Normal, true);
	//stack_info = new QGraphicsSimpleTextItem;
	//stack_info->setFont(font);
	////stack_info->setText(QString("size of the stack: %1").arg(stack.size()));
	//stack_info->setPos(100, 180);
	//_scene->addItem(stack_info);
	//queue_info = new QGraphicsSimpleTextItem;
	//queue_info->setFont(font);
	////queue_info->setText(QString("size of the queue: %1").arg(queue.size()));
	//queue_info->setPos(100, 210);
	//_scene->addItem(queue_info);

}

FindNodeItem* FindView::addNode(QPointF center,int value, qreal radius) {
	FindNodeItem* newNode = new FindNodeItem(center, radius, value);
	_scene->addItem(newNode);
	newNode->estConnection(this); 
	newNode->showAnimation();
	emit logAdded(new FindViewLog(QString("[Vex] | Added \"" + newNode->Text() + "\"")));
	return newNode;
}

void FindView::mousePressEvent(QMouseEvent* event) {
	if (event->button() == Qt::RightButton) {
		onRightPress = true;
		lastPos = mapToScene(event->pos());
		return;
	}

	emit mouseLeftClicked(mapToScene(event->pos()));
}

void FindView::mouseReleaseEvent(QMouseEvent* event) {
	if (onRightPress) {
		onRightPress = false;
		return;
	}

	emit mouseReleased();
}

void FindView::mouseMoveEvent(QMouseEvent* event) {
	if (onRightPress) {
		QPointF dp = mapToScene(event->pos()) - lastPos;
		setSceneRect(sceneRect().x() - dp.x(), sceneRect().y() - dp.y(), sceneRect().width(), sceneRect().height());
		lastPos = mapToScene(event->pos());
	}
	emit mouseMoved(mapToScene(event->pos()));
}

void FindView::wheelEvent(QWheelEvent* event) {
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

void FindView::updateTextSize(int value) {
	/*for (auto& x : stack) {
		x->setTextSize(value);
	}
	for (auto& x : queue) {
		x->setTextSize(value);
	}*/
}

void FindView::on_push_back(int value)
{
	if (vec.isEmpty()) {
		vec.push_back(addNode(QPointF(radius + 20, radius + 20),value, radius));
	}
	else {
		vec.push_back(addNode(QPointF(vec.back()->rect().center() + QPointF(radius * 2, 0)), value, radius));
	}
	//stack_info->setText(QString("size of the stack: %1").arg(vec.size()));
}

void FindView::on_push_front(int value)
{
	if (vec.isEmpty()) {
		vec.push_front(addNode(QPointF(radius + 20, radius + 20), value, radius));
	}
	else {
		vec.push_front(addNode(QPointF(vec.front()->rect().center() - QPointF(radius * 2, 0)), value, radius));
	}
}

int FindView::on_pop_back()
{
	if (vec.isEmpty()) {
		throw std::runtime_error("Array is empty");
	}
	auto value = vec.back()->value();
	vec.back()->remove();
	vec.pop_back();
	//stack_info->setText(QString("size of the stack: %1").arg(vec.size()));
	return value;
}

int FindView::on_pop_front()
{
	if (vec.isEmpty()) {
		throw std::runtime_error("Array is empty");
	}
	auto value = vec.front()->value();
	vec.front()->remove();
	vec.pop_front();
	return value;
}

void FindView::clear()
{
	while (!vec.isEmpty()) {
		vec.back()->remove();
		vec.pop_back();
	}
	vec.clear();
}
