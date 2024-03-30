#include "textButton.h"
#include <QLabel>
#include <QPropertyAnimation>

textButton::textButton(QString text, QWidget* parent, qreal ratio) :
    QWidget(parent)
{
    QFont textFont = QFont("Corbel", 10);
    QFontMetrics fm(textFont);
    qreal height = fm.lineSpacing();
    btnText = new QLabel(this);
    btnText->setText(text);
    btnText->setFont(textFont);
    btnText->setFixedHeight(height);
    btnText->setFixedWidth(fm.size(Qt::TextSingleLine, text).width() + 2);
    btnText->setStyleSheet("color:#1c1c1c");
    btnText->setAlignment(Qt::AlignCenter);

    bgWidget = new QWidget(this);
    bgWidget->setStyleSheet("background-color:" + defaultColor + ";border-radius:5px;");

    this->setFixedHeight(btnText->height() / ratio);
}

textButton::textButton(QString text, QString defC, QString hoverC, QString pressedC, QWidget* parent, qreal ratio) :
    QWidget(parent),
    defaultColor(defC),
    hoverColor(hoverC),
    pressedColor(pressedC)
{
    QFont textFont = QFont("Corbel", 10);
    QFontMetrics fm(textFont);
    qreal height = fm.lineSpacing();
    btnText = new QLabel(this);
    btnText->setText(text);
    btnText->setFont(textFont);
    btnText->setFixedHeight(height);
    btnText->setFixedWidth(fm.size(Qt::TextSingleLine, text).width() + 2);
    btnText->setStyleSheet("color:#1c1c1c");
    btnText->setAlignment(Qt::AlignCenter);

    bgWidget = new QWidget(this);
    bgWidget->setStyleSheet("background-color:" + defaultColor + ";border-radius:5px;");

    this->setFixedHeight(btnText->height() / ratio);
}

void textButton::resizeEvent(QResizeEvent* event) {
    bgWidget->resize(this->size());
    btnText->move(this->width() / 2 - btnText->width() / 2, this->height() / 2 - btnText->height() / 2);
}

void textButton::enterEvent(QEnterEvent* event) {
    bgWidget->setStyleSheet("background-color:" + hoverColor + ";border-radius:5px;");
}

void textButton::leaveEvent(QEvent* event) {
    bgWidget->setStyleSheet("background-color:" + defaultColor + ";border-radius:5px;");
    if (mousePressed) {
        bgWidget->setStyleSheet("background-color:" + pressedColor + ";border-radius:5px;");
        QPropertyAnimation* enlarge = new QPropertyAnimation(bgWidget, "geometry", this);
        enlarge->setStartValue(bgWidget->geometry());
        enlarge->setEndValue(QRect(0, 0, this->width(), this->height()));
        enlarge->setDuration(150);
        enlarge->setEasingCurve(QEasingCurve::OutBounce);
        enlarge->start();
        mousePressed = false;
    }
}

void textButton::mousePressEvent(QMouseEvent* event) {
    bgWidget->setStyleSheet("background-color:" + pressedColor + ";border-radius:5px;");
    QPropertyAnimation* shrink = new QPropertyAnimation(bgWidget, "geometry", this);
    shrink->setStartValue(bgWidget->geometry());
    shrink->setEndValue(QRect(0.05 * this->width(), 0.05 * this->height(), this->width() * 0.9, this->height() * 0.9));
    shrink->setDuration(100);
    shrink->setEasingCurve(QEasingCurve::OutBack);
    shrink->start();
    mousePressed = true;
    setFocus();
}

void textButton::mouseReleaseEvent(QMouseEvent* event) {
    if (mousePressed) {
        bgWidget->setStyleSheet("background-color:" + hoverColor + ";border-radius:5px;");
        QPropertyAnimation* enlarge = new QPropertyAnimation(bgWidget, "geometry", this);
        enlarge->setStartValue(bgWidget->geometry());
        enlarge->setEndValue(QRect(0, 0, this->width(), this->height()));
        enlarge->setDuration(150);
        enlarge->setEasingCurve(QEasingCurve::OutBounce);
        enlarge->start();
        mousePressed = false;
        emit clicked();
    }
}
