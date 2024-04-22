#ifndef GRAPH_VIEW_H
#define GRAPH_VIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QResizeEvent>
#include <QQueue>
#include <QFile>
#include <QTextStream>
#include <QScrollBar>
#include <QLabel>

//Header for MyVex class
#include <QGraphicsEllipseItem>
#include <QVector>

#include <QTimeLine>
#include <QEasingCurve>

class MyGraphicsNodeItem;
class StaqueView : public QGraphicsView {
    Q_OBJECT

private:
    enum mouseStates {
        NORMAL = 0b00000000,
        ON_HOVER = 0b00010000,
        ON_SELECTED = 0b00100000,
        ON_MOVING = 0b01000000
    };

    QGraphicsScene* myGraphicsScene;
    int type;
    int nodeID = 0;
    int mouseState = NORMAL;
    bool onRightPress = false;
    bool onMiddlePress = false;
    QPointF lastPos;

    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void resizeEvent(QResizeEvent* event) { this->setSceneRect(this->rect()); }

    void changeCursor();

public:
    int vexNum = 0;
    /* For Saving */
    QVector<MyGraphicsNodeItem*> vexes;

    /* for visit flag */
    bool hasVisitedItem = false;

    StaqueView(QWidget* parent = nullptr);

    MyGraphicsNodeItem* selectedVex();

    void RemoveVex(MyGraphicsNodeItem* vex);
    void HideUnvisited();
    void ShowUnvisited();

    void setType(int _type) { type = _type; }

signals:
    void mouseMoved(QPointF position);
    void mouseLeftClicked(QPointF position);
    void mouseRightClicked(QPointF position);
    void mouseReleased();

public slots:
    void setHover(bool in = true);
};



#endif // GRAPH_VIEW_H
