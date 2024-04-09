#ifndef LINKED_LIST_CANVAS_H_
#define LINKED_LIST_CANVAS_H_

#include <QWidget>

class LinkedListCanvas: public QWidget {
	Q_OBJECT

public:
	LinkedListCanvas();
	~LinkedListCanvas();


	void drawLinkedList(QPainter* painter, const QList<int>& values, int width, int height);

private:
	
};

#endif // !LINKED_LIST_CANVAS_H_
