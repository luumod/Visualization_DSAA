#ifndef SINGLE_SELECT_GROUP
#define SINGLE_SELECT_GROUP

#include <QWidget>

class QLabel;
class QGraphicsOpacityEffect;
class QVBoxLayout;
class selectionItem : public QWidget {
    Q_OBJECT

private:
    QLabel* title;
    QLabel* description;
    QWidget* indicator;
    QWidget* mainContent;
    QWidget* bgWidget;
    QGraphicsOpacityEffect* opac;
    bool onSelected = false;
    bool mousePressed = false;

    void enterEvent(QEnterEvent* event);
    void leaveEvent(QEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void resizeEvent(QResizeEvent* event);

public:
    selectionItem(QString name, QString info = "", QWidget* parent = nullptr);
    void Select();
    void Deselect();
    void setTitle(QString titleText);
    void setDescription(QString descText);

signals:
    void selected(selectionItem* item);
};

class singleSelectGroup : public QWidget {
    Q_OBJECT

private:
    const int middleSpacing = 5;
    const int bottomSpacing = 30;
    QLabel* groupName;
    QVBoxLayout* mainLayout;
    int selectedID = -1;
    QVector<selectionItem*> selections;

public:
    singleSelectGroup(QString name = "", QWidget* parent = nullptr);
    void AddItem(selectionItem* item);
    void RemoveItem(selectionItem* item);
    void SetSelection(selectionItem* item);
    qreal value() { return selectedID; }

signals:
    void selectedItemChange(int selectID);
    void itemChange();

private slots:
    void changeSelection(selectionItem* item);
};

#endif