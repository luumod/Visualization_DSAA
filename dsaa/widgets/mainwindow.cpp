#if DASS_VERSION

#include "mainwindow.h"
#include "common.h"
#include "customIcon.h"
#include "singleSelectGroup.h"
#include <QPointer>


MainWindow::MainWindow(QWidget* parent)
	:FramelessWindow(20,parent){
	resize(640, 480);
}

MainWindow::~MainWindow(){

}

void MainWindow::init(){
	icon_settings = new customIcon(ICON_FILE QString("settings.svg"), "", 10, this);
	icon_settings->move(10,10);

	icon_back = new customIcon(ICON_FILE "back.svg", "back_icon", 10, this);
	icon_back->move(30,10);


	singleSelectGroup* structureSel = new singleSelectGroup("Structure", this);
	selectionItem* item_1 = new selectionItem("AL", "Use adjacent list for canvas", this);
	selectionItem* item_2 = new selectionItem("AML", "Use multiple adjacent list for canvas", this);
	structureSel->AddItem(item_1);
	structureSel->AddItem(item_2);

	structureSel->move(10, 50);
}

void MainWindow::testFrameLessWindow(){
	FramelessWindow* winLess = new FramelessWindow(10);
	winLess->resize(400, 400);
	winLess->show();
}

#else 

#include "mainwindow.h"
#include "pushbutton.h"
#include <QHBoxLayout>
#include <QResizeEvent>

#define MAX_MOUSE_MOVEMENT 300

MainWindow::MainWindow(QWidget* parent)
    : FramelessWindow(20, parent)
{
    auto t = new PushButton(nullptr,nullptr);
    t->show();

    auto w = new FramelessWindow(20,nullptr);
    w->resize(400, 400);
    w->show();

    this->setMouseTracking(true);
    this->resize(1250, 750);

    // Create main layout for page and sidebar
    _mainLayout = new QHBoxLayout(_windowWidget);
    _mainLayout->setContentsMargins(0, 0, 0, 0);
    _mainLayout->setSpacing(0);
    _windowWidget->setLayout(_mainLayout);

    // Create placeholder widget for pages
    _placeHolderWidget = new QWidget(_windowWidget);
    _placeHolderWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _placeHolderWidget->setMouseTracking(true);

    // Connect the resize event of the placeholder widget to the resizePages function using event filter
    _placeHolderWidget->installEventFilter(this);

    // Create sidebar
    _sideBar = new SideBar(_windowWidget);
    connect(_sideBar, &SideBar::onPageChanged, this, [=](PageWidget* previousPage, PageWidget* currentPage) {
        // Check for input validity
        if (previousPage == currentPage) {
            return;
        }
        if (previousPage != nullptr) {
            previousPage->offStage();
        }
        if (currentPage != nullptr) {
            currentPage->onStage();
        }
        });
    _sideBar->setMouseTracking(true);

    // Add sidebar and placeholder widget to main layout
    _mainLayout->addWidget(_sideBar);
    _mainLayout->addWidget(_placeHolderWidget);

    // Create editor page and connect to side bar
    /*_editorPage = new EditorPage(_placeHolderWidget);
    _editorPage->setMouseTracking(true);
    _sideBar->addPage(_editorPage);*/

    // Create setting page and connect to side bar
    /*_settingPage = new SettingPage(_placeHolderWidget);
    _settingPage->setMouseTracking(true);
    _sideBar->addPage(_settingPage);*/

    // Create about page and connect to side bar
    _aboutPage = new AboutPage(_placeHolderWidget);
    _aboutPage->setMouseTracking(true);
    _sideBar->addPage(_aboutPage);

    //connect(_settingPage, &SettingPage::onSettingsChanged, _editorPage, &EditorPage::updateSetting);
}

MainWindow::~MainWindow() {
}

void MainWindow::resizePages(QResizeEvent* event) {
    // Check for input validity
    if (event == nullptr) {
        return;
    }

    // Get the size of the placeholder widget
    QSize size = event->size();

    // Resize the editor page
    //_editorPage->resize(size);
    //_settingPage->resize(size);
    _aboutPage->resize(size);
}

void MainWindow::showEvent(QShowEvent* event) {
    // Call parent show event
    FramelessWindow::showEvent(event);

    // Resize all the pages based on the placeholder widget
    //_editorPage->resize(_placeHolderWidget->size());
    //_settingPage->resize(_placeHolderWidget->size());
    _aboutPage->resize(_placeHolderWidget->size());
}

bool MainWindow::eventFilter(QObject* object, QEvent* event) {
    // Check for input validity
    if (object == nullptr || event == nullptr) {
        return false;
    }

    // Check if the object is the placeholder widget
    if (object == _placeHolderWidget) {
        // Check if the event is a resize event
        if (event->type() == QEvent::Resize) {
            // Resize all the pages
            resizePages(static_cast<QResizeEvent*>(event));
        }
    }

    // Call parent event filter
    return FramelessWindow::eventFilter(object, event);
}

#endif