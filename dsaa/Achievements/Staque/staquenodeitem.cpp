#include "staquenodeitem.h"
#include "staqueview.h"
#include "staqueviewlog.h"
#include "logger.h"
#include "common.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QTimeLine>
#include <QTimer>
#include <QRandomGenerator>


QFont StaqueNodeItem::nameFont = QFont("Corbel", 13, QFont::Normal, true);

StaqueNodeItem::StaqueNodeItem(QPointF _center, qreal _r, int value, QGraphicsItem* parent) :
	QGraphicsRectItem(_center.x() - 0.5, _center.y() - 0.5, 1, 1, parent),
	center(_center),
	radius(_r),
	_value(value)
{
	regBrush = QBrush(QColor(
		QRandomGenerator::global()->bounded(64, 256), 
		QRandomGenerator::global()->bounded(64, 256), 
		QRandomGenerator::global()->bounded(128)      
	));

	nameText = QString::asprintf("%d", value);
	nameTag = new QGraphicsSimpleTextItem;
	nameTag->setPos(center + QPointF(-10, -radius - QFontMetrics(nameFont).height()));
	nameTag->setFont(nameFont);
	nameTag->setText(nameText);
	nameTag->setZValue(this->zValue());
	this->setPen(Qt::NoPen);
	this->setBrush(regBrush);
}

void StaqueNodeItem::setTextSize(int value)
{
	nameFont.setPointSize(value);
	nameTag->setFont(nameFont);
	nameTag->setPos(center + QPointF(-10, -radius - QFontMetrics(nameFont).height()));
}

void StaqueNodeItem::showAnimation()
{
	//stopAnimation();
	QTimeLine* timeLine = new QTimeLine(500, this);
	timeLine->setFrameRange(0, 200);
	QEasingCurve curve = QEasingCurve::OutBounce;
	qreal baseRadius = this->rect().width() / 2;
	qreal difRadius = radius - baseRadius;
	connect(timeLine, &QTimeLine::frameChanged, timeLine, [=](int frame) {
		qreal curProgress = curve.valueForProgress(frame / 200.0);
		qreal curRadius = baseRadius + difRadius * curProgress;
		this->setRect(QRectF(center.x() - curRadius, center.y() - curRadius, curRadius * 2, curRadius * 2));
		});
	curAnimation = timeLine;
	startAnimation();
}

void StaqueNodeItem::startAnimation()
{
	if (curAnimation != nullptr) {
		curAnimation->start();
	}
}

void StaqueNodeItem::stopAnimation()
{
	if (curAnimation != nullptr) {
		curAnimation->stop();
		curAnimation->deleteLater();
		curAnimation = nullptr;
	}
}

void StaqueNodeItem::estConnection(StaqueView* view)
{
	view->scene()->addItem(nameTag);
	connect(this, SIGNAL(logAdded(StaqueViewLog*)), view, SLOT(addLog(StaqueViewLog*)));
	connect(view, SIGNAL(mouseMoved(QPointF)), this, SLOT(onMouseMove(QPointF)));
	connect(view, SIGNAL(mouseLeftClicked(QPointF)), this, SLOT(onLeftClick(QPointF)));
	connect(view, SIGNAL(mouseRightClicked(QPointF)), this, SLOT(onRightClick(QPointF)));
	connect(view, SIGNAL(mouseReleased(QPointF)), this, SLOT(onMouseRelease(QPointF)));
	connect(this, SIGNAL(selected(QGraphicsItem*)), view, SLOT(setSel(QGraphicsItem*)));
}

void StaqueNodeItem::remove()
{
	this->setBrush(regBrush);
	onPopEffect();

	if (curAnimation) {
		connect(curAnimation, &QTimeLine::finished, this, [=]() {
			if (tag)
				scene()->removeItem(tag);
			scene()->removeItem(nameTag);
			scene()->removeItem(this);
			this->deleteLater();
		});
	}
}

void StaqueNodeItem::onMouseMove(QPointF position) {

}

void StaqueNodeItem::onLeftClick(QPointF position)
{
	if (this->contains(position)) {
		emit selected(this);
		//state |= ON_LEFT_CLICK;
		onClickEffect();
	}
}

void StaqueNodeItem::onRightClick(QPointF position)
{
}

void StaqueNodeItem::onMouseRelease(QPointF position)
{
}

void StaqueNodeItem::onClickEffect() {
	stopAnimation();
	qreal curRadius = 0.75 * radius;
	QTimeLine* timeLine = new QTimeLine(300, this);
	timeLine->setFrameRange(0, 100);
	QEasingCurve curve = QEasingCurve::OutBounce;
	qreal baseRadius = this->rect().width() / 2;
	qreal difRadius = curRadius - baseRadius;
	connect(timeLine, &QTimeLine::frameChanged, [=](int frame) {
		qreal curProgress = curve.valueForProgress(frame / 100.0);
		qreal newRadius = baseRadius + difRadius * curProgress;
		this->setRect(QRectF(center.x() - newRadius, center.y() - newRadius, newRadius * 2, newRadius * 2));
		});
	connect(timeLine, &QTimeLine::finished, [=]() {
		this->setRect(QRectF(center.x() - radius, center.y() - radius, radius * 2, radius * 2));
		});
	curAnimation = timeLine;
	startAnimation();
}


void StaqueNodeItem::onReleaseEffect() {
	stopAnimation();
	QTimeLine* timeLine = new QTimeLine(300, this);
	timeLine->setFrameRange(0, 100);
	QEasingCurve curve = QEasingCurve::OutBounce;
	qreal baseRadius = this->rect().width() / 2;
	qreal difRadius = radius * 1.25 - baseRadius;
	connect(timeLine, &QTimeLine::frameChanged, [=](int frame) {
		qreal curProgress = curve.valueForProgress(frame / 100.0);
		qreal curRadius = baseRadius + difRadius * curProgress;
		this->setRect(QRectF(center.x() - curRadius, center.y() - curRadius, curRadius * 2, curRadius * 2));
		});

	connect(timeLine, &QTimeLine::finished, [=]() {
		this->setRect(QRectF(center.x() - baseRadius, center.y() - baseRadius, baseRadius * 2, baseRadius * 2));
		});

	curAnimation = timeLine;
	startAnimation();
}

void StaqueNodeItem::onPopEffect()
{
	stopAnimation();
	qreal curRadius = 0.75 * radius;
	this->setRect(QRectF(center.x() - curRadius, center.y() - curRadius, curRadius * 2, curRadius * 2));
	QTimeLine* timeLine = new QTimeLine(300, this);
	timeLine->setFrameRange(0, 100);
	QEasingCurve curve = QEasingCurve::OutBounce;
	qreal baseRadius = this->rect().width() / 2;
	qreal difRadius = radius * 1.25 - baseRadius;
	connect(timeLine, &QTimeLine::frameChanged, [=](int frame) {
		qreal curProgress = curve.valueForProgress(frame / 100.0);
		qreal curRadius = baseRadius + difRadius * curProgress;
		this->setRect(QRectF(center.x() - curRadius, center.y() - curRadius, curRadius * 2, curRadius * 2));
		});
	curAnimation = timeLine;
	startAnimation();
}
