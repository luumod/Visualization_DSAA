#include "lineardatafactory.h"
//#include "doubly_linked_list.h"

LinearDataFactory* LinearDataFactory::getInstance()
{
	static LinearDataFactory linear;
	return &linear;
}

BaseList* LinearDataFactory::createLinearObject(int row, QObject* parent)
{
	//new DoublyLinkedList(parent);
	return nullptr;
}
