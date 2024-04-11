#include "linkedlistcavnas.h"
#include "slidepage.h"
#include "singleSelectGroup.h"
#include "horizontalValueAdjuster.h"
#include "textInputItem.h"
#include "textButton.h"
#include "customScrollContainer.h"
#include "doubly_linked_list.h"
#include "linkedlistview.h"
#include <QPainter>
#include <QList>
#include <QHBoxLayout>
#include <QTimer>
#include <QLabel>
#include <QPaintEvent>


LinkedListCanvas::LinkedListCanvas(int radius, QString name, QString desc, QWidget* parent)
	:QWidget(parent),
	canvasName(name),
	canvasDescription(desc)
{
	setAttribute(Qt::WA_StyledBackground, true);

	mainLayout = new QHBoxLayout(this);
	mainLayout->setContentsMargins(0, 0, 0, 0);
	this->setLayout(mainLayout);

	view = new LinkedListView(this);
	view->setStyleSheet("border:1px solid #cfcfcf; border-radius: 10px");
	view->setAutoFillBackground(true);
	palette.setColor(QPalette::Window, Qt::white);
	view->setPalette(palette);
	mainLayout->addWidget(view);
	
	this->setFocusPolicy(Qt::ClickFocus);

	CreateSettings(radius);
}

LinkedListCanvas::~LinkedListCanvas()
{
}
void LinkedListCanvas::CreateSettings(int radius)
{
	/* create settings page */
	settings = new SlidePage(radius, "SETTINGS", this->parentWidget());
	singleSelectGroup* structureSetting = new singleSelectGroup("Sort Algorithms", settings);
	selectionItem* setBubble = new selectionItem("Bubble", "Adjacent list structure", settings);
	selectionItem* setSelection = new selectionItem("Selection", "Adjacent multiple list", settings);
	selectionItem* setInsertion = new selectionItem("Insertion", "Adjacent multiple list", settings);
	selectionItem* setQuick = new selectionItem("Quick", "Adjacent multiple list", settings);
	selectionItem* setShell = new selectionItem("Shell", "Adjacent multiple list", settings);
	structureSetting->AddItem(setBubble);
	structureSetting->AddItem(setSelection);
	structureSetting->AddItem(setInsertion);
	structureSetting->AddItem(setQuick);
	structureSetting->AddItem(setShell);
	connect(structureSetting, &singleSelectGroup::selectedItemChange, this, [=](int index) {
		
		});

	QWidget* whiteSpace = new QWidget(settings);
	whiteSpace->setFixedHeight(30);

	// Sort speed rate.
	horizontalValueAdjuster* sortInterval = new horizontalValueAdjuster("Sort interval", 1, 99, 1, settings);
	sortInterval->setValue(20);
	connect(sortInterval, &horizontalValueAdjuster::valueChanged, view, [=](qreal value) {
		
		});

	// Sort data volume.
	horizontalValueAdjuster* sortDataVolume = new horizontalValueAdjuster("Sort data volume", 5, 30, 1, settings);
	sortDataVolume->setValue(10);
	connect(sortDataVolume, &horizontalValueAdjuster::valueChanged, view, [=](qreal value) {
		
		});

	textInputItem* rename = new textInputItem("Name", settings);
	rename->setValue(canvasName);
	connect(rename, &textInputItem::textEdited, this, [=](QString text) {
		
		});

	textInputItem* redesc = new textInputItem("Detail", settings);
	redesc->setValue(canvasDescription);
	connect(redesc, &textInputItem::textEdited, this, [=](QString text) {
		
		});

	QWidget* whiteSpace2 = new QWidget(settings);
	whiteSpace2->setFixedHeight(30);

	textButton* btnStart = new textButton("Start", settings);
	textButton* btnStop = new textButton("Stop", settings);
	connect(btnStart, &textButton::clicked, settings, [=] {
		
		});
	// Clicked to stop sort.
	connect(btnStop, &textButton::clicked, this, [=] {
		
		});

	settings->AddContent(btnStop);
	settings->AddContent(btnStart);
	settings->AddContent(whiteSpace2);
	settings->AddContent(structureSetting);
	settings->AddContent(sortDataVolume);
	settings->AddContent(sortInterval);
	settings->AddContent(whiteSpace);
	settings->AddContent(redesc);
	settings->AddContent(rename);
	settings->show();

	QTimer* delay = new QTimer(this);
	connect(delay, &QTimer::timeout, this, [=]() {Init(); });
	delay->setSingleShot(true);
	delay->start(10);
}

