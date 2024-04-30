#include <QApplication>
#include <QMainWindow>
#include <QTimer>
#include <QPainter>
#include <QVector>
#include <QPair>
#include <QDebug>

class GreedyChangeDemo : public QMainWindow
{
    Q_OBJECT

public:
    GreedyChangeDemo(QWidget* parent = nullptr) : QMainWindow(parent)
    {
        setWindowTitle("Greedy Change Demo");
        resize(800, 600);

        // ������Ǯ���
        coinValues << 25 << 10 << 5 << 1;

        // ������Ҫ����Ľ��
        targetAmount = 99;

        // ��ʼ��������ʱ��
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &GreedyChangeDemo::nextStep);

        // ��ʼ����
        timer->start(1000);
    }

protected:
    void paintEvent(QPaintEvent* event) override
    {
        Q_UNUSED(event);
        QPainter painter(this);

        painter.fillRect(0, 0, width(), height(), Qt::white);

        // ������Ǯ
        painter.setPen(Qt::black);
        for (int i = 0; i < coinValues.size(); ++i)
        {
            painter.drawRect(100 + i * 50, height() - 50, 40, 40);
            painter.drawText(120 + i * 50, height() - 25, QString::number(coinValues[i]));
        }

        // ����Ŀ����
        painter.setPen(Qt::red);
        painter.drawText(width() / 2 - 40, height() - 100, "Target Amount: " + QString::number(targetAmount));

        // ���Ƶ�ǰ����Ľ��
        painter.setPen(Qt::blue);
        painter.drawText(width() / 2 - 40, height() - 75, "Current Amount: " + QString::number(currentAmount));

        // �����Ѿ��ҵ���Ӳ��
        painter.setPen(Qt::darkGreen);
        int x = 50;
        int y = height() - 150;
        for (int i = 0; i < currentCoins.size(); ++i)
        {
            painter.drawRect(x, y, 40, 40);
            painter.drawText(x + 20, y + 25, QString::number(currentCoins[i]));
            x += 50;
        }
    }

private slots:
    void nextStep()
    {
        if (currentAmount == targetAmount)
        {
            // ������ɣ�ֹͣ����
            timer->stop();
            return;
        }

        for (int i = 0; i < coinValues.size(); ++i)
        {
            if (currentAmount + coinValues[i] <= targetAmount)
            {
                currentCoins.push_back(coinValues[i]);
                currentAmount += coinValues[i];
                break;
            }
        }

        update();
    }

private:
    QTimer* timer;
    QVector<int> coinValues;
    QVector<int> currentCoins;
    int targetAmount;
    int currentAmount = 0;
};

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    GreedyChangeDemo w;
    w.show();
    return a.exec();
}

#include "main.moc"
