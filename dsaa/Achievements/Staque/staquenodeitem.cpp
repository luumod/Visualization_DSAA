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

/// <summary>
/// 
/// </summary>

unsigned int StaqueNodeItem::internalID = 0;

StaqueNodeItem::StaqueNodeItem(QPointF _center, qreal _r, int value, QGraphicsItem* parent) :
	QGraphicsRectItem(_center.x() - 0.5, _center.y() - 0.5, 1, 1, parent),
	center(_center),
	radius(_r) 
{
	id = internalID++;
	nameText = QString::asprintf("%d", value);
	nameTag = new QGraphicsSimpleTextItem;
	nameTag->setPos(center + QPointF(radius, -radius - QFontMetrics(nameFont).height()));
	nameTag->setFont(nameFont);
	nameTag->setText(nameText);
	nameTag->setZValue(this->zValue());
	this->setPen(Qt::NoPen);
	this->setBrush(regBrush);
}

void StaqueNodeItem::move(QPointF position){
	QPointF displacement = position - (this->scenePos() + this->rect().center());
	this->setRect(QRectF(this->rect().x() + displacement.x(), this->rect().y() + displacement.y(), this->rect().width(), this->rect().height()));
	center = center + displacement;
	if (tag)
		tag->moveBy(displacement.x(), displacement.y());
	/*for (int i = 0; i < linesStartWith.size(); i++)
		linesStartWith[i]->moveStart(this);
	for (int i = 0; i < linesEndWith.size(); i++)
		linesEndWith[i]->moveEnd(this);*/
	nameTag->moveBy(displacement.x(), displacement.y());
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
	//connect(timeLine, &QTimeLine::finished, [this]() {this->state &= ~PREPARING; });
	//timeLine->start();
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
	connect(view, SIGNAL(mouseReleased()), this, SLOT(onMouseRelease()));
	connect(this, SIGNAL(selected(QGraphicsItem*)), view, SLOT(setSel(QGraphicsItem*)));
	/*connect(this, SIGNAL(setHover(bool)), view, SLOT(setHover(bool)));
	connect(this, SIGNAL(lineFrom(MyGraphicsVexItem*)), view, SLOT(startLine(MyGraphicsVexItem*)));
	connect(this, SIGNAL(menuStateChanged(QGraphicsItem*, bool)), view, SLOT(setMenu(QGraphicsItem*, bool)));
	connect(this, SIGNAL(removed(MyGraphicsVexItem*)), view, SLOT(vexRemoved(MyGraphicsVexItem*)));
	connect(this, SIGNAL(addAnimation(QTimeLine*)), view, SLOT(addAnimation(QTimeLine*)));*/
}

