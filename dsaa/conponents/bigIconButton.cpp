#include "bigIconButton.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPropertyAnimation>

bigIconButton::bigIconButton(const QString& iconPath, const QString& description, int radius, QWidget* parent) :
    QWidget(parent),
    cornerRadius(radius)
{
    iconImg = new QPixmap(iconPath);

    /* set icon label and text label */
    icon = new QLabel(this);
    icon->setPixmap(*iconImg);
    icon->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    icon->setAlignment(Qt::AlignCenter);

    QFont textFont = QFont("Corbel", 13);
    QFontMetrics fm(textFont);
    text = new QLabel(this);
    text->setFont(textFont);
    text->setText(description);
    text->setWordWrap(true);
    text->setMinimumHeight(fm.lineSpacing());
    text->setAlignment(Qt::AlignCenter);

    /* set indicator */
    indicator = new QWidget(this);
    indicator->resize(6, 6);
    indicator->move(this->width() - 3, this->height() - 21);
    indicator->setStyleSheet("border-radius:3px;background-color:#afafaf");

    /* set background */
    bgWidget = new QWidget(this);
    bgWidget->resize(this->size());
    radiusStyle = QString::asprintf("border-radius:%dpx;", cornerRadius);
    bgWidget->setStyleSheet(radiusStyle + "background-color:#04000000");
    bgWidget->lower();
    bgWidget->show();

    /* set layout */
    QVBoxLayout* layout = new QVBoxLayout(this);
    this->setLayout(layout);
    layout->setContentsMargins(15, 35, 15, 35);
    layout->setSpacing(15);
    layout->addWidget(icon);
    layout->addWidget(text);
    layout->setAlignment(Qt::AlignCenter);

    this->setMinimumHeight(200);
}

void bigIconButton::resizeEvent(QResizeEvent* event) {
    bgWidget->setFixedSize(this->size());
    if (onSelected) {
        indicator->resize(this->width() * 0.1, 6);
        indicator->move(this->width() * 0.45, this->height() - 21);
    }
    else {
        indicator->resize(this->width() * 0.1, 6);
        indicator->move(this->width() * 0.45, this->height() - 21);
    }
}

void bigIconButton::enterEvent(QEnterEvent* event) {
    bgWidget->setStyleSheet(radiusStyle + "background-color:#0a0078D4");
    QPropertyAnimation* longer = new QPropertyAnimation(indicator, "geometry", this);
    longer->setStartValue(indicator->geometry());
    longer->setEndValue(QRectF(this->width() * 0.2, this->height() - 21, this->width() * 0.6, 6));
    longer->setDuration(150);
    longer->setEasingCurve(QEasingCurve::OutBack);
    longer->start();

    indicator->setStyleSheet("border-radius:3px;background-color:#0078d4");
}

void bigIconButton::leaveEvent(QEvent* event) {
    bgWidget->setStyleSheet(radiusStyle + "background-color:#04000000");
    QPropertyAnimation* shorter = new QPropertyAnimation(indicator, "geometry", this);
    shorter->setStartValue(indicator->geometry());
    if (!onSelected)
        shorter->setEndValue(QRectF(this->width() * 0.45, this->height() - 21, this->width() * 0.1, 6));
    else
        shorter->setEndValue(QRectF(this->width() * 0.3, this->height() - 21, this->width() * 0.4, 6));
    shorter->setDuration(250);
    shorter->setEasingCurve(QEasingCurve::OutBack);
    shorter->start();

    if (!onSelected)
        indicator->setStyleSheet("border-radius:3px;background-color:#afafaf");

    if (mousePressed)
        mousePressed = false;
}

void bigIconButton::mousePressEvent(QMouseEvent* event) {
    bgWidget->setStyleSheet(radiusStyle + "background-color:#1a0078D4");
    QPropertyAnimation* shorter = new QPropertyAnimation(indicator, "geometry", this);
    shorter->setStartValue(indicator->geometry());
    shorter->setEndValue(QRectF(this->width() * 0.4, this->height() - 21, this->width() * 0.2, 6));
    shorter->setDuration(100);
    shorter->setEasingCurve(QEasingCurve::OutBack);
    shorter->start();

    mousePressed = true;
}

void bigIconButton::mouseReleaseEvent(QMouseEvent* event) {
    if (mousePressed) {
        bgWidget->setStyleSheet(radiusStyle + "background-color:#0a0078D4");
        QPropertyAnimation* longer = new QPropertyAnimation(indicator, "geometry", this);
        longer->setStartValue(indicator->geometry());
        longer->setEndValue(QRectF(this->width() * 0.2, this->height() - 21, this->width() * 0.6, 6));
        longer->setDuration(150);
        longer->setEasingCurve(QEasingCurve::OutBack);
        longer->start();

        mousePressed = false;
        emit clicked();
        if (selectable) {
            emit selected();
            onSelected = true;
        }
    }
}

void bigIconButton::setScale(qreal scale) {
    iconImg = new QPixmap(iconImg->scaled(iconImg->size() * scale, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    icon->setPixmap(*iconImg);
}