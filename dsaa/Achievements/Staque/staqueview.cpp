#include "staqueview.h"
#include "staquenodeitem.h"
#include "staqueviewlog.h"
#include "logger.h"
#include "common.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QScrollBar>
#include <QHBoxLayout>
#include <QToolButton>
#include <QSignalMapper>

StaqueView::StaqueView(QWidget* parent) :
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
}

StaqueNodeItem* StaqueView::addNode(QPointF center,int value, qreal radius) {
	StaqueNodeItem* newNode = new StaqueNodeItem(center, radius, value);
	_scene->addItem(newNode);
	newNode->estConnection(this); 
	newNode->showAnimation();
	vexNum++;
	vexes.push_back(newNode);
	//emit vexAdded(newNode);
	emit logAdded(new StaqueViewLog(QString("[Vex] | Added \"" + newNode->Text() + "\"")));
	return newNode;
}

void StaqueView::addLine(StaqueNodeItem* start, StaqueNodeItem* end) {
	StaqueNodeLine* newLine = new StaqueNodeLine(start, end);
	_scene->addItem(newLine);
	//newLine->estConnection(this);
	newLine->refrshLine();
	newLine->setZValue(--zValue);
	//start->addStartLine(newLine);
	//end->addEndLine(newLine);
	arcNum++;
	lines.push_back(newLine);
	//emit arcAdded(newLine);
	emit logAdded(new StaqueViewLog(QString("[Arc] | Added \"" + newLine->stVex()->Text() + "\" -> \"" + newLine->edVex()->Text() + "\"")));
}

void StaqueView::mousePressEvent(QMouseEvent* event) {
	if (event->button() == Qt::RightButton) {
		onRightPress = true;
		lastPos = mapToScene(event->pos());
		return;
	}

	emit mouseLeftClicked(mapToScene(event->pos()));
}

void StaqueView::mouseReleaseEvent(QMouseEvent* event) {
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
		on_stack_push_from_release(111, releasePos);
	}

	emit mouseReleased();
}

void StaqueView::mouseMoveEvent(QMouseEvent* event) {
	if (onRightPress) {
		QPointF dp = mapToScene(event->pos()) - lastPos;
		setSceneRect(sceneRect().x() - dp.x(), sceneRect().y() - dp.y(), sceneRect().width(), sceneRect().height());
		lastPos = mapToScene(event->pos());
	}
	emit mouseMoved(mapToScene(event->pos()));
}

void StaqueView::wheelEvent(QWheelEvent* event) {
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

void StaqueView::push(int val){
	stack.push(val);
}

void StaqueView::pop() {
	stack.pop();;
}

void StaqueView::startLine(StaqueNodeItem* startVex)
{
	strtVex = startVex;
}

void StaqueView::setSel(QGraphicsItem* sel) {

}


void StaqueView::on_stack_push(int value){
	stack.push(value);
	if (stack.size() == 1) {
		// Head node.
		addNode(push_stackNodeScenePos, value);
	}
	else {
		addNode(push_stackNodeScenePos + (QPointF(200,0) * node_spacing_rate), value);
		addLine((StaqueNodeItem*)*(vexes.end() - 2), *(vexes.end() - 1));
	}
	node_spacing_rate++;
}

void StaqueView::on_stack_push_from_release(int value,QPointF scenePos) {
	stack.push(value);
	if (stack.size() == 1) {
		// Head node.
		addNode(scenePos, value);
	}
	else {
		addNode(scenePos, value);
		addLine((StaqueNodeItem*)*(vexes.end() - 2), *(vexes.end() - 1));
	}
	push_stackNodeScenePos = scenePos;
	node_spacing_rate = 1;
}

void StaqueView::on_stack_pop(){
	stack.pop();
	// delete the last node
	if (!vexes.isEmpty()) {
		vexes.back()->remove();
		vexes.pop_back();
	}
	if (!lines.isEmpty()) {
		lines.back()->remove();
		lines.pop_back();
	}
	node_spacing_rate == 1 ? node_spacing_rate = 1 : node_spacing_rate--;
}
