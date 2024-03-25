#ifndef SORT_PAGE_H
#define SORT_PAGE_H

#include <QWidget>
#include <QGridLayout>
#include "slidepage.h"
#include <QFileDialog>

class SortPage : public QWidget
{
    Q_OBJECT
private:
    QString canvasName;
    QString canvasDescription;

    SlidePage *settings;

    //For display
    //MyGraphicsView *view;
    QHBoxLayout *mainLayout;
    QWidget *infoWidget;
    QLabel *pageName;

    //AbstractGraph *g;
    int structure_type;
    int type;
    bool generateForest = false;
public:
    enum { AL = 128, AML = 256 };

    explicit SortPage(int radius, QString name = "", QString desc = "", QWidget *parent = nullptr);
    SortPage(QTextStream &ts, int radius, QWidget *parent = nullptr);
    QString name(){return canvasName;}
    QString description(){return canvasDescription;}
};

#endif // MYCANVAS_H
