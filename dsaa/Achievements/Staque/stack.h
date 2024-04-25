#ifndef STACK_H
#define STACK_H

#include <vector>
#include <QObject>
#include <QPainter>

class Stack :public QObject {
	Q_OBJECT
	
public:
	void push(const int& item);
	void pop();
	int& top();
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

#endif // STACK_H
