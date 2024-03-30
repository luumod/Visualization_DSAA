#include "singleSelectGroup.h"
#include <QLabel>
#include <QGraphicsOpacityEffect>
#include <QVBoxLayout>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>

selectionItem::selectionItem(QString name, QString info, QWidget* parent) :
    QWidget(parent) {
    /* set labels */
    QFont titleFont = QFont("Corbel", 13);
    QFontMetrics fm(titleFont);
    qreal height = fm.lineSpacing();
    title = new QLabel(this);
    title->setText(name);
    title->setFont(titleFont);
    title->setMinimumHeight(height);
    title->setStyleSheet("color:#2c2c2c");
    title->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    QFont descFont = QFont("Corbel Light", 11);
    fm = QFontMetrics(descFont);
    height = fm.lineSpacing();
    description = new QLabel(this);
    description->setText(info);
    description->setFont(descFont);
    description->setMinimumHeight(height);
    description->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    description->setStyleSheet("color:#707070");

    indicator = new QWidget(this);

    /* set minimum height and layout */
    setFixedHeight(title->height() + (info == "" ? 0 : description->height() + 5));
    indicator->resize(6, 0.4 * this->height());
    indicator->move(4, 0.3 * this->height());
    indicator->setStyleSheet("border-radius:3px;background-color:#0078D4");
    opac = new QGraphicsOpacityEffect(indicator);
    opac->setOpacity(0);
    indicator->setGraphicsEffect(opac);

    QVBoxLayout* contentLayout = new QVBoxLayout(this);
    contentLayout->setContentsMargins(20, 0, 0, 0);
    contentLayout->setSpacing(2);
    this->setLayout(contentLayout);
    contentLayout->addWidget(title);
    if (info != "")
        contentLayout->addWidget(description);
    contentLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    /* set background widget */
    bgWidget = new QWidget(this);
    bgWidget->resize(this->size());
    bgWidget->setStyleSheet("border-radius:5px;background-color:#00000000");
    bgWidget->lower();
    bgWidget->show();

    this->setMouseTracking(true);
}

void selectionItem::enterEvent(QEnterEvent* event) {
    bgWidget->setStyleSheet("border-radius:5px;background-color:#0a000000");
    QParallelAnimationGroup* enter = new QParallelAnimationGroup(this);
    //Control the indication bar animation effect.
    QPropertyAnimation* longer = new QPropertyAnimation(indicator, "geometry", this);
    longer->setStartValue(indicator->geometry());
    longer->setEndValue(QRectF(4, 0.25 * this->height(), 6, this->height() * 0.5));
    longer->setDuration(150);
    longer->setEasingCurve(QEasingCurve::OutBack);
    //Control the opacity of the other area.
    QPropertyAnimation* fadeIn = new QPropertyAnimation(opac, "opacity", this);
    fadeIn->setStartValue(opac->opacity());
    fadeIn->setEndValue(0.99);
    fadeIn->setDuration(100);
    enter->addAnimation(longer);
    enter->addAnimation(fadeIn);
    enter->start();
}

void selectionItem::leaveEvent(QEvent* event) {
    bgWidget->setStyleSheet("border-radius:5px;background-color:#00000000");
    QParallelAnimationGroup* leave = new QParallelAnimationGroup(this);
    QPropertyAnimation* shorter = new QPropertyAnimation(indicator, "geometry", this);
    shorter->setStartValue(indicator->geometry());
    shorter->setEndValue(QRectF(4, 0.3 * this->height(), 6, this->height() * 0.4));
    shorter->setDuration(150);
    shorter->setEasingCurve(QEasingCurve::OutBack);
    QPropertyAnimation* fadeOut = new QPropertyAnimation(opac, "opacity", this);
    fadeOut->setStartValue(opac->opacity());
    fadeOut->setEndValue(onSelected ? 0.99 : 0);
    fadeOut->setDuration(100);
    leave->addAnimation(shorter);
    leave->addAnimation(fadeOut);
    leave->start();

    if (mousePressed)
        mousePressed = false;
}

void selectionItem::mousePressEvent(QMouseEvent* event) {
    bgWidget->setStyleSheet("border-radius:5px;background-color:#1a000000");
    QPropertyAnimation* shorter = new QPropertyAnimation(indicator, "geometry", this);
    shorter->setStartValue(indicator->geometry());
    shorter->setEndValue(QRectF(4, 0.4 * this->height(), 6, this->height() * 0.2));
    shorter->setDuration(100);
    shorter->setEasingCurve(QEasingCurve::OutBack);
    shorter->start();

    mousePressed = true;
}

