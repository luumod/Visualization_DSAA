#ifndef MAIN_WINDOW
#define MAIN_WINDOW

#include <QMainWindow>
#include "conponents/framelesswindow.h"
#include "conponents/sidebar.h"
#include "aboutpage.h"

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

private:
    // Main ui layout
    QHBoxLayout* _mainLayout = nullptr;

    // Side bar and corresponding pages
    SideBar* _sideBar = nullptr;
    AboutPage* _aboutPage = nullptr;

    //If you want to add a new Page, firstly declaration in here.
    //EditorPage* _editorPage = nullptr;
    //SettingPage* _settingPage = nullptr;

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