#include "doubly_linked_list.h"
#include <QPainter>

int DoublyLinkedList::getHeight() const {
	int rows = (m_size + maxNodesPerRow - 1) / maxNodesPerRow;
	return rows * (nodeHeight + row_spacing) + 10;
}

void DoublyLinkedList::draw(QPainter* painter, int width, int height){
	int nodeSpacing{};
	if (m_size <= 5) {
		nodeSpacing = (width - m_size * nodeWidth) / (m_size + 1);
	}
	else {
		nodeSpacing = (width - maxNodesPerRow * nodeWidth) / (maxNodesPerRow + 1);
	}

	int dir{ 1 };

	int x = nodeSpacing;
	int y = 10; 
	int nodesInRow = 0;
	int now_count = 0;
	int cur_row = 0;
	Node* cur = m_head;
	while (cur != nullptr) {
		// 当前行的节点数量加1
		nodesInRow++;
		now_count++;
		// 绘制箭头（除了最后一个节点）
		if (dir == 1) {
			// 绘制节点
			painter->fillRect(x, y, nodeWidth, nodeHeight, QBrush(color_node));

			QString text = QString::number(cur->data);
			QFont textFont = QFont("Corbel", 12);
			painter->setFont(textFont);
			painter->setPen(color_text);
			painter->drawText(x + textSpace, y + nodeHeight / 2 + painter->fontMetrics().height() / 2, text);

			if (now_count == m_size) {
				break;
			}
			painter->setPen(color_arrow);
			if (now_count != 0 && now_count % maxNodesPerRow == 0) {
				painter->drawLine(x + nodeWidth / 2, y + nodeHeight, x + nodeWidth / 2, y + nodeHeight + row_spacing);
				painter->drawLine(x + nodeWidth / 2, y + nodeHeight + row_spacing, x + nodeWidth / 2 + 10, y + nodeHeight + row_spacing - 10);
				painter->drawLine(x + nodeWidth / 2, y + nodeHeight + row_spacing, x + nodeWidth / 2 - 10, y + nodeHeight + row_spacing - 10);
			}
			else {
				painter->drawLine(x + nodeWidth, y + nodeHeight / 2, x + nodeWidth + nodeSpacing, y + nodeHeight / 2);
				painter->drawLine(x + nodeWidth + nodeSpacing, y + nodeHeight / 2, x + nodeWidth + nodeSpacing - 10, y + nodeHeight / 2 - arrowSize / 2);
				painter->drawLine(x + nodeWidth + nodeSpacing, y + nodeHeight / 2, x + nodeWidth + nodeSpacing - 10, y + nodeHeight / 2 + arrowSize / 2);
			}
			// 更新坐标
			x += nodeWidth + nodeSpacing;
		}
		else {
			//从右往左
			painter->fillRect(x, y, nodeWidth, nodeHeight, QBrush(color_node));

			QString text = QString::number(cur->data);
			QFont textFont = QFont("Corbel", 12);
			painter->setFont(textFont);
			painter->setPen(color_text);
			painter->drawText(x + textSpace, y + nodeHeight / 2 + painter->fontMetrics().height() / 2, text);

			if (now_count == m_size) {
				break;
			}
			painter->setPen(color_arrow);
			if (now_count != 0 && now_count % maxNodesPerRow == 0) {
				painter->drawLine(x + nodeWidth / 2, y + nodeHeight, x + nodeWidth / 2, y + nodeHeight + row_spacing);
				painter->drawLine(x + nodeWidth / 2, y + nodeHeight + row_spacing, x + nodeWidth / 2 + 10, y + nodeHeight + row_spacing - 10);
				painter->drawLine(x + nodeWidth / 2, y + nodeHeight + row_spacing, x + nodeWidth / 2 - 10, y + nodeHeight + row_spacing - 10);
			}
			else {
				painter->drawLine(x, y + nodeHeight / 2, x - nodeSpacing, y + nodeHeight / 2);
				painter->drawLine(x - nodeSpacing, y + nodeHeight / 2, x - nodeSpacing + 10, y + nodeHeight / 2 - arrowSize / 2);
				painter->drawLine(x - nodeSpacing, y + nodeHeight / 2, x - nodeSpacing + 10, y + nodeHeight / 2 + arrowSize / 2);
			}
			// 更新坐标
			x -= nodeWidth + nodeSpacing;
		}

		if (nodesInRow == maxNodesPerRow) {
			cur_row++;
			nodesInRow = 0;
			dir = 1 - dir;
			if (dir == 1) {
				// 从右往左
				x += nodeWidth + nodeSpacing;
			}
			else {
				// 从左往右
				x -= nodeWidth + nodeSpacing;
			}
			// height / 2 - nodeHeight / 2
			y = 10 + cur_row * (nodeHeight + row_spacing);
		}

		cur = cur->next;
	}
}

DoublyLinkedList::DoublyLinkedList(QObject* parent)
	:BaseList(parent) {
}


DoublyLinkedList::~DoublyLinkedList() {}


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
		push_front(elem);
		return m_head;
	}

	if (index >= m_size) {
		push_back(elem);
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
		pop_front();
		return m_head;
	}

	if (index + 1 == m_size) {
		pop_back();
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
		pop_front();
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