void StaqueNodeItem::remove()
{
	this->setBrush(QColor(Qt::red));
	onPopEffect();

	if (curAnimation) {
		connect(curAnimation, &QTimeLine::finished, this, [=]() {
			if (tag)
				scene()->removeItem(tag);
			scene()->removeItem(nameTag);
			scene()->removeItem(this);
			//emit removed(this);
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

void StaqueNodeItem::onMouseRelease()
{
	onReleaseEffect();
}

void StaqueNodeItem::onClickEffect() {
	stopAnimation();
	qreal curRadius = 0.75 * radius;
	this->setRect(QRectF(center.x() - curRadius, center.y() - curRadius, curRadius * 2, curRadius * 2));
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

StaqueNodeLine::StaqueNodeLine(StaqueNodeItem* start, StaqueNodeItem* end, QGraphicsItem* parent):
	QGraphicsLineItem(parent),
	startVex(start),
	endVex(end) 
{
	//Set display effect
	defaultPen.setWidth(lineWidth);
	defaultPen.setStyle(lineStyle);
	defaultPen.setCapStyle(capStyle);
	defaultPen.setColor(defaultColor);
	curPen = defaultPen;

	setFlag(QGraphicsItem::ItemIsSelectable);
}

void StaqueNodeLine::moveStart(StaqueNodeItem* start)
{
	delArrow();
	startVex = start;
	refrshLine();
}

void StaqueNodeLine::moveEnd(StaqueNodeItem* end)
{
	delArrow();
	endVex = end;
	refrshLine();
}

void StaqueNodeLine::remove()
{
	QTimer::singleShot(300, [=]() {
		if (line1)
			scene()->removeItem(line1);
		if (line2)
			scene()->removeItem(line2);
		if (arrow)
			scene()->removeItem(arrow);
		if (textItem)
			scene()->removeItem(textItem);
		scene()->removeItem(this);
		//emit removed(this);
		this->deleteLater();
	});
}

void StaqueNodeLine::drawText()
{
	if (textItem) {
		this->scene()->removeItem(textItem);
		textItem = nullptr;
	}
	QGraphicsSimpleTextItem* t = new QGraphicsSimpleTextItem(text);
	t->setFont(textFont);
	t->setPos(center - QPointF(t->boundingRect().width(), t->boundingRect().height()) / 2);
	QColor c = curPen.color();
	t->setBrush(c.darker(150));
	this->scene()->addItem(t);
	textItem = t;
}

void StaqueNodeLine::drawLine()
{
	//draw invisible line
	this->setLine(sP.x(), sP.y(), eP.x(), eP.y());
	//this->setPen(curPen);
	QPen bgPen;
	bgPen.setColor(QColor(255, 255, 255, 0));
	bgPen.setWidth(lineWidth + 5);
	this->setPen(bgPen);

	if (line1) {
		scene()->removeItem(line1);
		line1 = nullptr;
	}
	if (line2) {
		scene()->removeItem(line2);
		line2 = nullptr;
	}

	center = (startVex->scenePos() + startVex->rect().center() + endVex->scenePos() + endVex->rect().center()) / 2;

	drawText();

	if (text != "" && (eP - center).x() * (sP - center).x() <= 0) {
		qreal dx = 0;
		qreal dy = 0;
		int f1 = 1, f2 = 1;
		if (textItem->boundingRect().width() != 0) {
			if (abs(textItem->boundingRect().height() / textItem->boundingRect().width()) < abs(tan(angle))) {
				dx = (textItem->boundingRect().height() + 10) / (2 * tan(angle));
				dy = (textItem->boundingRect().height() + 10) / 2;
				f2 = angle > 0 ? -1 : 1;
			}
			else {
				dy = (textItem->boundingRect().width() + 10) * tan(angle) / 2;
				dx = (textItem->boundingRect().width() + 10) / 2;
				f1 = tan(angle) < 0 ? -1 : 1;
				f2 = angle >= 0 ? -1 : 1;
			}
		}
		dx *= f1 * f2;
		dy *= f1 * f2;
		QGraphicsLineItem* newLine1 = new QGraphicsLineItem(sP.x(), sP.y(), center.x() + dx, center.y() + dy);
		QGraphicsLineItem* newLine2 = new QGraphicsLineItem(center.x() - dx, center.y() - dy, eP.x(), eP.y());

		newLine1->setZValue(this->zValue() - 1);
		newLine2->setZValue(this->zValue() - 1);
		newLine1->setPen(curPen);
		newLine2->setPen(curPen);

		scene()->addItem(newLine1);
		scene()->addItem(newLine2);
		line1 = newLine1;
		line2 = newLine2;
	}
	else {
		QGraphicsLineItem* newLine = new QGraphicsLineItem(sP.x(), sP.y(), eP.x(), eP.y());
		newLine->setPen(curPen);
		newLine->setZValue(this->zValue() - 1);
		this->scene()->addItem(newLine);
		line1 = newLine;
	}
	drawArrow();
}

void StaqueNodeLine::delArrow()
{
	if (arrow != nullptr) {
		this->scene()->removeItem(arrow);
		arrow = nullptr;
	}
}

void StaqueNodeLine::drawArrow()
{
	QPointF temp = eP;
	eP = (sP + eP) / 2;
	QPointF leftEnd = QPointF(eP.x() - cos(angle - M_PI / 6) * arrowLength, eP.y() - sin(angle - M_PI / 6) * arrowLength);
	QPointF rightEnd = QPointF(eP.x() - cos(angle + M_PI / 6) * arrowLength, eP.y() - sin(angle + M_PI / 6) * arrowLength);

	QPainterPath arrowPath;
	arrowPath.moveTo(leftEnd);
	arrowPath.lineTo(eP);
	arrowPath.lineTo(rightEnd);

	QGraphicsPathItem* arrowItem = new QGraphicsPathItem(arrowPath);
	arrowItem->setPen(curPen);
	this->scene()->addItem(arrowItem);
	arrow = arrowItem;

	eP = temp;
}

void StaqueNodeLine::refrshLine()
{
	setLengthRate(1);
	drawLine();
}

void StaqueNodeLine::setLengthRate(qreal r)
{
	sP = startVex->scenePos() + startVex->rect().center();
	eP = endVex->scenePos() + endVex->rect().center();
	dP = eP - sP;
	angle = atan2(dP.y(), dP.x());
	eP -= QPointF(endVex->getRadius() * cos(angle), endVex->getRadius() * sin(angle));
	sP += QPointF(endVex->getRadius() * cos(angle), endVex->getRadius() * sin(angle));
	dP = (eP - sP) * r;
	eP = sP + dP;
}