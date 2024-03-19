#ifndef HORIZONTAL_VALUE_ADJUSTER
#define HORIZONTAL_VALUE_ADJUSTER

#include <QWidget>

class QLabel;
class customIcon;
class QSlider;
class horizontalValueAdjuster : public QWidget {
    Q_OBJECT

private:
    const int middleSpacing = 5;
    const int bottomSpacing = 30;
    QLabel* title;
    qreal curValue;
    qreal minValue;
    qreal maxValue;
    qreal stepValue;
    QWidget* editArea;
    QLabel* valueLabel;
    //QDoubleSpinBox *editLabel;
    customIcon* decreaseBtn;
    customIcon* increaseBtn;
    QSlider* slider;

public:
    horizontalValueAdjuster(QString name, qreal min, qreal max, qreal step, QWidget* parent = nullptr);
    void setValue(qreal value);
    qreal value() { return curValue; }

signals:
    void valueChanged(qreal value);

};


#endif // !HORIZONTAL_VALUE_ADJUSTER

