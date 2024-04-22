#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QScrollBar>
#include <QPainter>
#include <QMouseEvent>

// 自定义节点类
class NodeItem : public QGraphicsItem {
public:
	NodeItem(int value, QGraphicsItem* parent = nullptr) : QGraphicsItem(parent), m_value(value) {}

	QRectF boundingRect() const override {
		return QRectF(-20, -20, 40, 40); // 设置节点的边界
	}

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override {
		Q_UNUSED(option);
		Q_UNUSED(widget);

		painter->setBrush(Qt::blue); // 设置节点颜色
		painter->drawEllipse(-20, -20, 40, 40); // 绘制节点
		painter->drawText(-5, 5, QString::number(m_value)); // 绘制节点值
	}

private:
	int m_value;
};

// 自定义链表可视化视图类
class LinkedListView : public QGraphicsView {
public:
	LinkedListView(QWidget* parent = nullptr) : QGraphicsView(parent) {
		// 创建场景
		scene = new QGraphicsScene(this);
		setScene(scene);
		scene->setBackgroundBrush(QColor(0, 255, 255));

		// 添加节点到链表中
		addNode(10);
		addNode(20);
		addNode(30);
		addNode(40);

		// 设置场景大小无限大
		setSceneRect(0, 0, 1000, 500);
	}

	void addNode(int value) {
		NodeItem* node = new NodeItem(value);
		scene->addItem(node);

		// 设置节点位置
		node->setPos(nodeCount * 100, 50);

		nodeCount++;
	}
protected:
	void mousePressEvent(QMouseEvent* ev)override {
		QPoint pos = ev->pos();
		QPointF scene_pos = this->mapToScene(pos);
		QPointF global_pos = this->mapToGlobal(pos);
		qInfo() << "view pos: " << pos << "scene pos: " << scene_pos << "global pos: " << global_pos;
	}

private:
	QGraphicsScene* scene;
	int nodeCount = 0;
};

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	LinkedListView view;
	view.setWindowTitle("Linked List Visualization");
	view.resize(500, 200);
	view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn); // 始终显示水平滚动条
	view.show();

	return app.exec();
}
