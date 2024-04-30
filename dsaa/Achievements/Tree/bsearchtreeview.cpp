#include "bsearchtreeview.h"
#include "bsearchtreenodeitem.h"
#include "bsearchtreeviewlog.h"
#include "logger.h"
#include "common.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QScrollBar>
#include <QHBoxLayout>
#include <QToolButton>
#include <QSignalMapper>
#include <QRandomGenerator>
#include <QEventLoop>
#include <QTimer>

BSearchTreeView::BSearchTreeView(QWidget* parent) :
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
}

BSearchTreeNodeItem* BSearchTreeView::addNode(QPointF center, int value, qreal radius, BSearchTreeNodeItem* node_parent) {
	BSearchTreeNodeItem* newNode = new BSearchTreeNodeItem(center, radius, value, node_parent);
	_scene->addItem(newNode);
	newNode->estConnection(this);
	newNode->showAnimation();
	vexNum++;
	vexes.push_back(newNode);
	return newNode;
}

void BSearchTreeView::addLine(BSearchTreeNodeItem* start, BSearchTreeNodeItem* end, Dir dir) {
	BSearchTreeNodeLine* newLine = new BSearchTreeNodeLine(start, end);
	_scene->addItem(newLine);
	newLine->estConnection(this);
	newLine->refrshLine();
	newLine->setZValue(--zValue);
	if (dir == Dir::LEFT) {
		start->addStartLine_left(newLine);
	}
	else if (dir == Dir::RIGHT) {
		start->addStartLine_right(newLine);
	}
	end->addEndLine(newLine);
	arcNum++;
	lines.push_back(newLine);
	//emit arcAdded(newLine);
	//emit logAdded(new StaqueViewLog(QString("[Arc] | Added \"" + newLine->stVex()->Text() + "\" -> \"" + newLine->edVex()->Text() + "\"")));
}

void BSearchTreeView::mousePressEvent(QMouseEvent* event) {
	if (event->button() == Qt::RightButton) {
		onRightPress = true;
		lastPos = mapToScene(event->pos());
		return;
	}

	emit mouseLeftClicked(mapToScene(event->pos()));
}

void BSearchTreeView::mouseReleaseEvent(QMouseEvent* event) {
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
		on_tree_push_from_release(111, releasePos);
	}

	emit mouseReleased();
}

void BSearchTreeView::mouseMoveEvent(QMouseEvent* event) {
	if (onRightPress) {
		QPointF dp = mapToScene(event->pos()) - lastPos;
		setSceneRect(sceneRect().x() - dp.x(), sceneRect().y() - dp.y(), sceneRect().width(), sceneRect().height());
		lastPos = mapToScene(event->pos());
	}
	emit mouseMoved(mapToScene(event->pos()));
}

