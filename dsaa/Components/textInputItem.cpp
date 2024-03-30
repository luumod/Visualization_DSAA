#include "textInputItem.h"
#include <QLabel>
#include <QLineEdit>
#include <QGraphicsOpacityEffect>
#include <QTimer>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QValidator>

textInputItem::textInputItem(const QString& name, QWidget* parent) :
    QWidget(parent)
{
    QFont nameFont = QFont("Corbel", 12);
    QFontMetrics fm(nameFont);
    qreal height = fm.lineSpacing();
    itemName = new QLabel(this);
    itemName->setText(name);
    itemName->setFont(nameFont);
    itemName->setFixedHeight(height);
    itemName->setStyleSheet("color:#1c1c1c");

    QFont textFont = QFont("Corbel", 12);
    fm = QFontMetrics(textFont);
    editor = new QLineEdit(this);
    editor->setText("");
    editor->setFixedHeight(fm.lineSpacing());
    editor->setStyleSheet("color:#5c5c5c;background-color:#00000000;border-style:none;");
    editor->setReadOnly(true);
    editor->setFont(textFont);

    bgWidget = new QWidget(this);
    bgWidget->setStyleSheet("background-color:#00000000;border-radius:5px;");
    bgWidget->lower();
    bgWidget->show();

    indicator = new QWidget(this);
    indicator->setFixedHeight(4);
    indicator->setStyleSheet("background-color:#0078d4;border-radius:2px");

    opac = new QGraphicsOpacityEffect(this);
    opac->setOpacity(0);
    indicator->setGraphicsEffect(opac);

    this->setFixedHeight(itemName->height() + 10);

    connect(editor, &QLineEdit::returnPressed, this, [=]() {
        leaveEditEffect();
        onEditing = false;
        editor->setReadOnly(true);
        curText = editor->text();
        });
    connect(editor, &QLineEdit::editingFinished, this, [=]() {
        leaveEditEffect();
        onEditing = false;
        editor->setReadOnly(true);
        curText = editor->text();
        QTimer* delay = new QTimer(this);
        connect(delay, &QTimer::timeout, this, [=]() {mousePressed = false; });
        delay->setSingleShot(true);
        delay->start(10);
        mousePressed = false;
        emit textEdited(curText);
        });
}

void textInputItem::resizeEvent(QResizeEvent* event) {
    itemName->move(margin, this->height() / 2 - itemName->height() / 2);
    itemName->setFixedWidth(this->width() * 0.3 - margin - spacing);
    int width = QFontMetrics(editor->font()).size(Qt::TextSingleLine, editor->text()).width() + 3;
    if (!onEditing) {
        if (width > this->width() * 0.7 - margin)
            editor->resize(this->width() * 0.7 - margin, editor->height());
        else
            editor->resize(width, editor->height());
        editor->move(this->width() - margin - editor->width(), this->height() / 2 - editor->height() / 2);
        indicator->move(this->width() - margin, this->height() - 7);
    }
    else {
        editor->resize(this->width() * 0.7 - margin, editor->height());
        editor->move(this->width() * 0.3, this->height() / 2 - editor->height() / 2 - 2);
        indicator->move(this->width() * 0.3, this->height() - 7);
    }
    bgWidget->setFixedSize(this->size());
}

void textInputItem::enterEditEffect() {
    editor->setCursorPosition(editor->text().length());
    editor->setStyleSheet("color:#1c1c1c;background-color:#00000000;border-style:none;");
    QParallelAnimationGroup* group = new QParallelAnimationGroup(this);
    QPropertyAnimation* longer = new QPropertyAnimation(indicator, "geometry", this);
    longer->setStartValue(indicator->geometry());
    longer->setEndValue(QRectF(this->width() * 0.3, this->height() - 7, this->width() * 0.7 - margin, 4));
    longer->setDuration(500);
    longer->setEasingCurve(QEasingCurve::InOutExpo);
    QPropertyAnimation* fade = new QPropertyAnimation(opac, "opacity", this);
    fade->setStartValue(opac->opacity());
    fade->setEndValue(0.99);
    fade->setDuration(150);
    QPropertyAnimation* move = new QPropertyAnimation(editor, "geometry", this);
    move->setStartValue(editor->geometry());
    move->setEndValue(QRectF(this->width() * 0.3, this->height() / 2 - editor->height() / 2 - 2, this->width() * 0.7 - margin, editor->height()));
    move->setDuration(500);
    move->setEasingCurve(QEasingCurve::InOutExpo);
    group->addAnimation(longer);
    group->addAnimation(fade);
    group->addAnimation(move);
    group->start();
}

