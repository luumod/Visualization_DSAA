#include "linkedlistview.h"
#include "doubly_linked_list.h"
#include <QPaintEvent>
#include <QPainter>

LinkedListView::LinkedListView(QWidget* parent)
	:QWidget(parent)
{
	base_list_obj = new DoublyLinkedList(this);
}

LinkedListView::~LinkedListView()
{
}

void LinkedListView::paintEvent(QPaintEvent* event) {

	event->accept();
	if (!painter) {
		painter = new QPainter(this);
	}
	painter->begin(this);
	
	base_list_obj->draw(painter, width(), height());

	painter->end();
}