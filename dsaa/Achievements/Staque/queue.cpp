#include "queue.h"

void Queue::enqueue(const int& item) {
    data.push_back(item);
}


void Queue::dequeue() {
    if (!isEmpty()) {
        data.erase(data.begin());
    }
}


int& Queue::front() {
    return data.front();
}


bool Queue::isEmpty() const {
    return data.empty();
}


size_t Queue::size() const {
    return data.size();
}

void Queue::draw(QPainter* painter, int x, int y) {
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(Qt::red);

    int width = 50;
    int height = 30;
    int spacing = 10;

    painter->drawText(x, y - 20, "Queue");
    for (int i = 0; i < data.size(); ++i) {
        painter->drawRect(x, y, width, height);
        painter->drawText(x + 10, y + 20, QString::number(data[i]));
        y += height + spacing;
    }
}