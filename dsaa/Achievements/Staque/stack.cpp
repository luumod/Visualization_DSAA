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

void Stack::clear(){
	data.clear();
}

void Stack::draw(QPainter* painter, int x, int y) {
	painter->setRenderHint(QPainter::Antialiasing);
	painter->setPen(Qt::red);

	// »æÖÆÕ»
	painter->drawText(x, y - 20, "Stack");
	for (int i = 0; i < data.size(); ++i) {
		painter->drawRect(x, y, node_width, node_height);
		painter->drawText(x + 10, y + 20, QString::number(data[i]));
		y += node_height + node_spacing;
	}
}