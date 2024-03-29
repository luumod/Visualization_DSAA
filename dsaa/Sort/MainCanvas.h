#ifndef MAIN_CANVAS
#define MAIN_CANVAS

#include <QWidget>

class SortObject;
class QThread;
/**
 * @brief The main canvas for every sort operation.
 */
class MainCanvas : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Constructor of the MainCanvas's widget.
     */
    explicit MainCanvas(QWidget* parent = nullptr);

    /**
     * @brief Get sort type of user choice. Each type has different implement method.
     */
    int getSortType() const;

    /**
     * @brief Set or update sort object.
     * @param type: Sort type.
     * @param obj: Concrete sort object.
     */
    void setSortObject(int type, SortObject* obj);

    /**
     * @brief Control to begin sort.
     * @param count: data size
     * @param interval: interval of sorting.
     */
    void sort(int count, int interval);

    /**
     * @brief Control to stop sort.
     */
    void stop();

    //void intoThread();

protected:
    /**
     * @brief Use update to redraw canvas.
     */
    void paintEvent(QPaintEvent* event) override;

signals:
    void runFlagChanged(bool running);

private:
    int sortType{ -1 };
    SortObject* sortObj{ nullptr };
    QThread* thread{ nullptr };
};

#endif // !MAIN_CANVAS