void LinkedListCanvas::Init()
{
	/* Create info widget */
	infoWidget = new QWidget(this);
	mainLayout->addWidget(infoWidget);
	mainLayout->setStretch(0, 7);
	mainLayout->setStretch(1, 3);
	infoWidget->setMinimumWidth(250);
	infoWidget->setMaximumWidth(500);

	//Set basic layout
	QVBoxLayout* infoLayout = new QVBoxLayout(infoWidget);
	infoWidget->setLayout(infoLayout);
	infoLayout->setContentsMargins(10, 0, 0, 0);
	infoLayout->setAlignment(Qt::AlignTop);

	QFont titleFont = QFont("Corbel", 20);

	QWidget* upper = new QWidget(infoWidget);
	QVBoxLayout* upperLayout = new QVBoxLayout(upper);
	upper->setLayout(upperLayout);
	upperLayout->setContentsMargins(0, 0, 0, 0);
	upper->setContentsMargins(0, 0, 0, 0);
	pageName = new QLabel(infoWidget);
	pageName->setText("INFO");
	pageName->setFont(titleFont);
	pageName->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	pageName->setStyleSheet("color:#2c2c2c");
	QWidget* upperSeparate = new QWidget(upper);
	upperSeparate->setFixedSize(30, 6);
	upperSeparate->setStyleSheet("background-color:#3c3c3c;border-radius:3px;");
	upperLayout->addWidget(pageName);
	upperLayout->addWidget(upperSeparate);

	QWidget* defInfoPage = new QWidget(infoWidget);
	QVBoxLayout* defInfoLayout = new QVBoxLayout(defInfoPage);
	defInfoPage->setLayout(defInfoLayout);
	defInfoLayout->setContentsMargins(0, 0, 0, 0);
	defInfoLayout->setAlignment(Qt::AlignTop);

	QWidget* defTextItems = new QWidget(defInfoPage);
	defTextItems->setObjectName("DefTextItems");
	defTextItems->setStyleSheet("QWidget#DefTextItems{border:1px solid #cfcfcf;border-radius:5px;}");
	QVBoxLayout* defTextLayout = new QVBoxLayout(defTextItems);
	defTextItems->setLayout(defTextLayout);
	defTextLayout->setContentsMargins(0, 5, 0, 5);

	// Canvas name.
	textInputItem* textName = new textInputItem("Name", defInfoPage);
	textName->setValue(canvasName);
	//connect(this, &SortCanvas::nameChanged, this, [=]() {textName->setValue(canvasName); });
	textName->setEnabled(false);
	// Canvas description.
	textInputItem* textDesc = new textInputItem("Detail", defInfoPage);
	textDesc->setValue(canvasDescription);
	//connect(this, &SortCanvas::descChanged, this, [=]() {textDesc->setValue(canvasDescription); });
	textDesc->setEnabled(false);
	// Sort type.
	textInputItem* sortType = new textInputItem("Type", defInfoPage);
	sortType->setValue(canvasSortType);
	//connect(this, &SortCanvas::typeChanged, this, [=](QString value) {sortType->setValue(value); });
	textName->setEnabled(false);
	// Sort interval.
	textInputItem* interval = new textInputItem("Interval", defInfoPage);
	interval->setValue(canvasSortInterval);
	//connect(this, &SortCanvas::intervalChanged, this, [=](QString value) {interval->setValue(value); });
	interval->setEnabled(false);
	// Sort volume.
	textInputItem* volume = new textInputItem("Volume", defInfoPage);
	volume->setValue(canvasSortVolume);
	//connect(this, &SortCanvas::volumeChanged, this, [=](QString value) {volume->setValue(value); });
	volume->setEnabled(false);

	textButton* btn = new textButton("Add Node", defInfoPage);
	textInputItem* input_add = new textInputItem("input", defInfoPage);
	
	QWidget* input_btn = new QWidget(defInfoPage);
	input_btn->setObjectName("DefTextItems");
	input_btn->setStyleSheet("QWidget#DefTextItems{border:1px solid #cfcfcf;border-radius:5px;}");
	QHBoxLayout* layout_add = new QHBoxLayout(input_btn);
	input_btn->setLayout(layout_add);
	layout_add->addWidget(input_add);
	layout_add->addWidget(btn);
	layout_add->setStretch(0, 7);
	layout_add->setStretch(1, 3);

	connect(input_add, &textInputItem::textEdited, this, [=](QString text) {
		view->listObj()->push_back(text.toInt());
		view->update();
	});
	connect(btn, &textButton::clicked, this, [=]() {
		view->listObj()->push_back(1111);
		view->update();
		});

	defTextLayout->addWidget(textName);
	defTextLayout->addWidget(textDesc);
	defTextLayout->addWidget(sortType);
	defTextLayout->addWidget(interval);
	defTextLayout->addWidget(volume);
	defTextLayout->addWidget(input_btn);

	defInfoLayout->addWidget(defTextItems);
	upperLayout->addWidget(defInfoPage);
	defInfoPage->show();

	//--------------------------------

	QWidget* lower = new QWidget(infoWidget);
	QVBoxLayout* lowerLayout = new QVBoxLayout(lower);
	lower->setLayout(lowerLayout);
	lowerLayout->setContentsMargins(0, 0, 0, 0);
	QLabel* logLabel = new QLabel(lower);
	logLabel->setText("LOG");
	logLabel->setFont(titleFont);
	logLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	logLabel->setStyleSheet("color:#2c2c2c");
	QWidget* lowerSplitter = new QWidget(lower);
	lowerSplitter->setFixedSize(30, 6);
	lowerSplitter->setStyleSheet("background-color:#3c3c3c;border-radius:3px;");
	ScrollAreaCustom* logDisplay = new ScrollAreaCustom(lower);
	logDisplay->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	lowerLayout->addWidget(logLabel);
	lowerLayout->addWidget(lowerSplitter);
	lowerLayout->addWidget(logDisplay);

	infoLayout->addWidget(upper);
	infoLayout->addWidget(lower);
}

