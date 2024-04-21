#ifndef STAQUE_CANVAS_H_
#define STAQUE_CANVAS_H_

#include <QWidget>
#include <QPalette>

class SlidePage;
class QLabel;
class QHBoxLayout;
class StaqueView;
class StaqueCanvas: public QWidget {
	Q_OBJECT

public:
	explicit StaqueCanvas(int radius, QString name, QString desc, QWidget* parent = nullptr);

	~StaqueCanvas();

	void CreateSettings(int r);
    void Init();

	SlidePage* settingPage() { return settings; }


signals:
    void runFlagChanged(bool running);
    void nameChanged(QString name);
    void descChanged(QString desc);

private: 

    QString canvasName;
    QString canvasDescription;
    QString canvasSortType = "Linked List";
    QString canvasSortInterval = QString::number(20);
    QString canvasSortVolume = QString::number(10);

    SlidePage* settings;

    //For display
    QHBoxLayout* mainLayout;
    StaqueView* view{ nullptr };
    QWidget* infoWidget;
    QLabel* pageName{ nullptr };

    QPalette palette{ nullptr };

    int structure_type;
    int type;
    bool generateForest = false;
};

#endif // !LINKED_LIST_CANVAS_H_