void selectionItem::mouseReleaseEvent(QMouseEvent* event) {
    if (mousePressed) {
        bgWidget->setStyleSheet("border-radius:5px;background-color:#0a000000");
        QPropertyAnimation* longer = new QPropertyAnimation(indicator, "geometry", this);
        longer->setStartValue(indicator->geometry());
        longer->setEndValue(QRectF(4, 0.25 * this->height(), 6, this->height() * 0.5));
        longer->setDuration(150);
        longer->setEasingCurve(QEasingCurve::OutBack);
        longer->start();

        if (!onSelected) {
            onSelected = true;
            title->setStyleSheet("color:#005FB8");
            description->setStyleSheet("color:#3a8fb7");
            emit selected(this);
            setFocus();
        }
        mousePressed = false;
    }
}

void selectionItem::resizeEvent(QResizeEvent* event) {
    bgWidget->resize(this->size());
}

void selectionItem::Select() {
    if (!onSelected) {
        onSelected = true;
        title->setStyleSheet("color:#005FB8");
        description->setStyleSheet("color:#3a8fb7");
        indicator->setGeometry(4, 0.5 * this->height(), 6, 0);

        QParallelAnimationGroup* sel = new QParallelAnimationGroup(this);
        QPropertyAnimation* longer = new QPropertyAnimation(indicator, "geometry", this);
        longer->setStartValue(indicator->geometry());
        longer->setEndValue(QRectF(4, 0.3 * this->height(), 6, this->height() * 0.4));
        longer->setDuration(150);
        longer->setEasingCurve(QEasingCurve::OutBack);
        QPropertyAnimation* fadeIn = new QPropertyAnimation(opac, "opacity", this);
        fadeIn->setStartValue(opac->opacity());
        fadeIn->setEndValue(0.99);
        fadeIn->setDuration(100);
        sel->addAnimation(longer);
        sel->addAnimation(fadeIn);
        sel->start();

        emit selected(this);
    }
}

void selectionItem::Deselect() {
    if (onSelected) {
        onSelected = false;
        title->setStyleSheet("color:#2c2c2c");
        description->setStyleSheet("color:#707070");

        QPropertyAnimation* fadeOut = new QPropertyAnimation(opac, "opacity", this);
        fadeOut->setStartValue(opac->opacity());
        fadeOut->setEndValue(0);
        fadeOut->setDuration(100);
        fadeOut->start();
    }
}

void selectionItem::setTitle(QString titleText) {
    title->setText(titleText);
}

void selectionItem::setDescription(QString descText) {
    description->setText(descText);
}

singleSelectGroup::singleSelectGroup(QString name, QWidget* parent) :
    QWidget(parent) {
    QFont titleFont = QFont("Corbel", 16);
    QFontMetrics fm(titleFont);
    qreal height = fm.lineSpacing();
    groupName = new QLabel(this);
    groupName->setMinimumHeight(height);
    groupName->setFont(titleFont);
    groupName->setText(name);

    QWidget* spacingLine = new QWidget(this);
    spacingLine->setFixedHeight(1);
    spacingLine->setStyleSheet("background-color:#0a000000");

    this->setFixedHeight(groupName->height() + middleSpacing + 1 + bottomSpacing);

    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 0, 10, bottomSpacing);
    mainLayout->setSpacing(middleSpacing);
    mainLayout->addWidget(groupName);
    mainLayout->addWidget(spacingLine);
}

void singleSelectGroup::AddItem(selectionItem* item) {
    selections.push_back(item);
    this->setFixedHeight(this->height() + middleSpacing + item->height());
    mainLayout->addWidget(item);
    if (selectedID == -1) {
        item->Select();
        selectedID = 0;
    }
    connect(item, SIGNAL(selected(selectionItem*)), this, SLOT(changeSelection(selectionItem*)));
    emit itemChange();
}

void singleSelectGroup::RemoveItem(selectionItem* item) {
    int id = selections.indexOf(item);
    if (id < 0)  return;
    selections.erase(selections.begin() + id);
    mainLayout->removeWidget(item);
    item->setParent(nullptr);
    item->deleteLater();
    this->setFixedHeight(this->height() - middleSpacing - item->height());
    if (selections.size() == 0)
        selectedID = -1;
    else {
        selectedID = id < selections.size() ? id : id - 1;
        selections[selectedID]->Select();
    }
    emit selectedItemChange(selectedID);
    emit itemChange();
}

void singleSelectGroup::SetSelection(selectionItem* item) {
    int id = selections.indexOf(item);
    selections[id]->Select();
}

void singleSelectGroup::changeSelection(selectionItem* item) {
    int id = selections.indexOf(item);
    for (int i = 0; i < selections.size(); i++) {
        if (i == id) continue;
        selections[i]->Deselect();
    }
    selectedID = id;
    emit selectedItemChange(id);
}