void textInputItem::leaveEditEffect() {
    editor->setCursorPosition(0);
    editor->setStyleSheet("color:#5c5c5c;background-color:#00000000;border-style:none;");
    QParallelAnimationGroup* group = new QParallelAnimationGroup(this);
    QPropertyAnimation* shorter = new QPropertyAnimation(indicator, "geometry", this);
    shorter->setStartValue(indicator->geometry());
    shorter->setEndValue(QRectF(this->width() - margin - 4, this->height() - 7, 4, 4));
    shorter->setDuration(500);
    shorter->setEasingCurve(QEasingCurve::InOutExpo);
    QPropertyAnimation* fade = new QPropertyAnimation(opac, "opacity", this);
    fade->setStartValue(opac->opacity());
    fade->setEndValue(0);
    fade->setDuration(350);
    QPropertyAnimation* move = new QPropertyAnimation(editor, "geometry", this);
    move->setStartValue(editor->geometry());
    int width = QFontMetrics(editor->font()).size(Qt::TextSingleLine, editor->text()).width() + 3;
    if (width > this->width() * 0.7 - margin)
        move->setEndValue(QRectF(this->width() * 0.3, this->height() / 2 - editor->height() / 2, this->width() * 0.7 - margin, editor->height()));
    else
        move->setEndValue(QRectF(this->width() - width - margin, this->height() / 2 - editor->height() / 2, width, editor->height()));
    move->setDuration(500);
    move->setEasingCurve(QEasingCurve::InOutExpo);
    group->addAnimation(shorter);
    group->addAnimation(fade);
    group->addAnimation(move);
    group->start();
}

void textInputItem::enterEvent(QEnterEvent* event) {
    bgWidget->setStyleSheet("border-radius:5px;background-color:#0a000000");
}

void textInputItem::leaveEvent(QEvent* event) {
    bgWidget->setStyleSheet("border-radius:5px;background-color:#00000000");
}

void textInputItem::mousePressEvent(QMouseEvent* event) {
    bgWidget->setStyleSheet("border-radius:5px;background-color:#1a000000");
    mousePressed = true;
}

void textInputItem::mouseReleaseEvent(QMouseEvent* event) {
    if (mousePressed) {
        bgWidget->setStyleSheet("border-radius:5px;background-color:#0a000000");
        if (onEditing) {
            leaveEditEffect();
            onEditing = false;
            curText = editor->text();
            editor->setReadOnly(true);
            emit textEdited(curText);
        }
        else {
            if (enabled) {
                enterEditEffect();
                editor->raise();
                onEditing = true;
                editor->setReadOnly(false);
                editor->setText(curText + "");
                editor->setFocus();
            }
        }
        mousePressed = false;
    }
}

QLineEdit* textInputItem::lineEditor(){ 
    return editor; 
}

QString textInputItem::value() {
    return editor->text(); 
}

void textInputItem::setValue(const QString& text) {
    editor->setText(text);
    editor->setCursorPosition(0);
    curText = text;
    int width = QFontMetrics(editor->font()).size(Qt::TextSingleLine, editor->text()).width() + 3;
    if (!onEditing) {
        if (width > this->width() * 0.7 - margin)
            editor->resize(this->width() * 0.7 - margin, editor->height());
        else
            editor->resize(width, editor->height());
        editor->move(this->width() - margin - editor->width(), this->height() / 2 - editor->height() / 2);
    }
    else {
        editor->resize(this->width() * 0.7 - margin, editor->height());
        editor->move(this->width() * 0.3, this->height() / 2 - editor->height() / 2 - 2);
    }
}

void textInputItem::setValidator(QValidator* vali) {
    editor->setValidator(vali); 
}

void textInputItem::setEnabled(bool enable) {
    enabled = enable; 
}