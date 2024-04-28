#ifndef SORT_OBJECT
#define SORT_OBJECT

#include <QObject>
#include <QPainter>
#include <QVector>

/**
 * @brief The parent class of all sort object.
 */
class SortObject : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructor of SortObject.
     */
    explicit SortObject(QObject *parent = nullptr);

    /**
     * @brief Virtual function of bubble sort.
     * @param count: The number of data element for Bubble sort.
     * @param interval: The interval of data element for Bubble sort.
     */
    virtual void sort(int count, int interval) = 0;
    
    /**
     * @brief Virtual function for Stopped sort when bubble sort is running.
     */
    virtual void stop() = 0;
    
    /**
     * @brief Virtual draw method of the bubble sort.
     * @param painter: Qt painter object
     * @param canvas_width: Canvas widget's width.
     * @param canvas_height: Canvas widget's height.
     */
    virtual void draw(QPainter *painter, int width, int height) = 0;

    /**
     * @brief Is running? true or false.
     */
    bool getRunFlag() const;
    
    /**
     * @brief Set or update sort type.
     */
    void setRunFlag(bool flag);

signals:
    void runFlagChanged(bool running);
    void updateToDraw();
    void finishedEachIteration(QVector<int> arr);

private:
    bool runFlag{false};
};

#endif