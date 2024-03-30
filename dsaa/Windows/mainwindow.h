#ifndef MAIN_WINDOW
#define MAIN_WINDOW

#include "Components/framelesswindow.h"

class QLineEdit;
class QGraphicsDropShadowEffect;
class SlidePage;
class SortPage;
class GraphPage;
class AboutPage;
class bigIconButton;
class SideBar;
#define DASS_VERSION false

class MainWindow : public FramelessWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void Init();
    void selectCanvas(SortPage* canvas);
    void deleteCanvas(SortPage* canvas);
private:
    // Main ui layout
    QHBoxLayout* _mainLayout = nullptr;

    // Side bar and corresponding pages
    SideBar* _sideBar = nullptr;

    //If you want to add a new Page, firstly declaration in here.
    SortPage* _sortPage = nullptr;
    AboutPage* _aboutPage = nullptr;
    GraphPage* _graphPage = nullptr;

    // Sub Components in the home page.
    bigIconButton* _homeSortButton = nullptr;

    QWidget* defaultPage = nullptr;
    SlidePage* createNewPage = nullptr;
    int cornerRadius = 20;
    QVector<SlidePage*> pageList;
    
    // Place holder widget for resizing pages
    QWidget* _placeHolderWidget = nullptr;

private:
    void resizePages(QResizeEvent* event);

private:
    virtual void showEvent(QShowEvent* event) override;
    virtual bool eventFilter(QObject* object, QEvent* event) override;
};

#endif