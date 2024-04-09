#ifndef LINKED_LIST_CANVAS_H_
#define LINKED_LIST_CANVAS_H_

#include <QWidget>

class SlidePage;
class LinkedListCanvas: public QWidget {
	Q_OBJECT

public:
	explicit LinkedListCanvas(QWidget* parent = nullptr);

	~LinkedListCanvas();

	void drawLinkedList(QPainter* painter, const QList<int>& values, int width, int height);

	void CreateSettings(int r);

	SlidePage* settingPage() { return settings; }
private:
	SlidePage* settings{ nullptr };
};

#endif // !LINKED_LIST_CANVAS_H_
