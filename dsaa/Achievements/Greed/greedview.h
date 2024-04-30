#ifndef GREED_VIEW_H_
#define GREED_VIEW_H_

#include <QWidget>
#include <QVector>

class QTimer;
class GreedyChangeView : public QWidget
{
    Q_OBJECT

public:
    GreedyChangeView(QWidget* parent = nullptr);

    void showDefault();

    void setValues(QVector<int> values);
    void setCurrentCoins(QVector<int> coins);
    void setTargetAmout(int amout);
    void setCurrentAmout(int cur_amout);
protected:
    void paintEvent(QPaintEvent* event) override;

public slots:
    void startChange();
    void nextStep();
private:
    QTimer* timer;
    QVector<int> coinValues;
    QVector<int> currentCoins;
    int targetAmount;
    int currentAmount = 0;
};


#endif // !GREED_VIEW_H_
