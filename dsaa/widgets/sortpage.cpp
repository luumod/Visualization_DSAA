#include "sortpage.h"

SortPage::SortPage(int radius, QString name, QString desc, QWidget *parent) :
    QWidget(parent),
    canvasName(name),
    canvasDescription(desc)
{
    /* create canvas */
    mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(mainLayout);

    this->setFocusPolicy(Qt::ClickFocus);
}

SortPage::SortPage(QTextStream &ts, int radius, QWidget *parent) :
    QWidget(parent)
{
    canvasName = ts.readLine();
    canvasDescription = ts.readLine();
    ts >> structure_type >> type;

    /* create canvas */
    mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(mainLayout);
    


    this->setFocusPolicy(Qt::ClickFocus);

}
