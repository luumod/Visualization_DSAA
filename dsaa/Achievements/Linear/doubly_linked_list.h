#ifndef CORE_DOUBLY_LINKED_LIST_H_
#define CORE_DOUBLY_LINKED_LIST_H_

#include "base_list.h"
#include <QColor>

class QPainter;
class DoublyLinkedList : public BaseList {

    Q_OBJECT

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

public:
    int getHeight() const;
    void draw(QPainter* painter, int width, int height)override;

protected:
    Node_ptr internal_search(const int& elem);
    Node_ptr internal_find(std::size_t index);

};


#endif  // CORE_DOUBLY_LINKED_LIST_HPP_
