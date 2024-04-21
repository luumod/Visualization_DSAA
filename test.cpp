#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QScrollBar>
#include <QPainter>

// �Զ���ڵ���
class NodeItem : public QGraphicsItem {
public:
    NodeItem(int value, QGraphicsItem* parent = nullptr) : QGraphicsItem(parent), m_value(value) {}

    QRectF boundingRect() const override {
        return QRectF(-20, -20, 40, 40); // ���ýڵ�ı߽�
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override {
        Q_UNUSED(option);
        Q_UNUSED(widget);

        painter->setBrush(Qt::blue); // ���ýڵ���ɫ
        painter->drawEllipse(-20, -20, 40, 40); // ���ƽڵ�
        painter->drawText(-5, 5, QString::number(m_value)); // ���ƽڵ�ֵ
    }

private:
    int m_value;
};

// �Զ���������ӻ���ͼ��
class LinkedListView : public QGraphicsView {
public:
    LinkedListView(QWidget* parent = nullptr) : QGraphicsView(parent) {
        // ��������
        scene = new QGraphicsScene(this);
        setScene(scene);

        // ��ӽڵ㵽������
        addNode(10);
        addNode(20);
        addNode(30);
        addNode(40);

        // ���ó�����С���޴�
        setSceneRect(0, 0, 1000, 500);
    }

    void addNode(int value) {
        NodeItem* node = new NodeItem(value);
        scene->addItem(node);

        // ���ýڵ�λ��
        node->setPos(nodeCount * 100, 50);

        nodeCount++;
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
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn); // ʼ����ʾˮƽ������
    view.show();

    return app.exec();
}
