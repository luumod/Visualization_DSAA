#include "doubly_linked_list.h"

inline DoublyLinkedList::DoublyLinkedList(QObject* parent)
	:BaseList(parent) {
}


inline DoublyLinkedList::~DoublyLinkedList() {}


 DoublyLinkedList::Node_ptr DoublyLinkedList::search(
	const int& elem) {
	return internal_search(elem);
}


 DoublyLinkedList::Node_ptr DoublyLinkedList::find(
	std::size_t index) {
	return internal_find(index);
}

 DoublyLinkedList::Node_ptr DoublyLinkedList::insert(
	std::size_t index, const int& elem) {
	if (index == 0) {
		Base::push_front(elem);
		return m_head;
	}

	if (index >= m_size) {
		Base::push_back(elem);
		return m_tail;
	}

	Node_ptr ptr = find(index);
	auto new_node = new Node{ elem, ptr->prev, ptr };

	ptr->prev->next = new_node;
	ptr->prev = new_node;
	++m_size;

	return new_node;
}


 DoublyLinkedList::Node_ptr DoublyLinkedList::remove(
	std::size_t index) {
	if (index >= m_size) {
		return nullptr;
	}

	if (index == 0) {
		Base::pop_front();
		return m_head;
	}

	if (index + 1 == m_size) {
		Base::pop_back();
		return nullptr;
	}

	Node_ptr ptr = find(index);
	Node_ptr ret = ptr->next;

	ptr->next->prev = ptr->prev;
	ptr->prev->next = ptr->next;

	delete ptr;
	--m_size;

	return ret;
}


int& DoublyLinkedList::at(std::size_t index) {
	return find(index)->data;
}

void DoublyLinkedList::clear() {
	while (!empty()) {
		Base::pop_front();
	}
}


DoublyLinkedList::Node_ptr DoublyLinkedList::internal_search(const int& elem) {
	Node_ptr ptr{ m_head };

	while (ptr != nullptr) {
		if (ptr->data == elem) {
			break;
		}

		ptr = ptr->next;
	}

	return ptr;
}

DoublyLinkedList::Node_ptr DoublyLinkedList::internal_find(std::size_t index) {
	Node_ptr ptr{ m_head };
	std::size_t pos = 0;

	while (ptr != nullptr && pos < index) {
		ptr = ptr->next;
		++pos;
	}

	return ptr;
}
