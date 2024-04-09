#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPushButton>

void drawLinkedList(QPainter* painter, const QList<int>& values, int width, int height) {
	painter->setPen(QColor(200, 200, 200));

	const int nodeWidth = 60; // �ڵ���εĿ��
	const int nodeHeight = 30; // �ڵ���εĸ߶�
	const int arrowSize = 10; // ��ͷ��С
	const int textSpace = 5; // �ı�����α�Ե�ľ���
	const int maxNodesPerRow = 5; // ÿ�������ʾ�Ľڵ�����
	const int row_spacing = 20; //�м��

	// 600 - 5 * 60 = 300 / 6 = 50
	// ����ڵ���
	int nodeSpacing{};
	if (values.length() <= 5) {
		nodeSpacing = (width - values.length() * nodeWidth) / (values.length() + 1);
	}
	else {
		nodeSpacing = (width - maxNodesPerRow * nodeWidth) / (maxNodesPerRow + 1);
	}

	int dir{1};

	// ���ƽڵ�ͼ�ͷ
	int x = nodeSpacing;
	int y = height / 2 - nodeHeight / 2;
	int nodesInRow = 0; // ��ǰ���ѻ��ƵĽڵ�����
	int now_count = 0;
	int cur_row = 0;
	for (int i = 0; i < values.length(); ++i) {
		// ��ǰ�еĽڵ�������1
		nodesInRow++;
		now_count++;
		// ���Ƽ�ͷ���������һ���ڵ㣩
		if (dir == 1) {
			// ���ƽڵ�
			painter->drawRect(x, y, nodeWidth, nodeHeight);

			// ���ƽڵ�ֵ
			QString text = QString::number(values[i]);
			painter->drawText(x + textSpace, y + nodeHeight / 2 + painter->fontMetrics().height() / 2, text);

			if (now_count == values.length()) {
				break;
			}
			if (now_count != 0 && now_count % 5 == 0) {
				//����һ�����µļ�ͷ
				painter->drawLine(x + nodeWidth / 2, y + nodeHeight, x + nodeWidth / 2, y + nodeHeight + row_spacing);
				painter->drawLine(x + nodeWidth / 2, y + nodeHeight + row_spacing, x + nodeWidth / 2 + 10, y + nodeHeight + row_spacing - 10);
				painter->drawLine(x + nodeWidth / 2, y + nodeHeight + row_spacing, x + nodeWidth / 2 - 10, y + nodeHeight + row_spacing - 10);
			}
			else {
				painter->drawLine(x + nodeWidth, y + nodeHeight / 2, x + nodeWidth + nodeSpacing, y + nodeHeight / 2);
				painter->drawLine(x + nodeWidth + nodeSpacing, y + nodeHeight / 2, x + nodeWidth + nodeSpacing - 10, y + nodeHeight / 2 - arrowSize / 2);
				painter->drawLine(x + nodeWidth + nodeSpacing, y + nodeHeight / 2, x + nodeWidth + nodeSpacing - 10, y + nodeHeight / 2 + arrowSize / 2);
			}
			// ��������
			x += nodeWidth + nodeSpacing;
		}
		else {
			//��������
			painter->drawRect(x, y, nodeWidth, nodeHeight);

			QString text = QString::number(values[i]);
			painter->drawText(x + textSpace, y + nodeHeight / 2 + painter->fontMetrics().height() / 2, text);

			if (now_count == values.length()) {
				break;
			}
			if (now_count != 0 && now_count % 5 == 0) {
				//����һ�����µļ�ͷ
				painter->drawLine(x + nodeWidth / 2, y + nodeHeight, x + nodeWidth / 2, y + nodeHeight + row_spacing);
				painter->drawLine(x + nodeWidth / 2, y + nodeHeight + row_spacing, x + nodeWidth / 2 + 10, y + nodeHeight + row_spacing - 10);
				painter->drawLine(x + nodeWidth / 2, y + nodeHeight + row_spacing, x + nodeWidth / 2 - 10, y + nodeHeight + row_spacing - 10);
			}
			else {
				painter->drawLine(x, y + nodeHeight / 2, x - nodeSpacing, y + nodeHeight / 2);
				painter->drawLine(x - nodeSpacing, y + nodeHeight / 2, x - nodeSpacing + 10, y + nodeHeight / 2 - arrowSize / 2);
				painter->drawLine(x - nodeSpacing, y + nodeHeight / 2, x - nodeSpacing + 10, y + nodeHeight / 2 + arrowSize / 2);
			}
			// ��������
			x -= nodeWidth + nodeSpacing;
		}

		// �����ǰ�еĽڵ������Ѿ��ﵽ���ֵ������x���겢����һ�п�ʼ����
		if (nodesInRow == maxNodesPerRow) {
			cur_row++;
			nodesInRow = 0;
			dir = 1 - dir;
			if (dir == 1) {
				// ��������
				x += nodeWidth + nodeSpacing;
			}
			else {
				// ��������
				x -= nodeWidth + nodeSpacing;
			}
			y = height / 2 - nodeHeight / 2 + cur_row * (nodeHeight + row_spacing);
		}
	}
}

class TestWidget : public QWidget {
public:
	TestWidget(const QList<int>& values) : m_values(values) {
		this->setMinimumSize(300, 300);
		init();
	}
	void init() {
		addNode();
		delNode();
	}
	void addNode() {
		btn_add = new QPushButton("Add", this);
		btn_add->move(10, 10);
		connect(btn_add, &QPushButton::clicked, this, [=]() {
			m_values.push_back(1);
			update();
		});
	}
	void delNode() {
		btn_pop_back = new QPushButton("Del", this);
		btn_pop_back->move(btn_add->pos().x() + btn_add->width(), 10);
		connect(btn_pop_back, &QPushButton::clicked, this, [=]() {
			if (!m_values.empty()) {
				m_values.pop_back();
				update();
			}
		});
	}
protected:
	void paintEvent(QPaintEvent* event) override {
		QPainter painter(this);
		drawLinkedList(&painter, m_values, width(), height());
	}

private:
	QList<int> m_values;
	QPushButton* btn_add{ nullptr };
	QPushButton* btn_pop_back{ nullptr };
};

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	// ������������
	QList<int> values;

	// �������ڲ���ʾ
	TestWidget widget(values);
	widget.show();

	return app.exec();
}
