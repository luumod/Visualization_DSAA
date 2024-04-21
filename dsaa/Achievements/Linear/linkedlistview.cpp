#include "linkedlistview.h"
#include "doubly_linked_list.h"
#include "logger.h"
#include "common.h"
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

void LinkedListView::updateSettings(int nodeWidth, int nodeHeight, int arrowSize, int textSpace, int maxNodesPerRow, int row_spacing){
	base_list_obj->updateSettings(nodeWidth, nodeHeight, arrowSize, textSpace, maxNodesPerRow, row_spacing);
	// Redraw.
	update();
#if DEBUG
	Logger::debug("-------- UpdateSettings and redrawing...-----------");
#endif
}

void LinkedListView::resetSettings(){
	base_list_obj->resetSettings();
	update();
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