#ifndef FIND__CANVAS_H_
#define FIND__CANVAS_H_

#include <QWidget>
#include <QPalette>

class SlidePage;
class QLabel;
class QHBoxLayout;
class FindView;
class FindCanvas: public QWidget {
	Q_OBJECT

public:
	explicit FindCanvas(int radius, QString name, QString desc, QWidget* parent = nullptr);

	~FindCanvas();

	void CreateSettings(int r);
    void Init();

	SlidePage* settingPage() { return settings; }


signals:
    void runFlagChanged(bool running);
    void nameChanged(QString name);
    void descChanged(QString desc);
    void choiceSearchApproach(int type);
private: 

    QString canvasName;
    QString canvasDescription;
    QString canvasSortType = "Linked List";
    QString canvasSortInterval = QString::number(20);
    QString canvasSortVolume = QString::number(10);

    SlidePage* settings;

    //For display
    QHBoxLayout* mainLayout;
    FindView* view{ nullptr };
    QWidget* infoWidget;
    QLabel* pageName{ nullptr };

    QPalette palette{ nullptr };

    int structure_type;
    int type;
    bool generateForest = false;
};

#endif // !LINKED_LIST_CANVAS_H_
