#ifndef MAIN_WINDOW
#define MAIN_WINDOW

#include <QMainWindow>
#include "conponents/framelesswindow.h"
#include "conponents/sidebar.h"
#include "conponents/singleSelectGroup.h"
#include "aboutpage.h"
#include "homepage.h"
#include "slidepage.h"

class QLineEdit;
class QGraphicsDropShadowEffect;
class SortPage;
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
    HomePage* _homePage = nullptr;
    AboutPage* _aboutPage = nullptr;

    // Sub conponents in the home page.
    bigIconButton* _homeSortButton = nullptr;

    QWidget* defaultPage = nullptr;
    SlidePage* createNewPage = nullptr;
    int cornerRadius = 20;
    QVector<SlidePage*> pageList;
    
    // Place holder widget for resizing pages
    QWidget* _placeHolderWidget = nullptr;

    // Sort page conponents.
    SortPage* _sortPage = nullptr;
    QLineEdit* _sortPageTitle = nullptr;
    QLineEdit* _sortPageDesc = nullptr;

private:
    void resizePages(QResizeEvent* event);

private:
    virtual void showEvent(QShowEvent* event) override;
    virtual bool eventFilter(QObject* object, QEvent* event) override;
};

#endif