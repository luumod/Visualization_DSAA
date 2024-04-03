#ifndef MAIN_CANVAS
#define MAIN_CANVAS

#include <QWidget>
#include <QPalette>

class SortObject;
class QThread;
class QPalette;
class SlidePage;
class QHBoxLayout;
/**
 * @brief The main canvas for every sort operation.
 */
class SortCanvas : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Constructor of the SortCanvas's widget.
     */
    explicit SortCanvas(int radius, QWidget* parent = nullptr);

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

    QString canvasName;
    QString canvasDescription;

    SlidePage* settings;

    //For display
    QHBoxLayout* mainLayout;
    QWidget* view{ nullptr };
    QWidget* infoWidget;

    int structure_type;
    int type;
    bool generateForest = false;

    void CreateSettings(int r);
    void Init();
    SlidePage* settingPage() { return settings; }

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
    QPalette palette{ nullptr };
};

#endif // !MAIN_CANVAS
