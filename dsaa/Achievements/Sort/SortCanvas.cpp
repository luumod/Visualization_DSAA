#include "SortCanvas.h"
#include "logger.h"
#include "common.h"
#include "SortObject.h"
#include "SortFactory.h"
#include "sortviewlog.h"
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
#include <QColorDialog>
#include "BubbleSort.h"

SortCanvas::SortCanvas(int radius, QString name, QString desc, QWidget *parent)
	:QWidget(parent),
	canvasName(name),
	canvasDescription(desc)
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
	connect(structureSetting, &singleSelectGroup::selectedItemChange, this, [=](int index) {
		switch (index)
		{
		case 0:
			emit typeChanged("Bubble Sort");
			break;
		case 1:
			emit typeChanged("Selection Sort");
			break;
		case 2:
			emit typeChanged("Insertion Sort");
			break;
		case 3:
			emit typeChanged("Quick Sort");
			break;
		case 4:
			emit typeChanged("Shell Sort");
			break;
		}
	});
	
	QWidget* whiteSpace = new QWidget(settings);
	whiteSpace->setFixedHeight(30);

	// Sort speed rate.
	horizontalValueAdjuster* sortInterval = new horizontalValueAdjuster("Sort interval", 1, 99, 1, settings);
	sortInterval->setValue(20);
	connect(sortInterval, &horizontalValueAdjuster::valueChanged, view, [=](qreal value) {
		setInterval(value);
		emit intervalChanged(QString::number(value));
#if DEBUG
		Logger::debug(QString("Sort Interval Changed: %1").arg(value));
#endif
	});
	
	// Sort data volume.
	horizontalValueAdjuster* sortDataVolume = new horizontalValueAdjuster("Sort data volume", 5, 30, 1, settings);
	sortDataVolume->setValue(10);
	connect(sortDataVolume, &horizontalValueAdjuster::valueChanged, view, [=](qreal value) {
		setDataVolume(value);
		emit volumeChanged(QString::number(value));
#if DEBUG
		Logger::debug(QString("Sort Volume Changed: %1").arg(value));
#endif
	});

	textInputItem* rename = new textInputItem("Name", settings);
	rename->setValue(canvasName);
	connect(rename, &textInputItem::textEdited, this, [=](QString text) {
		canvasName = text; 
		emit nameChanged(text); 
#if DEBUG
		Logger::debug(QString("Sort page rename: %1").arg(text));
#endif
		});

	textInputItem* redesc = new textInputItem("Detail", settings);
	redesc->setValue(canvasDescription);
	connect(redesc, &textInputItem::textEdited, this, [=](QString text) {
		canvasDescription = text; 
		emit descChanged(text);
#if DEBUG
		Logger::debug(QString("Sort page redesc: %1").arg(text));
#endif
	});

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
		setInterval(sortInterval->value());
		setDataVolume(sortDataVolume->value());
		settings->slideOut();
		sort();
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

void SortCanvas::Init(){
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
	connect(this, &SortCanvas::nameChanged, this, [=]() {textName->setValue(canvasName); });
	textName->setEnabled(false);
	// Canvas description.
	textInputItem* textDesc = new textInputItem("Detail", defInfoPage);
	textDesc->setValue(canvasDescription);
	connect(this, &SortCanvas::descChanged, this, [=]() {textDesc->setValue(canvasDescription); });
	textDesc->setEnabled(false);
	// Sort type.
	textInputItem* sortType = new textInputItem("Type", defInfoPage);
	sortType->setValue(canvasSortType);
	connect(this, &SortCanvas::typeChanged, this, [=](QString value) {
		sortType->setValue(value);
	});
	textName->setEnabled(false);
	// Sort interval.
	textInputItem* interval = new textInputItem("Interval", defInfoPage);
	interval->setValue(canvasSortInterval);
	connect(this, &SortCanvas::intervalChanged, this, [=](QString value) {interval->setValue(value); });
	interval->setEnabled(false);
	// Sort volume.
	textInputItem* volume = new textInputItem("Volume", defInfoPage);
	volume->setValue(canvasSortVolume);
	connect(this, &SortCanvas::volumeChanged, this, [=](QString value) {volume->setValue(value); });
	volume->setEnabled(false);


	defTextLayout->addWidget(textName);
	defTextLayout->addWidget(textDesc);
	defTextLayout->addWidget(sortType);
	defTextLayout->addWidget(interval);
	defTextLayout->addWidget(volume);

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
	logDisplay = new ScrollAreaCustom(lower);
	logDisplay->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	lowerLayout->addWidget(logLabel);
	lowerLayout->addWidget(lowerSplitter);
	lowerLayout->addWidget(logDisplay);

	

	infoLayout->addWidget(upper);
	infoLayout->addWidget(lower);

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
		connect(sortObj, &SortObject::finishedEachIteration, this, [=](QVector<int> arr) {
			QStringList stringList;
			for (int i = 0; i < arr.size(); ++i) {
				stringList << QString::number(arr[i]);
			}
			QString result = stringList.join(" ");
			logDisplay->addWidget(new SortViewLog(QString("[Iteration]: %1").arg(result), logDisplay));
			});
	}
	update();
}

void SortCanvas::sort()
{
	if (sortObj) {
		sortObj->sort(volume, interval);
	}
}

void SortCanvas::stop()
{
	if (sortObj) {
		sortObj->stop();
	}
}

void SortCanvas::setInterval(int interval){
	this->interval = interval;
}

void SortCanvas::setDataVolume(int dataVolume){
	this->volume = dataVolume;
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