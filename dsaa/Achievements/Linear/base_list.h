#ifndef CORE_BASE_LIST_HPP_
#define CORE_BASE_LIST_HPP_

#include <QObject>

class BaseList : public QObject {

    Q_OBJECT
public:
    explicit BaseList(QObject* parent = nullptr);

    ~BaseList();

    bool empty() const;

    std::size_t size() const;

protected:
    struct Node;
    using Node_ptr = Node*;

    struct Node {
        int data{};
        Node_ptr prev{};
        Node_ptr next{};
    };

    Node_ptr m_head{ nullptr };
    Node_ptr m_tail{ nullptr };
    std::size_t m_size{};

    void init_first_element(const int& elem);

    void clean_up();

    void copy_data(const BaseList& rhs);

    void push_back(const int& elem);

    void push_front(const int& elem);

    int& back() const;

    int& front() const;

    void pop_front();

    void pop_back();
};

#endif  // CORE_BASE_LIST_HPP_
