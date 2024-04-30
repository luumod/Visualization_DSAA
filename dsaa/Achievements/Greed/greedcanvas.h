#ifndef LINKED_LIST_CANVAS_H_
#define LINKED_LIST_CANVAS_H_

#include <QWidget>
#include <QPalette>

class SlidePage;
class QLabel;
class QHBoxLayout;
class BaseList;
class GreedyChangeView;
class GreedCanvas: public QWidget {
	Q_OBJECT

public:
	explicit GreedCanvas(int radius, QString name, QString desc, QWidget* parent = nullptr);

	~GreedCanvas();

	void CreateSettings(int r);
    void Init();

	SlidePage* settingPage() { return settings; }


signals:
    void startGreed();
    void runFlagChanged(bool running);
    void nameChanged(QString name);
    void descChanged(QString desc);
    void brushColorChanged(QColor color);
    void lineColorChanged(QColor color);
    void textColorChanged(QColor color);
private: 

    QString canvasName;
    QString canvasDescription;
    QString canvasSortType = "Linked List";
    QString canvasSortInterval = QString::number(20);
    QString canvasSortVolume = QString::number(10);

    SlidePage* settings;

    //For display
    QHBoxLayout* mainLayout;
    GreedyChangeView* view{ nullptr };
    QWidget* infoWidget;
    QLabel* pageName{ nullptr };

    QPalette palette{ nullptr };

    int structure_type;
    int type;
    bool generateForest = false;
};

#endif // !LINKED_LIST_CANVAS_H_
