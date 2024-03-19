#include "horizontalValueAdjuster.h"
#include <QLabel>
#include <QSlider>
#include <QHBoxLayout>

horizontalValueAdjuster::horizontalValueAdjuster(QString name, qreal min, qreal max, qreal step, QWidget* parent) :
    QWidget(parent),
    curValue(min),
    minValue(min),
    maxValue(max),
    stepValue(step)
{
    QFont titleFont = QFont("Corbel", 16);
    QFontMetrics fm(titleFont);
    qreal height = fm.lineSpacing();
    title = new QLabel(this);
    title->setMinimumHeight(height);
    title->setFont(titleFont);
    title->setText(name);

    QWidget* spacingLine = new QWidget(this);
    spacingLine->setFixedHeight(1);
    spacingLine->setStyleSheet("background-color:#0a000000");

    slider = new QSlider(Qt::Horizontal, this);
    slider->setMinimum(0);
    slider->setMaximum((max - min) / step + 1);
    slider->setPageStep(1);
    QString grooveStyle = "QSlider::groove:horizontal{height:6px; border-radius:3px;} ";
    QString sliderStyle = "QSlider::handle:horizontal{width:12px; margin-bottom:-3px; margin-top:-3px; background:#c2c2c2; border-radius:6px;} ";
    QString sliderHStyle = "QSlider::handle:horizontal:hover{width:12px; margin-bottom:-3px; margin-top:-3px; background:#3a8fb7; border-radius:6px;} ";
    QString sliderPStyle = "QSlider::handle:horizontal:pressed{width:12px; margin-bottom:-3px; margin-top:-3px; background:#005fb8; border-radius:6px;} ";
    QString subStyle = "QSlider::sub-page:horizontal{background:#0078D4; border-radius:3px} ";
    QString addStyle = "QSlider::add-page:horizontal{background:#1a000000; border-radius:3px} ";
    slider->setStyleSheet(grooveStyle + sliderStyle + sliderHStyle + sliderPStyle + subStyle + addStyle);


    QFont valueFont = QFont("Corbel", 13);
    fm = QFontMetrics(titleFont);
    height = fm.lineSpacing();
    valueLabel = new QLabel(this);
    valueLabel->setMinimumHeight(height);
    valueLabel->setFont(valueFont);
    valueLabel->setText(QString::asprintf("%g", min));
    valueLabel->setMinimumWidth(30);
    valueLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    valueLabel->setStyleSheet("margin-bottom:5px");

    QWidget* content = new QWidget(this);
    content->setMinimumHeight(valueLabel->height() < slider->height() ? valueLabel->height() : slider->height());
    QHBoxLayout* contentLayout = new QHBoxLayout(content);
    contentLayout->setAlignment(Qt::AlignVCenter);
    content->setLayout(contentLayout);
    contentLayout->setContentsMargins(0, 0, 0, 0);
    contentLayout->setSpacing(10);
    contentLayout->addWidget(valueLabel);
    contentLayout->addWidget(slider);

    this->setMinimumHeight(title->height() + 2 * middleSpacing + 1 + content->height() + bottomSpacing);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);
    mainLayout->setContentsMargins(10, 0, 10, bottomSpacing);
    mainLayout->setSpacing(middleSpacing);
    mainLayout->addWidget(title);
    mainLayout->addWidget(spacingLine);
    mainLayout->addWidget(content);

    connect(slider, &QSlider::valueChanged, this, [=](qreal value) {
        valueLabel->setText(QString::asprintf("%g", value * stepValue + minValue));
        curValue = value * stepValue + minValue;
        emit valueChanged(curValue);
        });
}

void horizontalValueAdjuster::setValue(qreal value) {
    valueLabel->setText(QString::asprintf("%g", value));
    slider->setValue((value - minValue) / stepValue);
    curValue = value;
    emit valueChanged(value);
}