#include "base_list.h"

inline BaseList::BaseList(QObject* parent)
    :QObject(parent) {}

BaseList::~BaseList() {
    clean_up();
}

bool BaseList::empty() const {
    return m_size == 0;
}

std::size_t BaseList::size() const {
    return m_size;
}

void BaseList::init_first_element(const int& elem) {
    m_head = new Node{ elem, nullptr, nullptr };
    m_tail = m_head;
    m_size = 1;
}

void BaseList::clean_up() {
    Node_ptr ptr{ nullptr };

    while (m_head != nullptr) {
        ptr = m_head->next;
        delete m_head;
        m_head = ptr;
    }

    m_tail = m_head;
    m_size = 0;
}


void BaseList::copy_data(const BaseList& rhs) {
    for (Node_ptr ptr = rhs.m_head; ptr != nullptr; ptr = ptr->next) {
        push_back(ptr->data);
    }
}


void BaseList::push_back(const int& elem) {
    if (empty()) {
        init_first_element(elem);
        return;
    }

    m_tail->next = new Node{ elem, m_tail, nullptr };
    m_tail = m_tail->next;
    ++m_size;
}


void BaseList::push_front(const int& elem) {
    if (empty()) {
        init_first_element(elem);
        return;
    }

    m_head->prev = new Node{ elem, nullptr, m_head };
    m_head = m_head->prev;
    ++m_size;
}


int& BaseList::back() const {
    return m_tail->data;
}


int& BaseList::front() const {
    return m_head->data;
}


void BaseList::pop_back() {
    if (size() <= 1) {
        clean_up();
        return;
    }

    m_tail = m_tail->prev;
    delete m_tail->next;
    m_tail->next = nullptr;
    --m_size;
}


void BaseList::pop_front() {
    if (size() <= 1) {
        clean_up();
        return;
    }

    m_head = m_head->next;
    delete m_head->prev;
    m_head->prev = nullptr;
    --m_size;
}
