#ifndef CORE_BASE_LIST_H_
#define CORE_BASE_LIST_H_

#include <QObject>

class QPainter;
class BaseList : public QObject {
    Q_OBJECT

public:
    explicit BaseList(QObject* parent = nullptr);

    ~BaseList();

    bool empty() const;

    std::size_t size() const;

public:
    virtual void draw(QPainter* painter, int width, int height) = 0;

public:
    struct Node {
        int data{};
        Node* prev{};
        Node* next{};
    };
    using Node_ptr = Node*;

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

#endif  // CORE_BASE_LIST_H_
