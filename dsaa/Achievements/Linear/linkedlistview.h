#ifndef LINKED_LIST_VIEW_H_
#define LINKED_LIST_VIEW_H_

#include <QWidget>

class DoublyLinkedList;
class QPaintEvent;
class LinkedListView : public QWidget {
    Q_OBJECT

public:
    LinkedListView(QWidget* parent = nullptr);
    ~LinkedListView();
    DoublyLinkedList* listObj() { return base_list_obj; }

    void updateColors(const QString& node, const QString& arrow, const QString& text);
    void updateSettings(int nodeWidth, int nodeHeight, int arrowSize, int textSpace, int maxNodesPerRow, int row_spacing);
    void resetSettings();
protected:
    void paintEvent(QPaintEvent* event)override;

private:
    bool isFinished{ false };

    DoublyLinkedList* base_list_obj{ nullptr };
    QPainter* painter{ nullptr };
};

#endif