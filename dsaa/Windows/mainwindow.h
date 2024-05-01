#ifndef MAIN_WINDOW
#define MAIN_WINDOW

#include "Components/framelesswindow.h"

class QLineEdit;
class QGraphicsDropShadowEffect;
class SlidePage;
class SortPage;
class GraphPage;
class LinkedListPage;
class StaquePage;
class GreedPage;
class BSearchTreePage;
class FindPage;
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
    int cornerRadius = 20;

    // Main ui layout
    QHBoxLayout* _mainLayout = nullptr;

    // Side bar and corresponding pages
    SideBar* _sideBar = nullptr;

    //If you want to add a new Page, firstly declaration in here.
    SortPage* _sortPage = nullptr;
    AboutPage* _aboutPage = nullptr;
    GraphPage* _graphPage = nullptr;
    StaquePage* _staquePage = nullptr;
    GreedPage* _greedPage = nullptr;
    BSearchTreePage* _bstreePage = nullptr;
    FindPage* _findPage = nullptr;
    LinkedListPage* _listPage = nullptr;

    
    // Place holder widget for resizing pages
    QWidget* _placeHolderWidget = nullptr;

protected:
    void resizeEvent(QResizeEvent* event);

private:
    void resizePages(QResizeEvent* event);

private:
    virtual void showEvent(QShowEvent* event) override;
    virtual bool eventFilter(QObject* object, QEvent* event) override;
};

#endif