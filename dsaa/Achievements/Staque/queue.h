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
    void clear();

    void draw(QPainter* painter, int x, int y);

    int node_height = 40;
    int node_width = 80;
    int node_spacing = 20;
private:
    std::vector<int> data;
};



#endif // QUEUE_H
