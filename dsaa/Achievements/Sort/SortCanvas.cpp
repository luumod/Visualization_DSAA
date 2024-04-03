#include "SortCanvas.h"
#include "SortObject.h"
#include <QPaintEvent>
#include <QPainter>

SortCanvas::SortCanvas(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground, true);

    this->setStyleSheet("border:1px solid #cfcfcf; border-radius: 10px");
    this->setAutoFillBackground(true);
    palette.setColor(QPalette::Window, Qt::white);
    setPalette(palette);
}

int SortCanvas::getSortType() const
{
    return sortType;
}

void SortCanvas::setSortObject(int type, SortObject *obj)
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
        connect(sortObj, &SortObject::runFlagChanged, this, &SortCanvas::runFlagChanged);
    }
    update();
}

void SortCanvas::sort(int count, int interval)
{
    if (sortObj) {
        
        sortObj->sort(count, interval);
    }
}

void SortCanvas::stop()
{
    if (sortObj) {
        sortObj->stop();
    }
}

void SortCanvas::paintEvent(QPaintEvent *event)
{
    event->accept();

    QPainter painter(this);
    setPalette(palette);

    if (sortObj) {
        sortObj->draw(&painter, width(), height());
    }
}
