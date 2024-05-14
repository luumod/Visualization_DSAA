#include "InsertionSort.h"
#include <algorithm>
#include <cmath>
#include <QtMath>
#include <QTime>
#include <QPainter>
#include <QPainterPath>
#include <QPaintEvent>
#include <QScopeGuard>
#include <QFontMetrics>
#include <QDebug>
#include <random>
#include <QTimer>

InsertionSort::InsertionSort(QObject *parent)
    : SortObject(parent)
{
    //animation.setDuration(2000);
    animation.setStartValue(0.0);
    animation.setEndValue(1.0);
    animation.setEasingCurve(QEasingCurve::OutQuart);
    animation.setLoopCount(1);
    connect(&animation, &QVariantAnimation::finished, &loop, &QEventLoop::quit);
    connect(&animation, &QVariantAnimation::valueChanged, this, &SortObject::updateToDraw);
}

/*//一般的插入排序写法
template<typename T>
void insertion_sort(std::vector<T>& arr)
{
    for (size_t i = 1; i < arr.size(); i++) {
        for (size_t j = i; j  > 0; j--) {
            if (arr[j] < arr[j - 1]) {
                std::swap(arr[j], arr[j - 1]);
            }
        }
    }
}*/

void InsertionSort::sort(int count, int interval)
{
    auto guard = qScopeGuard([this]{
        setRunFlag(false);
        emit updateToDraw();
    });
    Q_UNUSED(guard)

    stop();
    initArr(count);
    setRunFlag(true);

    int len = arr.length();
    for (arrI = 1; arrI < len; arrI++)
    {
        for (arrJ = arrI; arrJ > 0; arrJ--)
        {
            if (arr[arrJ] < arr[arrJ - 1]) {
                animation.setDuration(interval * 3);
                animation.start();
                swapFlag = true;
                loop.exec();
                if (getRunFlag()) {
                    qSwap(arr[arrJ], arr[arrJ - 1]);
                    swapFlag = false;
                }
            } else {
                //大于前面已排序好的数就不用交换了，=-1终止循环
                arrJ = -1;
                animation.setDuration(interval);
                animation.start();
                loop.exec();
            }
            emit updateToDraw();
            if (!getRunFlag()) {
                return;
            }
        }
        if (!finish) {
            loop_single_step.exec();
        }
        emit finishedEachIteration(arr);
        QEventLoop loop;
        QTimer::singleShot(200, &loop, &QEventLoop::quit);
        loop.exec();
        if (!getRunFlag()) {
            return;
        }
    }
    finish = false;
}

void InsertionSort::stop()
{
    setRunFlag(false);
    animation.stop();
    loop.quit();
    emit updateToDraw();
}

void InsertionSort::draw(QPainter *painter, int width, int height)
{
    painter->setPen(QColor(200, 200, 200));
    const int len = arr.length();
    //边框距离
    const int left_space = 0;
    const int right_space = 0;
    const int top_space = 20;
    const int bottom_space = 50;

    const int item_space = 10; 
    const int text_height = painter->fontMetrics().height();
    const int text_space = 15;
    const double item_width = (width + item_space - left_space - right_space) / (double)len - item_space;
    const double item_bottom = height - bottom_space;
    const double height_factor = (height - top_space - bottom_space) / (double)len;
    double item_left = 0;
    double item_height = 0;
    QColor color;
    for (int i = 0; i < len; i++)
    {
        item_left = left_space + i * (item_width + item_space);
        item_height = height_factor * arr.at(i);
        color = QColor(200, 200, 200);
        if (getRunFlag()) {
            if (i <=  arrI) {
                color = QColor(0, 170, 0);
            }
            if (i == arrJ - 1) {
                //color = QColor(255, 170 , 0);
                if (swapFlag) {
                    item_left += animation.currentValue().toDouble() * (item_width + item_space);
                }
            } else if (i == arrJ) {
                color = QColor(0, 170 , 255);
                if (swapFlag) {
                    item_left -= animation.currentValue().toDouble() * (item_width + item_space);
                }
            }
        }
        painter->drawText(item_left, item_bottom + text_height + text_space,
                          QString::number(arr.at(i)));
        // Draw pillar.
        QPainterPath roundPath;
        roundPath.addRoundedRect(QRectF(item_left, item_bottom - item_height,
            item_width, item_height), 10, 10);
        painter->fillPath(roundPath, color);
    }
}

void InsertionSort::initArr(int count)
{
    if (!u_arr.isEmpty()) {
        arr = u_arr;
    }
    else {
        if (count < 2) {
            return;
        }

        arr.resize(count);
        for (int i = 0; i < count; i++)
        {
            arr[i] = i + 1;
        }
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(arr.begin(), arr.end(), g);
    }

    arrI = 0;
    arrJ = 0;
    swapFlag = false;
    emit updateToDraw();
}
