#include <QApplication>
#include <QWidget>
#include <QPainter>

void drawLinkedList(QPainter* painter, const QList<int>& values, int width, int height) {
    painter->setPen(QColor(200, 200, 200));

    const int nodeWidth = 60; // 节点矩形的宽度
    const int nodeHeight = 30; // 节点矩形的高度
    const int arrowSize = 10; // 箭头大小
    const int textSpace = 5; // 文本与矩形边缘的距离

    // 600 - 5 * 60 = 300 / 6 = 50
    // 计算节点间距
    const int nodeSpacing = (width - values.length() * nodeWidth) / (values.length() + 1);

    // 绘制节点和箭头
    int x = nodeSpacing;
    int y = height / 2 - nodeHeight / 2;
    for (int i = 0; i < values.length(); ++i) {
        // 绘制节点
        painter->drawRect(x, y, nodeWidth, nodeHeight);

        // 绘制节点值
        QString text = QString::number(values[i]);
        painter->drawText(x + textSpace, y + nodeHeight / 2 + painter->fontMetrics().height() / 2, text);

        // 绘制箭头（除了最后一个节点）
        if (i < values.length() - 1) {
            painter->drawLine(x + nodeWidth, y + nodeHeight / 2, x + nodeWidth + arrowSize, y + nodeHeight / 2);
            painter->drawLine(x + nodeWidth + arrowSize, y + nodeHeight / 2, x + nodeWidth + arrowSize - arrowSize / 2, y + nodeHeight / 2 - arrowSize / 2);
            painter->drawLine(x + nodeWidth + arrowSize, y + nodeHeight / 2, x + nodeWidth + arrowSize - arrowSize / 2, y + nodeHeight / 2 + arrowSize / 2);
        }

        // 更新坐标
        x += nodeWidth + nodeSpacing;
    }
}

class TestWidget : public QWidget {
public:
    TestWidget(const QList<int>& values) : m_values(values) {}

protected:
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);
        drawLinkedList(&painter, m_values, width(), height());
    }

private:
    QList<int> m_values;
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // 创建链表数据
    QList<int> values;
    values << 5 << 3 << 9 << 2 << 7;

    // 创建窗口并显示
    TestWidget widget(values);
    widget.resize(500, 100);
    widget.show();

    return app.exec();
}
