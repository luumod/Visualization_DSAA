#include "lineardatafactory.h"
#include "doubly_linked_list.h"

inline LinearDataFactory* LinearDataFactory::getInstance()
{
	static LinearDataFactory linear;
	return &linear;
}

BaseList* LinearDataFactory::createLinearObject(int row, QObject* parent)
{
	return new DoublyLinkedList(parent);
}
