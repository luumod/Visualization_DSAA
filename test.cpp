#include <QApplication>
#include <QWidget>
#include <QPainter>

void drawLinkedList(QPainter* painter, const QList<int>& values, int width, int height) {
    painter->setPen(QColor(200, 200, 200));

    const int nodeWidth = 60; // �ڵ���εĿ��
    const int nodeHeight = 30; // �ڵ���εĸ߶�
    const int arrowSize = 10; // ��ͷ��С
    const int textSpace = 5; // �ı�����α�Ե�ľ���

    // 600 - 5 * 60 = 300 / 6 = 50
    // ����ڵ���
    const int nodeSpacing = (width - values.length() * nodeWidth) / (values.length() + 1);

    // ���ƽڵ�ͼ�ͷ
    int x = nodeSpacing;
    int y = height / 2 - nodeHeight / 2;
    for (int i = 0; i < values.length(); ++i) {
        // ���ƽڵ�
        painter->drawRect(x, y, nodeWidth, nodeHeight);

        // ���ƽڵ�ֵ
        QString text = QString::number(values[i]);
        painter->drawText(x + textSpace, y + nodeHeight / 2 + painter->fontMetrics().height() / 2, text);

        // ���Ƽ�ͷ���������һ���ڵ㣩
        if (i < values.length() - 1) {
            painter->drawLine(x + nodeWidth, y + nodeHeight / 2, x + nodeWidth + arrowSize, y + nodeHeight / 2);
            painter->drawLine(x + nodeWidth + arrowSize, y + nodeHeight / 2, x + nodeWidth + arrowSize - arrowSize / 2, y + nodeHeight / 2 - arrowSize / 2);
            painter->drawLine(x + nodeWidth + arrowSize, y + nodeHeight / 2, x + nodeWidth + arrowSize - arrowSize / 2, y + nodeHeight / 2 + arrowSize / 2);
        }

        // ��������
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

    // ������������
    QList<int> values;
    values << 5 << 3 << 9 << 2 << 7;

    // �������ڲ���ʾ
    TestWidget widget(values);
    widget.resize(500, 100);
    widget.show();

    return app.exec();
}
