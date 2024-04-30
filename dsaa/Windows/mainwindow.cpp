#ifndef DASS_VERSION
#define DASS_VERSION

#include "mainwindow.h"
#include "sidebar.h"
#include "singleSelectGroup.h"
#include "logger.h"
#include "common.h"
#include "pushbutton.h"
#include "textButton.h"
#include "textInputItem.h"
#include "bigIconButton.h"
#include "customIcon.h"
#include "sortpage.h"
#include "graphpage.h"
#include "staquepage.h"
#include "greedpage.h"
#include "aboutpage.h"
#include "linkedlistpage.h"
#include "slidepage.h"
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
#if DEBUG
	Logger::debug("Begin initialized MainWindow");
#endif // DEBUG
	this->setMouseTracking(true);
	this->resize(1250, 750);

	// Create main layout for page and sidebar
	_mainLayout = new QHBoxLayout(_FwindowWidget);
	_mainLayout->setContentsMargins(0, 0, 0, 0);
	_mainLayout->setSpacing(0);
	_FwindowWidget->setLayout(_mainLayout);

	// Create placeholder widget for pages
	_placeHolderWidget = new QWidget(_FwindowWidget);
	_placeHolderWidget->setObjectName("placeHolderWidget");
	_placeHolderWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	_placeHolderWidget->setMouseTracking(true);

	/*
	Connect the resize event of the placeholder widget to the resizePages function using event filter
	The event filter function in the MainWindow class is called when placeHolderWidget receives events to handle them.
	*/
	_placeHolderWidget->installEventFilter(this);
	
	// Create sidebar
	_sideBar = new SideBar(_FwindowWidget);

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

	// Add sort page and connect to side bar.
	_sortPage = new SortPage(_placeHolderWidget);
	_sortPage->setMouseTracking(true);
	_sideBar->addPage(_sortPage);

	// Add graph page and connect to side bar.
	_graphPage = new GraphPage(_placeHolderWidget);
	_graphPage->setMouseTracking(true);
	_sideBar->addPage(_graphPage);

	_listPage = new LinkedListPage(_placeHolderWidget);
	_listPage->setMouseTracking(true);
	_sideBar->addPage(_listPage);

	_staquePage = new StaquePage(_placeHolderWidget);
	_staquePage->setMouseTracking(true);
	_sideBar->addPage(_staquePage);

	_greedPage = new GreedPage(_placeHolderWidget);
	_greedPage->setMouseTracking(true);
	_sideBar->addPage(_greedPage);

	// Create about page and connect to side bar
	_aboutPage = new AboutPage(_placeHolderWidget);
	_aboutPage->setMouseTracking(true);
	_sideBar->addPage(_aboutPage);

#if DEBUG
	Logger::debug("------- End initialized MainWindow -------");
#endif // DEBUG
}

MainWindow::~MainWindow() {
}

void MainWindow::resizeEvent(QResizeEvent* event) {
	if (event == nullptr) {
		return;
	}
	FramelessWindow::resizeEvent(event);

	QSize newSize = QSize(event->size().width() - _sideBar->size().width() - 62 ,event->size().height() - 62);

	_placeHolderWidget->resize(newSize);
	_sortPage->resize(newSize);
	_graphPage->resize(newSize);
	_listPage->resize(newSize);
	_staquePage->resize(newSize);
	_greedPage->resize(newSize);
	_aboutPage->resize(newSize);

	_sortPage->autoResizeSettingsPage();
	_graphPage->autoResizeSettingsPage();
	_listPage->autoResizeSettingsPage();
	_staquePage->autoResizeSettingsPage();
	_greedPage->autoResizeSettingsPage();

#if DEBUG
	Logger::debug(QString("MainWindow::resizeEvent: (%1,%2)").arg(event->size().width()).arg(event->size().height()));
	Logger::debug(QString("MainWindow->placeHolderWidget::resize: (%1,%2)").arg(_placeHolderWidget->width()).arg(_placeHolderWidget->height()));
	Logger::debug(QString("MainWindow->sideBar::resize: (%1,%2)").arg(_sideBar->width()).arg(_sideBar->height()));
	Logger::debug(QString("-------------------------------------"));
#endif
}


void MainWindow::resizePages(QResizeEvent* event) {
	// Check for input validity
	if (event == nullptr) {
		return;
	}

	// Get the size of the placeholder widget
	QSize size = event->size();
	// Resize pages.
	_sortPage->resize(size);
	_graphPage->resize(size);
	_listPage->resize(size);
	_staquePage->resize(size);
	_greedPage->resize(size);
	_aboutPage->resize(size);
}

void MainWindow::showEvent(QShowEvent* event) {
	// Call parent show event
	FramelessWindow::showEvent(event);

	// Resize all the pages based on the placeholder widget
	_sortPage->resize(_placeHolderWidget->size());
	_graphPage->resize(_placeHolderWidget->size());
	_listPage->resize(_placeHolderWidget->size());
	_staquePage->resize(_placeHolderWidget->size());
	_greedPage->resize(_placeHolderWidget->size());
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