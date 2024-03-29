#pragma once
#include "SortObject.h"
#include <QVector>
#include <QStack>
#include <QEventLoop>
#include <QVariantAnimation>

/**
 * @brief Visualization of quick sort.
 */
class QuickSort : public SortObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructor of quick sort.
     */
    explicit QuickSort(QObject *parent = nullptr);

    /**
     * @brief Implement of quick sort. This is an override function.
     * @param count: The number of data element for Bubble sort.
     * @param interval: The interval of data element for Bubble sort.
     */
    void sort(int count, int interval) override;
    
    /**
    * @brief Stopped when quick sort is running. This is an override function.
    */
    void stop() override;
   
    /**
     * @brief Draw method of the quick sort. This is an override function.
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
    
    void doSort(int low, int high);
    
    void wait(int ms);
    
    void change(int from, int to);

private:
    QEventLoop loop;
    QVariantAnimation animation;
    int interval{0};

    QVector<int> arr;
    // recursion range
    QStack<QPair<int,int>> rangeStack;
    // current divided position.
    int rangeBegin{0};
    int rangeEnd{0};
    int curBegin{0};
    int curEnd{0};
    // The location and value of the pit
    int posIndex{0};
    int posValue{0};
    // exchange
    int swapFrom{0};
    int swapTo{0};
    bool swapFlag{false};
};
