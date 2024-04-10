#ifndef CORE_DOUBLY_LINKED_LIST_H_
#define CORE_DOUBLY_LINKED_LIST_H_

#include "base_list.h"

class DoublyLinkedList : public BaseList {

    Q_OBJECT

protected:
   /* using Base = BaseList;
    using Node = typename Base::Node;
    using Node_ptr = Node*;
    using cNode_ptr = const Node*;*/

public:
    /*using Base::empty;
    using Base::size;*/

    explicit DoublyLinkedList(QObject* parent = nullptr);

    ~DoublyLinkedList();

    Node_ptr search(const int& elem);

    Node_ptr find(std::size_t index);

    Node_ptr insert(std::size_t index, const int& elem);

    Node_ptr remove(std::size_t index);

    int& at(std::size_t index);

    void clear();

protected:
    /*using Base::m_head;
    using Base::m_size;
    using Base::m_tail;*/
    Node_ptr internal_search(const int& elem);
    Node_ptr internal_find(std::size_t index);
};

#endif  // CORE_DOUBLY_LINKED_LIST_HPP_
