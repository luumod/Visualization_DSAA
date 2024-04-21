#ifndef QUEUE_H
#define QUEUE_H

#include <vector>
#include <QObject>
#include <QPainter>
#include <QLabel>

class Queue :public QObject {
    Q_OBJECT

public:
    void enqueue(const int& item);
    void dequeue();
    int& front();
    bool isEmpty() const;
    size_t size() const;

    void draw(QPainter* painter, int x, int y);
private:
    std::vector<int> data;
};



#endif // QUEUE_H
