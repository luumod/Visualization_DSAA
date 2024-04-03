#ifndef MYCANVAS_H
#define MYCANVAS_H

#include <QWidget>
#include <QGridLayout>
#include "graph_view.h"
#include "graph_implement.h"
#include <QFileDialog>
#include "Components/slidepage.h"

class GraphCanvas : public QWidget
{
    Q_OBJECT
private:
    QString canvasName;
    QString canvasDescription;

    SlidePage *settings;

    //For display
    MyGraphicsView *view;
    QHBoxLayout *mainLayout;
    QWidget *infoWidget;
    QLabel *pageName;

    AbstractGraph *g;
    int structure_type;
    int type;
    bool generateForest = false;

    void CreateSettings(int r);
    void Init();
    void SaveToFile(const QString &path);

public:
    enum { UDG = AbstractGraph::UDG, DG = AbstractGraph::DG };
    enum { AL = 128, AML = 256 };

    explicit GraphCanvas(int radius, QString name = "", QString desc = "", int structure = AL, int _type = UDG, QWidget *parent = nullptr);
    GraphCanvas(QTextStream &ts, int radius, QWidget *parent = nullptr);
    QString name(){return canvasName;}
    QString description(){return canvasDescription;}
    SlidePage *settingPage(){return settings;}

signals:
    void nameChanged(QString name);
    void descChanged(QString desc);
    void setDel(GraphCanvas* target);

private slots:
    void addVex(MyGraphicsVexItem*);
    void addArc(MyGraphicsLineItem*);

};

#endif // MYCANVAS_H
