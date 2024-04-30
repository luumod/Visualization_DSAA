#include "bsearchtreeview.h"
#include <QTimer>
#include <QPainter>
#include <qrandom.h>

BSearchTreeView::BSearchTreeView(QWidget* parent) :
	QWidget(parent), bst(), timerId(0) 
{
	setFixedSize(800, 600);
	srand(time(nullptr));
	generateTree();
	timerId = startTimer(1000);
}

BSearchTreeView::~BSearchTreeView() {
	if (timerId != 0)
		killTimer(timerId);
}

void BSearchTreeView::paintEvent(QPaintEvent*) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.fillRect(rect(), Qt::white);
	drawTree(painter, width() / 2, 50, bst.getRoot(), width() / 4);
}

void BSearchTreeView::timerEvent(QTimerEvent* event) {
	Q_UNUSED(event);
	generateTree();
	update();
}

void BSearchTreeView::generateTree() {
	bst = BinarySearchTree();
	for (int i = 0; i < 10; ++i) {
		int value = QRandomGenerator::global()->bounded(1, 100);
		bst.insert(value);
	}
}

void BSearchTreeView::drawTree(QPainter& painter, int x, int y, TreeNode* node, int width) {
	if (!node)
		return;

	int depth = node->depth;
	int xSpacing = width / (1 << depth);

	if (node->left) {
		painter.drawLine(x, y, x - width / 2, y + 50);
		drawTree(painter, x - width / 2, y + 50, node->left, width / 2);
	}

	if (node->right) {
		painter.drawLine(x, y, x + width / 2, y + 50);
		drawTree(painter, x + width / 2, y + 50, node->right, width / 2);
	}

	painter.setPen(Qt::black);
	painter.setBrush(Qt::yellow);
	painter.drawEllipse(x - 20, y - 20, 40, 40);
	painter.drawText(x - 10, y, QString::number(node->value));
}