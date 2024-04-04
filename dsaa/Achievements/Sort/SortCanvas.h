#ifndef MAIN_CANVAS
#define MAIN_CANVAS

#include <QWidget>
#include <QPalette>

class SortObject;
class QThread;
class QPalette;
class SlidePage;
class QHBoxLayout;
class QLabel;
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
    explicit SortCanvas(int radius, QString name, QString desc, QWidget* parent = nullptr);

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
     */
    void sort();

    /**
     * @brief Control to stop sort.
     */
    void stop();


    /**
     * @brief Set interval.
     */
    void setInterval(int interval);

    /**
     * @brief Set volume.
     */
    void setDataVolume(int dataVolume);

    QString canvasName;
    QString canvasDescription;
    QString canvasSortType = "Bubble Sort";
    QString canvasSortInterval = QString::number(20);
    QString canvasSortVolume = QString::number(10);

    SlidePage* settings;

    //For display
    QHBoxLayout* mainLayout;
    QWidget* view{ nullptr };
    QWidget* infoWidget;
    QLabel* pageName{ nullptr };

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
    void nameChanged(QString name);
    void descChanged(QString desc);
    void typeChanged(QString type);
    void intervalChanged(QString interval);
    void volumeChanged(QString volume);
private:
    int sortType{ -1 };
    SortObject* sortObj{ nullptr };
    QPalette palette{ nullptr };
    int interval{ 0 };
    int volume{ 0 };
};

#endif // !MAIN_CANVAS
