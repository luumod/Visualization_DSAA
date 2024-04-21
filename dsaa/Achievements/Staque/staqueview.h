#ifndef LINKED_LIST_VIEW_H_
#define LINKED_LIST_VIEW_H_

#include <QWidget>
#include "stack.h"
#include "queue.h"

class DoublyLinkedList;
class QPaintEvent;
class StaqueView : public QWidget {
	Q_OBJECT

public:
	StaqueView(QWidget* parent = nullptr);
	~StaqueView();

	void updateColors(const QString& node, const QString& arrow, const QString& text);
	void updateSettings(int nodeWidth, int nodeHeight, int arrowSize, int textSpace, int maxNodesPerRow, int row_spacing);
	void resetSettings();

	Stack stack;
	Queue queue;

protected:
	void paintEvent(QPaintEvent* event)override;

private:
	QPainter* painter{ nullptr };
};

#endif