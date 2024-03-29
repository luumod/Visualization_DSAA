#pragma once
#include "SortObject.h"
#include <QVector>
#include <QEventLoop>
#include <QVariantAnimation>

/**
 * @brief Visualization of insertion sort.
 */
class InsertionSort : public SortObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructor of insertion sort.
     */
    explicit InsertionSort(QObject *parent = nullptr);

    /**
     * @brief Implement of insertion sort. This is an override function.
     * @param count: The number of data element for Bubble sort.
     * @param interval: The interval of data element for Bubble sort.
     */
    void sort(int count, int interval) override;
   
    /**
     * @brief Stopped when insertion sort is running. This is an override function.
     */
    void stop() override;

    /**
     * @brief Draw method of the insertion sort. This is an override function.
     * @param painter: Qt painter object
     * @param canvas_width: Canvas widget's width.
     * @param canvas_height: Canvas widget's height.
     */
    void draw(QPainter *painter, int width, int height) override;

private:
    /**
     * @brief Generate random data element for the initial unsorted arr.
     * @param count: The data size.
     */
    void initArr(int count);

private:
    QEventLoop loop;
    QVariantAnimation animation;
    QVector<int> arr;
    int arrI{0};
    int arrJ{0};
    bool swapFlag{false};
};
