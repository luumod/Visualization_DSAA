#include "doubly_linked_list.h"
#include <QPainter>

void DoublyLinkedList::draw(QPainter* painter, int width, int height){
	painter->setPen(QColor(200, 200, 200));

	const int nodeWidth = 60; // 节点矩形的宽度
	const int nodeHeight = 30; // 节点矩形的高度
	const int arrowSize = 10; // 箭头大小
	const int textSpace = 5; // 文本与矩形边缘的距离
	const int maxNodesPerRow = 5; // 每行最多显示的节点数量
	const int row_spacing = 20; //行间距

	// 600 - 5 * 60 = 300 / 6 = 50
	// 计算节点间距
	int nodeSpacing{};
	if (m_size <= 5) {
		nodeSpacing = (width - m_size * nodeWidth) / (m_size + 1);
	}
	else {
		nodeSpacing = (width - maxNodesPerRow * nodeWidth) / (maxNodesPerRow + 1);
	}

	int dir{ 1 };

	// 绘制节点和箭头
	int x = nodeSpacing;
	int y = height / 2 - nodeHeight / 2;
	int nodesInRow = 0; // 当前行已绘制的节点数量
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
			painter->drawRect(x, y, nodeWidth, nodeHeight);

			// 绘制节点值
			QString text = QString::number(cur->data);
			painter->drawText(x + textSpace, y + nodeHeight / 2 + painter->fontMetrics().height() / 2, text);

			if (now_count == m_size) {
				break;
			}
			if (now_count != 0 && now_count % 5 == 0) {
				//绘制一个向下的箭头
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
			painter->drawRect(x, y, nodeWidth, nodeHeight);

			QString text = QString::number(cur->data);
			painter->drawText(x + textSpace, y + nodeHeight / 2 + painter->fontMetrics().height() / 2, text);

			if (now_count == m_size) {
				break;
			}
			if (now_count != 0 && now_count % 5 == 0) {
				//绘制一个向下的箭头
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

		// 如果当前行的节点数量已经达到最大值，重置x坐标并在下一行开始绘制
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
			y = height / 2 - nodeHeight / 2 + cur_row * (nodeHeight + row_spacing);
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
