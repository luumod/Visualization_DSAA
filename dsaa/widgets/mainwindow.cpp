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
#include "common.h"
#include "pushbutton.h"
#include "singleSelectGroup.h"
#include "textButton.h"
#include "textInputItem.h"
#include "bigIconButton.h"
#include <QHBoxLayout>
#include <QResizeEvent>
#include <QLineEdit>
#define MAX_MOUSE_MOVEMENT 300

MainWindow::MainWindow(QWidget* parent)
    : FramelessWindow(20, parent)
{
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

    // When page changed, activate this lambda to achieve change.
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

    // Add home page and connect to side bar.
    _homePage = new HomePage(_placeHolderWidget);
    _homePage->setMouseTracking(true);
    _sideBar->addPage(_homePage);

    // Create about page and connect to side bar
    _aboutPage = new AboutPage(_placeHolderWidget);
    _aboutPage->setMouseTracking(true);
    _sideBar->addPage(_aboutPage);

    //connect(_settingPage, &SettingPage::onSettingsChanged, _editorPage, &EditorPage::updateSetting);

    _homeSortButton = _homePage->addConponent<bigIconButton>(new bigIconButton(ICON_FILE QString("sort.png"), "Sort Algotirhms", 10), 0, 0);
    auto place_holder1 = _homePage->addConponent<bigIconButton>(new bigIconButton(ICON_FILE QString("sort.png"), "Sort Algotirhms", 10), 0, 1);
    auto place_holder2 = _homePage->addConponent<bigIconButton>(new bigIconButton(ICON_FILE QString("sort.png"), "Sort Algotirhms", 10), 1, 0);
    auto place_holder3 = _homePage->addConponent<bigIconButton>(new bigIconButton(ICON_FILE QString("sort.png"), "Sort Algotirhms", 10), 1, 1);


    //-------------------------------
       
    /* create layers page */
    //for add new page
    textInputItem* rename = new textInputItem("Name:", createNewPage);
    rename->setValue("Layer_" + QString::asprintf("%d", 1));
    textInputItem* redescribe = new textInputItem("Detail:", createNewPage);
    redescribe->setValue("No description");

    // when user choice the "sort algorithms", show an sider page to user. 
    createNewPage = new SlidePage(cornerRadius, "CREATE CANVAS", this);
    QLineEdit* canvasName = new QLineEdit(this);
    canvasName->setMaximumHeight(20);
    QLineEdit* canvasDesc = new QLineEdit(this);
    canvasDesc->setMaximumHeight(20);

    QWidget* whiteSpace = new QWidget(createNewPage);
    whiteSpace->setFixedHeight(30);
    singleSelectGroup* structureSel = new singleSelectGroup("Structure", createNewPage);
    selectionItem* item_1 = new selectionItem("AL", "Use adjacent list for canvas", createNewPage);
    selectionItem* item_2 = new selectionItem("AML", "Use multiple adjacent list for canvas", createNewPage);
    structureSel->AddItem(item_1);
    structureSel->AddItem(item_2);
    singleSelectGroup* dirSel = new singleSelectGroup("Mode", createNewPage);
    selectionItem* item_3 = new selectionItem("DG", "Directed graph", createNewPage);
    selectionItem* item_4 = new selectionItem("UDG", "Undirected graph", createNewPage);
    dirSel->AddItem(item_3);
    dirSel->AddItem(item_4);
    textButton* submit = new textButton("Create!", createNewPage);

    // Key down action.
    /*connect(submit, &textButton::clicked, this, [=]() {
        MyCanvas* newCanvas = new MyCanvas(cornerRadius,
        rename->value(),
        redescribe->value(),
        structureSel->value() == 0 ? MyCanvas::AL : MyCanvas::AML,
        dirSel->value() == 0 ? MyCanvas::DG : MyCanvas::UDG, ui->mainWidget);
        canvasList.push_back(newCanvas);
        selectionItem* newLayer = new selectionItem(newCanvas->name(), newCanvas->description(), layersPage);
        layerSel->AddItem(newLayer);
        layerSel->SetSelection(newLayer);
        pageList.push_back(newCanvas->settingPage());
        connect(newLayer, &selectionItem::selected, this, [=]() {selectCanvas(newCanvas); });
        selectCanvas(newCanvas);
        connect(newCanvas, &MyCanvas::nameChanged, this, [=](QString text) {
            canvasTitle->setText(text);
            canvasTitle->setMaximumWidth(QFontMetrics(QFont("Corbel Light", 24)).size(Qt::TextSingleLine, canvasTitle->text()).width() + 10);
            newLayer->setTitle(text);
            });
        connect(newCanvas, &MyCanvas::descChanged, this, [=](QString text) {this->canvasDesc->setText(text); newLayer->setDescription(text); });
        connect(newCanvas, &MyCanvas::setDel, this, [=](MyCanvas* c) {curSettingsPage->slideOut(); deleteCanvas(c); layerSel->RemoveItem(newLayer); });
        createNewPage->slideOut();
        });*/
    createNewPage->AddContent(submit);
    createNewPage->AddContent(dirSel);
    createNewPage->AddContent(structureSel);
    createNewPage->AddContent(whiteSpace);
    createNewPage->AddContent(redescribe);
    createNewPage->AddContent(rename);
    connect(_homeSortButton, &bigIconButton::clicked, createNewPage, [=]() {
        rename->setValue("Layer_" + QString::asprintf("%d", 1));
        redescribe->setValue("No description");
        createNewPage->slideIn(); }
    );
    createNewPage->show();
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
    _homePage->resize(size);
    _aboutPage->resize(size);
}

void MainWindow::showEvent(QShowEvent* event) {
    // Call parent show event
    FramelessWindow::showEvent(event);

    // Resize all the pages based on the placeholder widget
    //_editorPage->resize(_placeHolderWidget->size());
    //_settingPage->resize(_placeHolderWidget->size());
    _homePage->resize(_placeHolderWidget->size());
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