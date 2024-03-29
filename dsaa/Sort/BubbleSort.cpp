#include "BubbleSort.h"
#include <algorithm>
#include <cmath>
#include <QtMath>
#include <QTime>
#include <QPainter>
#include <QPaintEvent>
#include <QScopeGuard>
#include <QFontMetrics>
#include <QDebug>
#include <random>

BubbleSort::BubbleSort(QObject *parent)
    : SortObject(parent)
{
    // Initialize of the animation for bubble sort.
    animation.setStartValue(0.0);
    animation.setEndValue(1.0);
    animation.setEasingCurve(QEasingCurve::OutQuart);
    animation.setLoopCount(1);
    connect(&animation, &QVariantAnimation::finished, &loop, &QEventLoop::quit);
    connect(&animation, &QVariantAnimation::valueChanged, this, &SortObject::updateToDraw);
}

// This is a template of the bubble sort.
//template<typename T>
//void bubble_sort(std::vector<T>& arr)
//{
//    for (size_t i = 0; i < arr.size() - 1; i++) {
//        for (size_t j = 0; j < arr.size() - 1 - i; j++) {
//            if (arr[j] > arr[j + 1]) {
//                std::swap(arr[j], arr[j + 1]);
//            }
//        }
//    }
//}

void BubbleSort::sort(int count, int interval)
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
    for (arrI = 0; arrI < len - 1; arrI++)
    {
        for (arrJ = 0; arrJ < len - 1 - arrI; arrJ++)
        {
            if (arr[arrJ] > arr[arrJ + 1]) {
                animation.setDuration(interval * 3);
                animation.start();
                swapFlag = true;
                loop.exec();
                if (getRunFlag()) {
                    qSwap(arr[arrJ], arr[arrJ + 1]);
                    swapFlag = false;
                }
            } else {
                animation.setDuration(interval);
                animation.start();
                loop.exec();
            }
            emit updateToDraw();
            if (!getRunFlag()) {
                return;
            }
        }
        if (!getRunFlag()) {
            return;
        }
    }
}

void BubbleSort::stop()
{
    setRunFlag(false);
    animation.stop();
    loop.quit();
    emit updateToDraw();
}

void BubbleSort::draw(QPainter *painter, int width, int height)
{
    painter->setPen(QColor(200, 200, 200));
    const int len = arr.length();
    
    // Border distance.
    const int left_space = 0;
    const int right_space = 0;
    const int top_space = 20;
    const int bottom_space = 50;

    const int item_space = 10; //Column horizon space.
    const int text_height = painter->fontMetrics().height();
    const int text_space = 15; // Text and column's space
    const double item_width = (width + item_space - left_space - right_space) / (double)len - item_space;
    const double item_bottom = height - bottom_space;
    const double height_factor = (height - top_space - bottom_space) / (double)len;
    double item_left = 0;
    double item_height = 0;
    QColor color;
    for (int i = 0; i < len; i++)
    {
        // Color block position x.
        item_left = left_space + i * (item_width + item_space);
        item_height = height_factor * arr.at(i);
        // The column's color.
        color = QColor(200, 200, 200);
        if (getRunFlag()) {
            if (i == arrJ) {
                // The first element.
                color = QColor(255, 170 , 0);
                if (swapFlag) {
                    item_left += animation.currentValue().toDouble() * (item_width + item_space);
                }
            } else if (i == arrJ + 1) {
                // The second element.
                color = QColor(0, 170 , 255);
                if (swapFlag) {
                    item_left -= animation.currentValue().toDouble() * (item_width + item_space);
                }
            } else if (i >= len - arrI) {
                // Other elements already sorted.
                color = QColor(0, 180, 0);
            }
        }
        // Draw Text
        painter->drawText(item_left, item_bottom + text_height + text_space,
                          QString::number(arr.at(i)));
        // Draw column rect.
        painter->fillRect(item_left, item_bottom - item_height,
                          item_width, item_height,
                          color);
    }
}

void BubbleSort::run(){
    sort(50, 5);
    emit finished();
}

void BubbleSort::initArr(int count)
{
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

    arrI = 0;
    arrJ = 0;
    swapFlag = false;
    emit updateToDraw();
}
