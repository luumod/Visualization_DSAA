#ifndef LINKED_LIST_CANVAS_H_
#define LINKED_LIST_CANVAS_H_

#include <QWidget>
#include <QPalette>

class SlidePage;
class QLabel;
class QHBoxLayout;
class DoublyLinkedList;
class LinkedListCanvas: public QWidget {
	Q_OBJECT

public:
	explicit LinkedListCanvas(int radius, QString name, QString desc, QWidget* parent = nullptr);

	~LinkedListCanvas();

	void CreateSettings(int r);
    void Init();

	SlidePage* settingPage() { return settings; }

protected:
    /**
     * @brief Use update to redraw canvas.
     */
    void paintEvent(QPaintEvent* event) override;

private:
    DoublyLinkedList* base_list_obj{ nullptr };

    QString canvasName;
    QString canvasDescription;
    QString canvasSortType = "Linked List";
    QString canvasSortInterval = QString::number(20);
    QString canvasSortVolume = QString::number(10);

    SlidePage* settings;

    //For display
    QHBoxLayout* mainLayout;
    QWidget* view{ nullptr };
    QWidget* infoWidget;
    QLabel* pageName{ nullptr };

    QPalette palette{ nullptr };

    int structure_type;
    int type;
    bool generateForest = false;
};

#endif // !LINKED_LIST_CANVAS_H_
