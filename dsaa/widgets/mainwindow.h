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
#define DASS_VERSION false

#if DASS_VERSION
class customIcon;
class MainWindow: public FramelessWindow {
	Q_OBJECT;
public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

	void init();

	void testFrameLessWindow();
private:
	customIcon* icon_settings{nullptr};
	customIcon* icon_back{ nullptr };
};

#else
class MainWindow : public FramelessWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void Init();

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


    QLineEdit* canvasTitle = nullptr;
    QLineEdit* canvasDesc = nullptr;
    customIcon* settingsIcon = nullptr;
    customIcon* layersIcon = nullptr;
    QWidget* canvasDisplay = nullptr;
    QWidget* border = nullptr;
    QColor mainBackGround = QColor(251, 251, 251);
    QGraphicsDropShadowEffect* windowShadow;
    QWidget* defaultPage = nullptr;
    // the side page for the choice sort algorithms.
    SlidePage* createNewPage = nullptr;
    SlidePage* defaultSettingsPage = nullptr;
    SlidePage* curSettingsPage = nullptr;
    singleSelectGroup* layerSel = nullptr;
    SlidePage* layersPage = nullptr;
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

#endif