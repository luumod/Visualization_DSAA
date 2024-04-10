#ifndef LINKED_LIST_CANVAS_H_
#define LINKED_LIST_CANVAS_H_

#include <QWidget>
#include <QPalette>

class SlidePage;
class QLabel;
class QHBoxLayout;
class LinkedListCanvas: public QWidget {
	Q_OBJECT

public:
	explicit LinkedListCanvas(int radius, QString name, QString desc, QWidget* parent = nullptr);

	~LinkedListCanvas();

	void drawLinkedList(QPainter* painter, const QList<int>& values, int width, int height);

	void CreateSettings(int r);
    void Init();

	SlidePage* settingPage() { return settings; }
private:
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
