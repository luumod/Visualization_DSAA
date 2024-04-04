#include "SortCanvas.h"
#include "SortObject.h"
#include "Components/horizontalValueAdjuster.h"
#include "Components/textButton.h"
#include "Components/singleSelectGroup.h"
#include "Components/textInputItem.h"
#include "Components/customScrollContainer.h"
#include "Components/slidepage.h"
#include <QPaintEvent>
#include <QPainter>
#include <QHBoxLayout>
#include <QTimer>

SortCanvas::SortCanvas(int radius, QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground, true);

    mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(mainLayout);

    view = new QWidget;
    view->setStyleSheet("border:1px solid #cfcfcf; border-radius: 10px");
    view->setAutoFillBackground(true);
    palette.setColor(QPalette::Window, Qt::white);
    view->setPalette(palette);
    mainLayout->addWidget(view);

    this->setFocusPolicy(Qt::ClickFocus);


    CreateSettings(radius);
}

void SortCanvas::CreateSettings(int radius){
    /* create settings page */
    settings = new SlidePage(radius, "SETTINGS", this->parentWidget());
    singleSelectGroup* structureSetting = new singleSelectGroup("Structure", this);
    selectionItem* setAL = new selectionItem("AL", "Adjacent list structure", this);
    selectionItem* setAML = new selectionItem("AML", "Adjacent multiple list", this);
    structureSetting->AddItem(setAL);
    structureSetting->AddItem(setAML);

    singleSelectGroup* dirSetting = new singleSelectGroup("Mode", this);
    selectionItem* setDG = new selectionItem("DG", "Directed graph", this);
    selectionItem* setUDG = new selectionItem("UDG", "Undirected graph", this);
    dirSetting->AddItem(setDG);
    dirSetting->AddItem(setUDG);
    
    singleSelectGroup* dfsSetting = new singleSelectGroup("Traverse Mode", this);
    selectionItem* setGenerateTree = new selectionItem("Tree", "Generate tree", this);
    selectionItem* setGenerateForest = new selectionItem("Forest", "Generate forest", this);
    dfsSetting->AddItem(setGenerateTree);
    dfsSetting->AddItem(setGenerateForest);
    
    QWidget* whiteSpace = new QWidget(this);
    whiteSpace->setFixedHeight(30);

    horizontalValueAdjuster* aniSpeed = new horizontalValueAdjuster("Animation speed", 0.1, 20, 0.1, this);
    aniSpeed->setValue(1.0);

    textInputItem* rename = new textInputItem("Name", this);
    rename->setValue(canvasName);

    textInputItem* redesc = new textInputItem("Detail", this);
    redesc->setValue(canvasDescription);
    textButton* hideBtn = new textButton("Hide Unvisited Items", this);

    textButton* showBtn = new textButton("Show Unvisited Items", this);
    QWidget* whiteSpace2 = new QWidget(this);
    whiteSpace2->setFixedHeight(30);
    textButton* saveBtn = new textButton("Save to file", this);

    textButton* delBtn = new textButton("Delete", "#0acb1b45", "#1acb1b45", "#2acb1b45", this);

    settings->AddContent(delBtn);
    settings->AddContent(saveBtn);
    settings->AddContent(whiteSpace2);
    settings->AddContent(showBtn);
    settings->AddContent(hideBtn);
    settings->AddContent(dfsSetting);
    settings->AddContent(dirSetting);
    settings->AddContent(structureSetting);
    settings->AddContent(aniSpeed);
    settings->AddContent(whiteSpace);
    settings->AddContent(redesc);
    settings->AddContent(rename);
    settings->show();
}

void SortCanvas::Init(){

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
