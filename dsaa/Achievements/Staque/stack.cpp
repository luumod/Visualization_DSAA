#include "stack.h"

void Stack::push(const int& item) {
	data.push_back(item);
}

void Stack::pop() {
	if (!isEmpty()) {
		data.pop_back();
	}
}

int& Stack::top() {
	return data.back();
}


bool Stack::isEmpty() const {
	return data.empty();
}


size_t Stack::size() const {
	return data.size();
}

void Stack::draw(QPainter* painter, int x, int y) {
	painter->setRenderHint(QPainter::Antialiasing);
	painter->setPen(Qt::red);

	int width = 50;
	int height = 30;
	int spacing = 10;

	// ����ջ
	painter->drawText(x, y - 20, "Stack");
	for (int i = 0; i < data.size(); ++i) {
		painter->drawRect(x, y, width, height);
		painter->drawText(x + 10, y + 20, QString::number(data[i]));
		y += height + spacing;
	}
}