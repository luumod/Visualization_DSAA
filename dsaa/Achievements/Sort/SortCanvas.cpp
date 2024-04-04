#include "SortCanvas.h"
#include "SortObject.h"
#include "SortFactory.h"
#include "Components/horizontalValueAdjuster.h"
#include "Components/textButton.h"
#include "Components/singleSelectGroup.h"
#include "Components/textInputItem.h"
#include "Components/customScrollContainer.h"
#include "Components/slidepage.h"
#include <QPaintEvent>
#include <QPainter>
#include <QHBoxLayout>
#include <QTimer>
#include <QLabel>
#include <QComboBox>
#include <QListView>
#include <QSpinBox>

SortCanvas::SortCanvas(int radius, QWidget *parent)
	: QWidget(parent)
{
	setAttribute(Qt::WA_StyledBackground, true);

	mainLayout = new QHBoxLayout(this);
	mainLayout->setContentsMargins(0, 0, 0, 0);
	this->setLayout(mainLayout);

	view = new QWidget(this);
	view->setStyleSheet("border:1px solid #cfcfcf; border-radius: 10px");
	view->setAutoFillBackground(true);
	palette.setColor(QPalette::Window, Qt::white);
	view->setPalette(palette);
	mainLayout->addWidget(view);
	
	this->setFocusPolicy(Qt::ClickFocus);

	CreateSettings(radius);
}

void SortCanvas::CreateSettings(int radius){
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
	
	QWidget* whiteSpace = new QWidget(settings);
	whiteSpace->setFixedHeight(30);

	// Sort speed rate.
	horizontalValueAdjuster* sortRate = new horizontalValueAdjuster("Sort rate", 1, 99, 1, settings);
	sortRate->setValue(20);

	// Sort data volume.
	horizontalValueAdjuster* sortDataVolume = new horizontalValueAdjuster("Sort data volume", 5, 30, 1, settings);
	sortDataVolume->setValue(10);

	textInputItem* rename = new textInputItem("Name", settings);
	rename->setValue(canvasName);

	textInputItem* redesc = new textInputItem("Detail", settings);
	redesc->setValue(canvasDescription);

	QWidget* whiteSpace2 = new QWidget(settings);
	whiteSpace2->setFixedHeight(30);

	textButton* btnStart = new textButton("Start", settings);
	textButton* btnStop = new textButton("Stop", settings);
	connect(btnStart, &textButton::clicked, settings, [=] {
		const int type = structureSetting->value();
		if (type != getSortType()) {
			SortObject* obj = SortFactory::getInstance()->createSortObject(type, this);
			setSortObject(type, obj);
		}
		//!!!!!!!
		settings->slideOut();
		sort(sortDataVolume->value(), sortRate->value());
		});
	// Clicked to stop sort.
	connect(btnStop, &textButton::clicked, this, [=] {
		settings->slideOut();
		stop();
		});

	settings->AddContent(btnStop);
	settings->AddContent(btnStart);
	settings->AddContent(whiteSpace2);
	settings->AddContent(structureSetting);
	settings->AddContent(sortDataVolume);
	settings->AddContent(sortRate);
	settings->AddContent(whiteSpace);
	settings->AddContent(redesc);
	settings->AddContent(rename);
	settings->show();

	QTimer* delay = new QTimer(this);
	connect(delay, &QTimer::timeout, this, [=]() {Init(); });
	delay->setSingleShot(true);
	delay->start(10);
}

void SortCanvas::Init(){
	/* Create info widget */
	infoWidget = new QWidget(this);
	mainLayout->addWidget(infoWidget);
	mainLayout->setStretch(3,1);
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

	auto h2 = new QHBoxLayout;
	auto combo = new QComboBox(infoWidget);
	combo->setView(new QListView(infoWidget));
	combo->addItems(SortFactory::getInstance()->getSortList());
	auto lab = new QLabel("Sort type", infoWidget);
	h2->addWidget(lab);
	h2->addWidget(combo);

	auto h3 = new QHBoxLayout;
	auto spinCount = new QSpinBox(infoWidget);
	spinCount->setRange(1, 100);
	spinCount->setValue(10);
	auto lab2 = new QLabel("Number of data:", infoWidget);
	h3->addWidget(lab2);
	h3->addWidget(spinCount);

	auto h4 = new QHBoxLayout;
	auto spinInterval = new QSpinBox(infoWidget);
	spinInterval->setValue(10);
	auto lab3 = new QLabel("Operate interval", infoWidget);
	h4->addWidget(lab3);
	h4->addWidget(spinInterval);

	upperLayout->addLayout(h2);
	upperLayout->addLayout(h3);
	upperLayout->addLayout(h4);

	QHBoxLayout* twoBtnHLayout = new QHBoxLayout;
	textButton* btnStart = new textButton("Start", infoWidget);
	textButton* btnStop = new textButton("Stop", infoWidget);
	twoBtnHLayout->addWidget(btnStart);
	twoBtnHLayout->addWidget(btnStop);
	upperLayout->addLayout(twoBtnHLayout);

	//connect(btnStart, &textButton::clicked, this, [=] {
	//	const int type = combo->currentIndex();
	//	if (type != getSortType()) {
	//		SortObject* obj = SortFactory::getInstance()->createSortObject(type, parent());
	//		setSortObject(type, obj);
	//	}
	//	sort(spinCount->value(), spinInterval->value());
	//});
	//// Clicked to stop sort.
	//connect(btnStop, &textButton::clicked, this, [=] {
	//	stop();
	// });

	// When sorting, user can't modified these thing.
	connect(this, &SortCanvas::runFlagChanged,
		this, [=](bool running) {
			combo->setEnabled(!running);
			spinCount->setEnabled(!running);
			spinInterval->setEnabled(!running);
			btnStart->setEnabled(!running);
		});

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

	/*
	--------------------------------------------------------------
	--------------------------------------------------------------
	--------------------------------------------------------------
	----------------------------Settings--------------------------
	--------------------------------------------------------------
	--------------------------------------------------------------
	--------------------------------------------------------------
	*/
	//1. Choice different sort type.

	//2. Adjust different interval.

	//3. Adjust different the number of elements for array.

}

int SortCanvas::getSortType() const
{
	return sortType;
}

void SortCanvas::setSortObject(int type, SortObject *obj)
{
	if (sortType == type) {
		return;
	}
	if (sortObj) {
		sortObj->deleteLater();
		sortObj = nullptr;
	}

	sortType = type;
	sortObj = obj;

	if (sortObj) {
		connect(sortObj, &SortObject::updateToDraw, this, [this]{
			update();
		});
		connect(sortObj, &SortObject::runFlagChanged, this, &SortCanvas::runFlagChanged);
	}
	update();
}

void SortCanvas::sort(int count, int interval)
{
	if (sortObj) {
		sortObj->sort(count, interval);
	}
}

void SortCanvas::stop()
{
	if (sortObj) {
		sortObj->stop();
	}
}

void SortCanvas::paintEvent(QPaintEvent *event)
{
	if (view == nullptr) {
		return;
	}

	event->accept();

	QPainter painter(this);
	setPalette(palette);

	if (sortObj) {
		sortObj->draw(&painter, view->width(), view->height());
	}
}
