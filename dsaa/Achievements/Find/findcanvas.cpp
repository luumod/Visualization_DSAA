#include "findcanvas.h"
#include "findview.h"
#include "slidepage.h"
#include "spinbox.h"
#include "textInputItem.h"
#include "textButton.h"
#include "findviewlog.h"
#include "singleSelectGroup.h"
#include "customScrollContainer.h"
#include "logger.h"
#include "common.h"
#include <QPainter>
#include <QColor>
#include <QList>
#include <QHBoxLayout>
#include <QTimer>
#include <QLabel>
#include <QPaintEvent>
#include <QLineEdit>
#include <QRegularExpressionValidator>
#include <QRandomGenerator>
#include <QColorDialog>
#include <QButtonGroup>
#include <QScrollArea>

FindCanvas::FindCanvas(int radius, QString name, QString desc, QWidget* parent)
	:QWidget(parent),
	canvasName(name),
	canvasDescription(desc)
{
	setAttribute(Qt::WA_StyledBackground, true);

	mainLayout = new QHBoxLayout(this);
	mainLayout->setContentsMargins(0, 0, 0, 0);
	this->setLayout(mainLayout);

	view = new FindView;
	view->setSceneRect(view->rect());
	view->setStyleSheet("background-color: #FFFFFF;border:1px solid #cfcfcf;border-radius:10px;");
	mainLayout->addWidget(view);
	
	this->setFocusPolicy(Qt::ClickFocus);

	CreateSettings(radius);
}

FindCanvas::~FindCanvas()
{
}
void FindCanvas::CreateSettings(int radius)
{
	/* create settings page */
	settings = new SlidePage(radius, "SETTINGS", this->parentWidget());

	QWidget* spacingLine = new QWidget(this);
	spacingLine->setFixedHeight(1);
	spacingLine->setStyleSheet("background-color:#0a000000");

	QWidget* whiteSpace = new QWidget(settings);
	whiteSpace->setFixedHeight(30);

	// Adjust attributes panel for the node.
	SpinBoxGroup* adjust_spin_group = new SpinBoxGroup("Adjust panel", settings);
	SpinBox* spin_text_size = new SpinBox("Text size",1,30,13, settings);
	adjust_spin_group->AddItem(spin_text_size);
	connect(spin_text_size, &SpinBox::valueChanged, this, [=](int value) {
		view->updateTextSize(value);
	});

	textInputItem* rename = new textInputItem("Set name", settings);
	rename->setValue(canvasName);
	connect(rename, &textInputItem::textEdited, this, [=](QString text) {
		canvasName = text;
		emit nameChanged(text);
#if DEBUG
		Logger::debug(QString(" page rename: %1").arg(text));
#endif
		});

	textInputItem* redesc = new textInputItem("Set detail", settings);
	redesc->setValue(canvasDescription);
	connect(redesc, &textInputItem::textEdited, this, [=](QString text) {
		canvasDescription = text;
		emit descChanged(text);
#if DEBUG
		Logger::debug(QString(" page rename: %1").arg(text));
#endif
		});

	QWidget* whiteSpace2 = new QWidget(settings);
	whiteSpace2->setFixedHeight(30);

	QWidget* whiteSpace_on = new QWidget(settings);
	whiteSpace_on->setFixedHeight(10);

	settings->AddContent(whiteSpace2);
	settings->AddContent(spacingLine);
	settings->AddContent(adjust_spin_group);
	settings->AddContent(whiteSpace);
	settings->AddContent(redesc);
	settings->AddContent(rename);
	settings->show();

	QTimer* delay = new QTimer(this);
	connect(delay, &QTimer::timeout, this, [=]() {Init(); });
	delay->setSingleShot(true);
	delay->start(10);
}