void BSearchTreeView::wheelEvent(QWheelEvent* event) {
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

void BSearchTreeView::push(int val) {
	//stack.push(val);
}

QString BSearchTreeView::traversal(Traversal tra)
{
	QVector<int> vec;
	if (tra == Traversal::PRE) preorderTraversal(root, vec);
	else if (tra == Traversal::IN) inorderTraversal(root,vec);
	else if (tra == Traversal::POST) postorderTraversal(root,vec);

	QStringList stringList;
	for (int i = 0; i < vec.size(); ++i) {
		stringList << QString::number(vec[i]);
	}
	QString result = stringList.join(" ");
	return result;
}

void BSearchTreeView::preorderTraversal(BSearchTreeNodeItem* root,QVector<int>& vec)
{
	if (root == nullptr)
		return;
	QEventLoop loop;
	QTimer::singleShot(300, &loop, &QEventLoop::quit);
	loop.exec();
	root->onTraversalEffect();
	vec.push_back(root->value);
	preorderTraversal(root->left,vec);
	preorderTraversal(root->right,vec);
}

void BSearchTreeView::inorderTraversal(BSearchTreeNodeItem* root, QVector<int>& vec)
{
	if (root == nullptr)
		return;
	preorderTraversal(root->left,vec);
	QEventLoop loop;
	QTimer::singleShot(300, &loop, &QEventLoop::quit);
	loop.exec();
	root->onTraversalEffect();
	vec.push_back(root->value);
	preorderTraversal(root->right, vec);
}

void BSearchTreeView::postorderTraversal(BSearchTreeNodeItem* root, QVector<int>& vec)
{
	if (root == nullptr)
		return;
	preorderTraversal(root->left, vec);
	preorderTraversal(root->right, vec);
	QEventLoop loop;
	QTimer::singleShot(300, &loop, &QEventLoop::quit);
	loop.exec();
	root->onTraversalEffect();
	vec.push_back(root->value);
}

void BSearchTreeView::clear()
{
	on_tree_pop(root);
	root = nullptr;
}

void BSearchTreeView::generateTree()
{
	for (int i = 0; i < 10; ++i) {
		int value = QRandomGenerator::global()->bounded(1, 100);
		QEventLoop loop;
		QTimer::singleShot(300, &loop, &QEventLoop::quit);
		loop.exec();
		insert(value);
	}
}

void BSearchTreeView::insert(int value) {
	if (!root) {
		root = addNode(QPointF(300,50),value,40);
		return;
	}
	BSearchTreeNodeItem* current = root;
	int rectify = QRandomGenerator::global()->bounded(30, 200);
	while (current) {
		if (value < current->value) {
			if (current->left)
				current = current->left;
			else {
				current->left = addNode(
					QPointF(current->rect().center().x()  - rectify, current->rect().center().y() + 100),
					value, 40, current
				);
				addLine(current, current->left,Dir::LEFT);
				updateDepth(current->left);
				break;
			}
		}
		else {
			if (current->right)
				current = current->right;
			else {
				current->right = addNode(
					QPointF(current->rect().center().x() + rectify, current->rect().center().y() + 100),
					value, 40, current
				);
				addLine(current, current->right, Dir::RIGHT);
				updateDepth(current->right);
				break;
			}
		}
	}
}

void BSearchTreeView::updateDepth(BSearchTreeNodeItem* node) {
	while (node) {
		int leftDepth = node->left ? node->left->depth : 0;
		int rightDepth = node->right ? node->right->depth : 0;
		node->depth = qMax(leftDepth, rightDepth) + 1;
		node = node->node_parent;
	}
}

void BSearchTreeView::pop() {
	//stack.pop();;
}

void BSearchTreeView::startLine(BSearchTreeNodeItem* startVex)
{
	strtVex = startVex;
}

void BSearchTreeView::setSel(QGraphicsItem* sel) {

}


void BSearchTreeView::on_tree_push(int value) {
	//stack.push(value);
	//if (stack.size() == 1) {
	//	// Head node.
	//	addNode(push_stackNodeScenePos, value);
	//}
	//else {
	//	addNode(push_stackNodeScenePos + (QPointF(200, 0) * node_spacing_rate), value);
	//	//addLine((StaqueNodeItem*)*(vexes.end() - 2), *(vexes.end() - 1));
	//}
	node_spacing_rate++;
}

void BSearchTreeView::on_tree_push_from_release(int value, QPointF scenePos) {
	//stack.push(value);
	//if (stack.size() == 1) {
	//	// Head node.
	//	addNode(scenePos, value);
	//}
	//else {
	//	addNode(scenePos, value);
	//	addLine((StaqueNodeItem*)*(vexes.end() - 2), *(vexes.end() - 1));
	//}
	push_stackNodeScenePos = scenePos;
	node_spacing_rate = 1;
}

void BSearchTreeView::on_tree_pop(BSearchTreeNodeItem* root) {
	if (root == nullptr)
		return;
	on_tree_pop(root->left);
	on_tree_pop(root->right);
	
	root->remove();
	root = nullptr;
}
