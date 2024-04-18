#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include "spinbox.h"

class TestWidget : public QWidget {
public:
	TestWidget(const QList<int>& values) : m_values(values) {
		this->setMinimumSize(300, 300);
		//init();
		auto spin = new SpinBox("input: ",this);
		spin->move(20, 20);
		spin->resize(200, 50);
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
