#include "staqueview.h"
#include <QGraphicsItem>

StaqueView::StaqueView(QWidget* parent) :
	QGraphicsView(parent)
 {
	this->setMouseTracking(true);
	this->setBackgroundBrush(Qt::transparent);
	myGraphicsScene = new QGraphicsScene();
	this->setScene(myGraphicsScene);
	myGraphicsScene->setBackgroundBrush(QColor(255, 0, 0));
	this->setRenderHint(QPainter::Antialiasing);
	this->setCursor(Qt::CrossCursor);
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	setResizeAnchor(QGraphicsView::AnchorUnderMouse);
}

void StaqueView::mousePressEvent(QMouseEvent* event) {
	if (event->button() == Qt::MiddleButton) {
		onMiddlePress = true;
		lastPos = mapToScene(event->pos());
		return;
	}
}

void StaqueView::mouseReleaseEvent(QMouseEvent* event) {
	if (onMiddlePress) {
		onMiddlePress = false;
		return;
	}
	emit mouseReleased();
	changeCursor();
}

void StaqueView::mouseMoveEvent(QMouseEvent* event) {
	if (onMiddlePress) {
		QPointF dp = mapToScene(event->pos()) - lastPos;
		setSceneRect(sceneRect().x() - dp.x(), sceneRect().y() - dp.y(), sceneRect().width(), sceneRect().height());
		lastPos = mapToScene(event->pos());
	}
	changeCursor();
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

void StaqueView::changeCursor() {

}

void StaqueView::setHover(bool in) {
	if (in)
		mouseState |= ON_HOVER;
	else
		mouseState &= ~ON_HOVER;
}