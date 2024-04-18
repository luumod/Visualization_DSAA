#include "spinbox.h"
#include "common.h"
#include <QFont>
#include <QFontMetrics>
#include <QTimer>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>

SpinBox::SpinBox(const QString& name, QWidget* parent) :
    QWidget(parent), minValue(0), maxValue(100), curValue(0)
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
    editor->setFixedHeight(fm.lineSpacing());
    editor->setStyleSheet("color:#5c5c5c;background-color:#00000000;border-style:none;");
    editor->setFont(textFont);
    editor->setReadOnly(true);

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

    upButton = new QPushButton(this);
    upButton->setFixedSize(16, 16);
    upButton->setStyleSheet("QPushButton{background-color:#00000000;border-style:none;} QPushButton:pressed{background-color:#1a000000;}");
    upButton->setIcon(QIcon(ICON_FILE "up-arrow.png"));
    connect(upButton, &QPushButton::clicked, this, &SpinBox::onUpButtonClicked);

    downButton = new QPushButton(this);
    downButton->setFixedSize(16, 16);
    downButton->setStyleSheet("QPushButton{background-color:#00000000;border-style:none;} QPushButton:pressed{background-color:#1a000000;}");
    downButton->setIcon(QIcon(ICON_FILE "down-arrow.png"));
    connect(downButton, &QPushButton::clicked, this, &SpinBox::onDownButtonClicked);

    this->setFixedHeight(itemName->height() + 10);

    updateEditor();
}

void SpinBox::resizeEvent(QResizeEvent* event)
{
    itemName->move(margin, this->height() / 2 - itemName->height() / 2);
    itemName->setFixedWidth(this->width() * 0.3 - margin - spacing);

    editor->resize(this->width() * 0.4 - margin, editor->height());
    editor->move(this->width() * 0.3, this->height() / 2 - editor->height() / 2);

    upButton->move(this->width() * 0.7, this->height() / 2 - upButton->height());
    downButton->move(this->width() * 0.7, this->height() / 2);

    indicator->move(this->width() * 0.3, this->height() - 7);
    indicator->resize(this->width() * 0.4 - margin, 4);

    bgWidget->setFixedSize(this->size());
}

void SpinBox::enterEditEffect()
{
    QParallelAnimationGroup* group = new QParallelAnimationGroup(this);
    QPropertyAnimation* fade = new QPropertyAnimation(opac, "opacity", this);
    fade->setStartValue(opac->opacity());
    fade->setEndValue(0.99);
    fade->setDuration(150);
    group->addAnimation(fade);
    group->start();
}

void SpinBox::leaveEditEffect()
{
    QParallelAnimationGroup* group = new QParallelAnimationGroup(this);
    QPropertyAnimation* fade = new QPropertyAnimation(opac, "opacity", this);
    fade->setStartValue(opac->opacity());
    fade->setEndValue(0);
    fade->setDuration(350);
    group->addAnimation(fade);
    group->start();
}

void SpinBox::enterEvent(QEnterEvent* event)
{
    bgWidget->setStyleSheet("border-radius:5px;background-color:#0a000000");
}

void SpinBox::leaveEvent(QEvent* event)
{
    bgWidget->setStyleSheet("border-radius:5px;background-color:#00000000");
}

void SpinBox::mousePressEvent(QMouseEvent* event)
{
    bgWidget->setStyleSheet("border-radius:5px;background-color:#1a000000");
    mousePressed = true;
}

void SpinBox::mouseReleaseEvent(QMouseEvent* event)
{
    if (mousePressed) {
        bgWidget->setStyleSheet("border-radius:5px;background-color:#0a000000");
        mousePressed = false;
    }
}

void SpinBox::onUpButtonClicked()
{
    if (enabled && curValue < maxValue) {
        curValue++;
        updateEditor();
        enterEditEffect();
        emit valueChanged(curValue);
        QTimer::singleShot(500, this, &SpinBox::leaveEditEffect);
    }
}

void SpinBox::onDownButtonClicked()
{
    if (enabled && curValue > minValue) {
        curValue--;
        updateEditor();
        enterEditEffect();
        emit valueChanged(curValue);
        QTimer::singleShot(500, this, &SpinBox::leaveEditEffect);
    }
}

void SpinBox::setValue(int value)
{
    if (value >= minValue && value <= maxValue) {
        curValue = value;
        updateEditor();
    }
}

int SpinBox::value() const
{
    return curValue;
}

void SpinBox::setRange(int min, int max)
{
    minValue = min;
    maxValue = max;
    if (curValue < minValue)
        curValue = minValue;
    else if (curValue > maxValue)
        curValue = maxValue;
    updateEditor();
}

void SpinBox::setEnabled(bool enable)
{
    enabled = enable;
    upButton->setEnabled(enable);
    downButton->setEnabled(enable);
}

void SpinBox::updateEditor()
{
    editor->setText(QString::number(curValue));
}