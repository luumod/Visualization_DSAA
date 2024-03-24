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
#include "customIcon.h"
#include <QHBoxLayout>
#include <QResizeEvent>
#include <QLineEdit>
#include <QTimer>
#include <QPainterPath>
#include <QGraphicsDropShadowEffect>
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

    
    Init();
}

MainWindow::~MainWindow() {
}

#if 1
void MainWindow::Init() {
    /* Create about page */
    defaultSettingsPage = new SlidePage(cornerRadius, "ABOUT", _homePage);
    textInputItem* version = new textInputItem("version", defaultSettingsPage);
    version->setValue("1.3-beta");
    version->setEnabled(false);
    textInputItem* updateDate = new textInputItem("last-upd", defaultSettingsPage);
    updateDate->setValue("2021/12/6 10:14");
    updateDate->setEnabled(false);
    textInputItem* Author = new textInputItem("author", defaultSettingsPage);
    Author->setValue("Linloir | Made with love");
    Author->setEnabled(false);
    textInputItem* lic = new textInputItem("lic", defaultSettingsPage);
    lic->setValue("MIT License");
    lic->setEnabled(false);
    textInputItem* GitHub = new textInputItem("git", defaultSettingsPage);
    GitHub->setValue("github.com/Linloir");
    GitHub->setEnabled(false);
    defaultSettingsPage->AddContent(GitHub);
    defaultSettingsPage->AddContent(lic);
    defaultSettingsPage->AddContent(Author);
    defaultSettingsPage->AddContent(updateDate);
    defaultSettingsPage->AddContent(version);
    curSettingsPage = defaultSettingsPage;
    defaultSettingsPage->show();
    pageList.push_back(defaultSettingsPage);

    /************************/

    /* Initialize display area */
    QFont titleFont = QFont("Corbel Light", 24);
    QFontMetrics titleFm(titleFont);
    canvasTitle = new QLineEdit(this);
    canvasTitle->setFont(titleFont);
    canvasTitle->setText("START");
    canvasTitle->setMaxLength(20);
    canvasTitle->setReadOnly(true);
    canvasTitle->setMinimumHeight(titleFm.height());
    canvasTitle->setMaximumWidth(titleFm.size(Qt::TextSingleLine, "START").width() + 10);
    canvasTitle->setStyleSheet("background-color:#00000000;border-style:none;border-width:0px;margin-left:1px;");
    connect(canvasTitle, &QLineEdit::textEdited, canvasTitle, [=](QString text) {canvasTitle->setMaximumWidth(titleFm.size(Qt::TextSingleLine, text).width()); });

    QFont descFont = QFont("Corbel Light", 12);
    QFontMetrics descFm(descFont);
    canvasDesc = new QLineEdit(this);
    canvasDesc->setFont(descFont);
    canvasDesc->setText("Add your first canvas to start");
    canvasDesc->setMaxLength(128);
    canvasDesc->setReadOnly(true);
    canvasDesc->setMinimumHeight(descFm.lineSpacing());
    canvasDesc->setStyleSheet("background-color:#00000000;border-style:none;border-width:0px;");

    // ---------------------------------
    settingsIcon = new customIcon(ICON_FILE "settings.svg", "settings", 5, this);
    settingsIcon->setMinimumHeight(canvasTitle->height() * 0.7);
    settingsIcon->setMaximumWidth(canvasTitle->height() * 0.7);
    connect(settingsIcon, &customIcon::clicked, this, [=]() {
        QPropertyAnimation* rotate = new QPropertyAnimation(settingsIcon, "rotationAngle", this);
        rotate->setDuration(750);
        rotate->setStartValue(0);
        rotate->setEndValue(90);
        rotate->setEasingCurve(QEasingCurve::InOutExpo);
        rotate->start();
        curSettingsPage->slideIn();
        });
    layersIcon = new customIcon(ICON_FILE "layers.svg", "layers", 5, this);
    layersIcon->setMinimumHeight(canvasTitle->height() * 0.7);
    layersIcon->setMaximumWidth(canvasTitle->height() * 0.7);

    /* create title */

    QWidget* titleInnerWidget = new QWidget(this);
    titleInnerWidget->setFixedHeight(canvasTitle->height());
    QHBoxLayout* innerLayout = new QHBoxLayout(titleInnerWidget);
    titleInnerWidget->setLayout(innerLayout);
    innerLayout->setContentsMargins(0, 0, 0, 0);
    innerLayout->setSpacing(10);
    innerLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    innerLayout->addWidget(canvasTitle);
    innerLayout->addWidget(settingsIcon);
    innerLayout->addWidget(layersIcon);

    QWidget* titleWidget = new QWidget(this);
    titleWidget->setMaximumHeight(canvasTitle->height() + canvasDesc->height());
    QVBoxLayout* outerLayout = new QVBoxLayout(titleWidget);
    titleWidget->setLayout(outerLayout);
    outerLayout->setContentsMargins(0, 0, 0, 0);
    outerLayout->setSpacing(0);
    outerLayout->addWidget(titleInnerWidget);
    outerLayout->addWidget(canvasDesc);

    /* create default page */

    defaultPage = new QWidget(_windowWidget);
    defaultPage->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    bigIconButton* createNew = new bigIconButton(ICON_FILE "create.png", "Create new", 10, this);
    createNew->setScale(0.9);
    bigIconButton* openFile = new bigIconButton(ICON_FILE "open.png", "Open from file", 10, this);
    QHBoxLayout* defaultPageLayout = new QHBoxLayout(defaultPage);
    defaultPage->setLayout(defaultPageLayout);
    defaultPageLayout->setContentsMargins(50, 30, 50, 80);
    defaultPageLayout->setSpacing(20);
    defaultPageLayout->addWidget(createNew);
    defaultPageLayout->addWidget(openFile);

    //-------------------------------------------------------------------
    /* create layers page */
    textInputItem* rename = new textInputItem("Name:", createNewPage);
    rename->setValue("Layer_" + QString::asprintf("%d", 11111));
    textInputItem* redescribe = new textInputItem("Detail:", createNewPage);
    redescribe->setValue("No description");

    layersPage = new SlidePage(cornerRadius, "LAYERS", _windowWidget);
    layersPage->stackUnder(createNewPage);
    connect(layersIcon, &customIcon::clicked, layersPage, &SlidePage::slideIn);
    layerSel = new singleSelectGroup("Layers", layersPage);
    connect(layerSel, &singleSelectGroup::itemChange, layersPage, [=]() {layersPage->UpdateContents(); });
    textButton* openFileBtn = new textButton("Open file", layersPage);
    textButton* addNewBtn = new textButton("Create new", layersPage);
    layersPage->AddContent(addNewBtn);
    layersPage->AddContent(openFileBtn);
    layersPage->AddContent(layerSel);
    connect(addNewBtn, &textButton::clicked, this, [=]() {rename->setValue("Layer_" + QString::asprintf("%d", 100)); redescribe->setValue("No description"); createNewPage->slideIn(); });
    layersPage->show();
    pageList.push_back(layersPage);

    /* create add new slide page */
    createNewPage = new SlidePage(cornerRadius, "CREATE CANVAS", _windowWidget);
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
    selectionItem* newLayer = new selectionItem("ylhhdrgdg", "dwadadadjaida", layersPage);
    layerSel->AddItem(newLayer);
    layerSel->SetSelection(newLayer);
    createNewPage->AddContent(submit);
    createNewPage->AddContent(dirSel);
    createNewPage->AddContent(structureSel);
    createNewPage->AddContent(whiteSpace);
    createNewPage->AddContent(redescribe);
    createNewPage->AddContent(rename);
    connect(createNew, &bigIconButton::clicked, createNewPage, [=]() {
        rename->setValue("Layer_" + QString::asprintf("%d", 100));
        redescribe->setValue("No description");
        createNewPage->slideIn(); }
    );
    createNewPage->show();
    pageList.push_back(createNewPage);

    _homePage->layout()->addWidget(titleWidget);
    _homePage->layout()->addWidget(defaultPage);
    _homePage->layout()->setAlignment(Qt::AlignTop);
}

#endif

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