void FindCanvas::Init()
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
	textInputItem* textName = new textInputItem("Title", defInfoPage);
	textName->setValue(canvasName);
	connect(this, &FindCanvas::nameChanged, this, [=]() {textName->setValue(canvasName); });
	textName->setEnabled(false);
	// Canvas description.
	textInputItem* textDesc = new textInputItem("Detail", defInfoPage);
	textDesc->setValue(canvasDescription);
	connect(this, &FindCanvas::descChanged, this, [=]() {textDesc->setValue(canvasDescription); });
	textDesc->setEnabled(false);

	// push 
	textInputItem* input_push = new textInputItem("input", defInfoPage);
	textButton* btn_random_data = new textButton("Random", defInfoPage);
	textButton* btn_push_back = new textButton("Push back", defInfoPage);
	textButton* btn_push_front = new textButton("Push front", defInfoPage);
	textButton* btn_pop_back = new textButton("Pop back", defInfoPage);
	textButton* btn_pop_front = new textButton("pop front", defInfoPage);
	textButton* btn_random_gen = new textButton("Random generate", defInfoPage);
	textButton* btn_clear_all = new textButton("Clear array", defInfoPage);
	QWidget* widget_push = new QWidget(defInfoPage);
	widget_push->setObjectName("DefTextItems");
	widget_push->setStyleSheet("QWidget#DefTextItems{border:1px solid #cfcfcf;border-radius:5px;}");
	QGridLayout* layout_push = new QGridLayout(widget_push);
	widget_push->setLayout(layout_push);
	layout_push->addWidget(input_push, 0, 0, 1, 3);
	layout_push->addWidget(btn_random_data, 0, 3, 1, 1);
	layout_push->addWidget(btn_push_back, 1, 0, 1, 2);
	layout_push->addWidget(btn_push_front, 1, 2, 1, 2);
	layout_push->addWidget(btn_pop_back, 2, 0, 1, 2);
	layout_push->addWidget(btn_pop_front, 2, 2, 1, 2); 
	layout_push->addWidget(btn_random_gen, 3, 0, 1, 2);
	layout_push->addWidget(btn_clear_all, 3, 2, 1, 2);
	connect(btn_random_data, &textButton::clicked, this, [=]() {
		int random_value = QRandomGenerator::global()->bounded(0, 1000);
		input_push->setValue(QString::number(random_value));
		});
	connect(btn_push_back, &textButton::clicked, this, [=]() {
		if (!input_push->value().isEmpty()) {
			auto val = input_push->value().toInt();
			view->on_push_back(val);
			logDisplay->addWidget(new FindViewLog(QString("[array] push_back: %1").arg(val), logDisplay));
		}
		});
	connect(btn_push_front, &textButton::clicked, this, [=]() {
		if (!input_push->value().isEmpty()) {
			auto val = input_push->value().toInt();
			view->on_push_front(val);
			logDisplay->addWidget(new FindViewLog(QString("[array] push_front: %1").arg(val), logDisplay));
		}
		});
	connect(btn_pop_back, &textButton::clicked, this, [=]() {
		try {
			int value = view->on_pop_back();
			logDisplay->addWidget(new FindViewLog(QString("[array] pop_back : %1").arg(value), logDisplay));
		}
		catch (const std::exception&) {
			logDisplay->addWidget(new FindViewLog(QString("[array] array is empty!!!"), logDisplay));
		}

		});
	connect(btn_pop_front, &textButton::clicked, this, [=]() {
		try {
			int value = view->on_pop_front();
			logDisplay->addWidget(new FindViewLog(QString("[array] pop_front : %1").arg(value), logDisplay));
		}
		catch (const std::exception&) {
			logDisplay->addWidget(new FindViewLog(QString("[array] array is empty!!!"), logDisplay));
		}

		});
	connect(btn_random_gen, &textButton::clicked, this, [=]() {
		std::size_t size = QRandomGenerator::global()->bounded(20);
		view->clear();
		for (int i = 0; i < size; i++) {
			auto num = QRandomGenerator::global()->bounded(1000);
			view->on_push_back(num);
			logDisplay->addWidget(new FindViewLog(QString("[array] push_front: %1").arg(num), logDisplay));
		}
		});
	connect(btn_clear_all, &textButton::clicked, this, [=]() {
		view->clear();
		});
	

	// user input
	// push 
	/*textInputItem* input_custom = new textInputItem("custom", defInfoPage);
	textButton* btn_custom_stack = new textButton("To stack", defInfoPage);
	textButton* btn_custom_queue = new textButton("To queue", defInfoPage);
	QWidget* widget_custom = new QWidget(defInfoPage);
	widget_custom->setObjectName("DefTextItems");
	widget_custom->setStyleSheet("QWidget#DefTextItems{border:1px solid #cfcfcf;border-radius:5px;}");
	QGridLayout* layout_custom = new QGridLayout(widget_custom);
	widget_custom->setLayout(layout_custom);
	layout_custom->addWidget(input_custom, 0, 0, 1, 4);
	layout_custom->addWidget(btn_custom_stack, 1, 0, 1, 2);
	layout_custom->addWidget(btn_custom_queue, 1, 2, 1, 2);
	connect(btn_custom_stack, &textButton::clicked, this, [=]() {
		if (!input_custom->value().isEmpty()) {
			QStringList input = input_custom->value().split(" ");
			QVector<int> arr;
			for (auto& x : input) {
				arr.append(x.toInt());
				view->on_stack_push(x.toInt());
			}
			logDisplay->addWidget(new FindViewLog(QString("[stack] construct: %1").arg(input_custom->value()), logDisplay));
		}
	});
	connect(btn_custom_queue, &textButton::clicked, this, [=]() {
		if (!input_custom->value().isEmpty()) {
			QStringList input = input_custom->value().split(" ");
			QVector<int> arr;
			for (auto& x : input) {
				arr.append(x.toInt());
				view->on_queue_push(x.toInt());
			}
			logDisplay->addWidget(new FindViewLog(QString("[queue] construct: %1").arg(input_custom->value()), logDisplay));
		}
		});*/

	defTextLayout->addWidget(textName);
	defTextLayout->addWidget(textDesc);
	defTextLayout->addWidget(widget_push);
	//defTextLayout->addWidget(widget_custom);
	//defTextLayout->addWidget(widget_pop);

	defInfoLayout->addWidget(defTextItems);
	upperLayout->addWidget(defInfoPage);
	defInfoPage->show();

	//--------------------------------

	infoLayout->addWidget(upper);
	infoLayout->addWidget(lower);


	connect(view, &FindView::logAdded, this, [=](FindViewLog* log) {logDisplay->addWidget(log); });
}

