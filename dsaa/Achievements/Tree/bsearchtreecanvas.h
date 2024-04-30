#ifndef BSEARCH_TREE_CANVAS_H_
#define BSEARCH_TREE_CANVAS_H_

#include <QWidget>
#include <QPalette>

class SlidePage;
class QLabel;
class QHBoxLayout;
class BSearchTreeView;
class BSearchTreeCanvas: public QWidget {
	Q_OBJECT

public:
	explicit BSearchTreeCanvas(int radius, QString name, QString desc, QWidget* parent = nullptr);

	~BSearchTreeCanvas();

	void CreateSettings(int r);
    void Init();

	SlidePage* settingPage() { return settings; }


signals:
    void startBSearchTree();
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
    BSearchTreeView* view{ nullptr };
    QWidget* infoWidget;
    QLabel* pageName{ nullptr };

    QPalette palette{ nullptr };

    int structure_type;
    int type;
    bool generateForest = false;
};

#endif // !LINKED_LIST_CANVAS_H_
