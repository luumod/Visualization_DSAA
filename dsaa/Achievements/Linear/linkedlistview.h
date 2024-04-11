#ifndef LINKED_LIST_VIEW_H_
#define LINKED_LIST_VIEW_H_

#include <QWidget>

class BaseList;
class QPaintEvent;
class LinkedListView : public QWidget {
	Q_OBJECT

public:
	LinkedListView(QWidget* parent = nullptr);
	~LinkedListView();
	BaseList* listObj() { return base_list_obj; }

protected:
	void paintEvent(QPaintEvent* event)override;
	
private:
	bool isFinished{ false };

	BaseList* base_list_obj{ nullptr };
	QPainter* painter{ nullptr };
};

#endif