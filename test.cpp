#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPushButton>


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

	// 创建链表数据
	QList<int> values;

	// 创建窗口并显示
	TestWidget widget(values);
	widget.show();

	return app.exec();
}
