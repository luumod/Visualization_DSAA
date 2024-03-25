#ifndef DASS_VERSION
#define DASS_VERSION


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

	// ÑÓ³Ù¹¹Ôì£¿
	QTimer* t = new QTimer(this);
	connect(t, &QTimer::timeout, this, [=]() {Init(); });
	t->setSingleShot(true);
	t->start(10);
}

MainWindow::~MainWindow() {
}

void MainWindow::Init() {
	/* create default page */
	defaultPage = new QWidget(_windowWidget);
	defaultPage->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	bigIconButton* sortAlgorithmBtn = new bigIconButton(ICON_FILE "sort.png", "Sort Algorithm", 10, this);
	sortAlgorithmBtn->setScale(0.9);
	bigIconButton* openFile = new bigIconButton(ICON_FILE "open.png", "Open from file", 10, this);
	QHBoxLayout* defaultPageLayout = new QHBoxLayout(defaultPage);
	defaultPage->setLayout(defaultPageLayout);
	defaultPageLayout->setContentsMargins(50, 30, 50, 80);
	defaultPageLayout->setSpacing(20);
	defaultPageLayout->addWidget(sortAlgorithmBtn);
	defaultPageLayout->addWidget(openFile);

	//-------------------------------------------------------------------
	textInputItem* rename = new textInputItem("Name:", createNewPage);
	rename->setValue("Layer_" + QString::asprintf("%d", 11111));
	textInputItem* redescribe = new textInputItem("Detail:", createNewPage);
	redescribe->setValue("No description");

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
	createNewPage->AddContent(submit);
	createNewPage->AddContent(dirSel);
	createNewPage->AddContent(structureSel);
	createNewPage->AddContent(whiteSpace);
	createNewPage->AddContent(redescribe);
	createNewPage->AddContent(rename);
	connect(sortAlgorithmBtn, &bigIconButton::clicked, createNewPage, [=]() {
		rename->setValue("Layer_" + QString::asprintf("%d", 100));
		redescribe->setValue("No description");
		createNewPage->slideIn(); 
	});
	createNewPage->show();
	pageList.push_back(createNewPage);

	_homePage->layout()->addWidget(defaultPage);
	_homePage->layout()->setAlignment(Qt::AlignTop);
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