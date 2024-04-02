#include "MainCanvas.h"
#include "SortObject.h"
#include <QPaintEvent>
#include <QPainter>

MainCanvas::MainCanvas(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground, true);

    this->setStyleSheet("border:1px solid #cfcfcf; border-radius: 10px");
    this->setAutoFillBackground(true);
    palette.setColor(QPalette::Window, Qt::white);
    setPalette(palette);
}

int MainCanvas::getSortType() const
{
    return sortType;
}

void MainCanvas::setSortObject(int type, SortObject *obj)
{
    if (sortType == type) {
        return;
    }
    if (sortObj) {
        sortObj->deleteLater();
        sortObj = nullptr;
    }

    sortType = type;
    sortObj = obj;

    if (sortObj) {
        connect(sortObj, &SortObject::updateToDraw, this, [this]{
            update();
        });
        connect(sortObj, &SortObject::runFlagChanged, this, &MainCanvas::runFlagChanged);
    }
    update();
}

void MainCanvas::sort(int count, int interval)
{
    if (sortObj) {
        
        sortObj->sort(count, interval);
    }
}

void MainCanvas::stop()
{
    if (sortObj) {
        sortObj->stop();
    }
}

void MainCanvas::paintEvent(QPaintEvent *event)
{
    event->accept();

    QPainter painter(this);
    setPalette(palette);

    if (sortObj) {
        sortObj->draw(&painter, width(), height());
    }
}
