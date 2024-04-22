#include "staquecanvas.h"
#include "staqueview.h"
#include "slidepage.h"
#include "spinbox.h"
#include "textInputItem.h"
#include "textButton.h"
#include "staqueviewlog.h"
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

StaqueCanvas::StaqueCanvas(int radius, QString name, QString desc, QWidget* parent)
	:QWidget(parent),
	canvasName(name),
	canvasDescription(desc)
{
	setAttribute(Qt::WA_StyledBackground, true);

	mainLayout = new QHBoxLayout(this);
	mainLayout->setContentsMargins(0, 0, 0, 0);
	this->setLayout(mainLayout);

	view = new StaqueView(this);

	mainLayout->addWidget(view);
	
	this->setFocusPolicy(Qt::ClickFocus);

	CreateSettings(radius);
}

StaqueCanvas::~StaqueCanvas()
{
}
void StaqueCanvas::CreateSettings(int radius)
{
	/* create settings page */
	settings = new SlidePage(radius, "SETTINGS", this->parentWidget());
	singleSelectGroup* structureSetting = new singleSelectGroup("Linked list", settings);
	selectionItem* setSingleList = new selectionItem("Single", "Adjacent list structure", settings);
	selectionItem* setDouble = new selectionItem("Double", "Adjacent multiple list", settings);
	selectionItem* setCircular_single = new selectionItem("Circular single", "Adjacent multiple list", settings);
	selectionItem* setCircular_double = new selectionItem("Circular double", "Adjacent multiple list", settings);
	structureSetting->AddItem(setSingleList);
	structureSetting->AddItem(setDouble);
	structureSetting->AddItem(setCircular_single);
	structureSetting->AddItem(setCircular_double);
	connect(structureSetting, &singleSelectGroup::selectedItemChange, this, [=](int index) {
		
		});

	QWidget* spacingLine = new QWidget(this);
	spacingLine->setFixedHeight(1);
	spacingLine->setStyleSheet("background-color:#0a000000");

	QWidget* whiteSpace = new QWidget(settings);
	whiteSpace->setFixedHeight(30);

	// Adjust attributes panel for the node.
	SpinBoxGroup* adjust_spin_group = new SpinBoxGroup("Adjust panel", settings);
	SpinBox* spin_node_width = new SpinBox("Node Width",40,100,60, settings);
	SpinBox* spin_node_height = new SpinBox("Node Height",30,100,30, settings);
	SpinBox* spin_arrow_length = new SpinBox("Arrow Length",1,100,10, settings);
	SpinBox* spin_text_size = new SpinBox("Text Size",1,20,5, settings);
	SpinBox* spin_max_number = new SpinBox("Max number",1,10,5, settings);
	SpinBox* spin_row_spacing = new SpinBox("Row spacing",10,100,20, settings);
	adjust_spin_group->AddItem(spin_node_width);
	adjust_spin_group->AddItem(spin_node_height);
	adjust_spin_group->AddItem(spin_arrow_length);
	adjust_spin_group->AddItem(spin_text_size);
	adjust_spin_group->AddItem(spin_max_number);
	adjust_spin_group->AddItem(spin_row_spacing);
	connect(adjust_spin_group, &SpinBoxGroup::spinBoxItemChange, this, [=](int unused) {
		//// Update all inborn attributes actually, not care if your whether modified it.
		//view->updateSettings(
		//	spin_node_width->value(),
		//	spin_node_height->value(),
		//	spin_arrow_length->value(),
		//	spin_text_size->value(),
		//	spin_max_number->value(),
		//	spin_row_spacing->value());
	});
	connect(adjust_spin_group, &SpinBoxGroup::spinBoxReset, this, [=]() {
		//view->resetSettings();
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

	textButton* btnStart = new textButton("Start", settings);
	textButton* btnStop = new textButton("Stop", settings);
	connect(btnStart, &textButton::clicked, settings, [=] {
		
		});
	// Clicked to stop sort.
	connect(btnStop, &textButton::clicked, this, [=] {
		
		});
	QWidget* whiteSpace_on = new QWidget(settings);
	whiteSpace_on->setFixedHeight(10);

	QWidget* color_group_widget = new QWidget(settings);
	QHBoxLayout* layout_color_group = new QHBoxLayout(color_group_widget);
	layout_color_group->setContentsMargins(0, 0, 0, 0);
	textButton* btn_node_brush = new textButton("Set brush color", QColor(216, 240, 224).name(),settings);
	textButton* btn_arrow_color = new textButton("Set arrow color", QColor(0, 0, 0).name(), settings);
	textButton* btn_text_color = new textButton("Set text color", QColor(0, 0, 0).name(), settings);
	layout_color_group->addWidget(btn_node_brush);
	layout_color_group->addWidget(btn_arrow_color);
	layout_color_group->addWidget(btn_text_color);
	layout_color_group->setStretch(0, 3);
	layout_color_group->setStretch(1, 3);
	layout_color_group->setStretch(2, 3);
	color_group_widget->setLayout(layout_color_group);
	connect(btn_node_brush, &textButton::clicked, this, [=]() {
		QColor color = QColorDialog::getColor(Qt::white, this, "Choose a color for the node to brush.");
		if (color.isValid()) {
			btn_node_brush->setDefaultColor(color);
			//view->updateColors(btn_node_brush->defaultColor, btn_arrow_color->defaultColor, btn_text_color->defaultColor);
		}
	});
	connect(btn_arrow_color, &textButton::clicked, this, [=]() {
		QColor color = QColorDialog::getColor(Qt::white, this, "Choose a color for the arrow.");
		if (color.isValid()) {
			btn_arrow_color->setDefaultColor(color);
			//view->updateColors(btn_node_brush->defaultColor, btn_arrow_color->defaultColor, btn_text_color->defaultColor);
		}
		});
	connect(btn_text_color, &textButton::clicked, this, [=]() {
		QColor color = QColorDialog::getColor(Qt::white, this, "Choose a color for text that in the middle of node.");
		if (color.isValid()) {
			btn_text_color->setDefaultColor(color);
			//view->updateColors(btn_node_brush->defaultColor, btn_arrow_color->defaultColor, btn_text_color->defaultColor);
		}
		});

	settings->AddContent(btnStop);
	settings->AddContent(btnStart);
	settings->AddContent(whiteSpace2);
	settings->AddContent(structureSetting);
	settings->AddContent(spacingLine);
	settings->AddContent(color_group_widget);
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

void StaqueCanvas::Init()
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
	connect(this, &StaqueCanvas::nameChanged, this, [=]() {textName->setValue(canvasName); });
	textName->setEnabled(false);
	// Canvas description.
	textInputItem* textDesc = new textInputItem("Detail", defInfoPage);
	textDesc->setValue(canvasDescription);
	connect(this, &StaqueCanvas::descChanged, this, [=]() {textDesc->setValue(canvasDescription); });
	textDesc->setEnabled(false);
	
	// push 
	textInputItem* input_push = new textInputItem("input", defInfoPage);
	textButton* btn_random_data = new textButton("Random", defInfoPage);
	textButton* btn_push_stack = new textButton("Push stack", defInfoPage);
	textButton* btn_push_queue = new textButton("Push queue", defInfoPage);
	textButton* btn_push_all = new textButton("Push all", defInfoPage);
	QWidget* widget_push = new QWidget(defInfoPage);
	widget_push->setObjectName("DefTextItems");
	widget_push->setStyleSheet("QWidget#DefTextItems{border:1px solid #cfcfcf;border-radius:5px;}");
	QGridLayout* layout_push = new QGridLayout(widget_push);
	widget_push->setLayout(layout_push);
	layout_push->addWidget(input_push,0,0,1,2);
	layout_push->addWidget(btn_random_data, 0, 2,1,1);
	layout_push->addWidget(btn_push_stack,1,0);
	layout_push->addWidget(btn_push_queue,1,1);
	layout_push->addWidget(btn_push_all,1,2);
	connect(btn_random_data, &textButton::clicked, this, [=]() {
		int random_value = QRandomGenerator::global()->bounded(0, 1000);
		input_push->setValue(QString::number(random_value));
		});
	connect(btn_push_stack, &textButton::clicked, this, [=]() {
		if (!input_push->value().isEmpty()) {
			auto val = input_push->value().toInt();
			//view->stack.push(val);
			logDisplay->addWidget(new StaqueViewLog(QString("[Stack] push: %1").arg(val),logDisplay));
			update();
		}
	});
	connect(btn_push_queue, &textButton::clicked, this, [=]() {
		if (!input_push->value().isEmpty()) {
			auto val = input_push->value().toInt();
			//view->queue.enqueue(val);
			logDisplay->addWidget(new StaqueViewLog(QString("[Queue] push: %1").arg(val), logDisplay));
		}
		update();
	});
	connect(btn_push_all, &textButton::clicked, this, [=]() {
		if (!input_push->value().isEmpty()) {
			auto val = input_push->value().toInt();
			//view->stack.push(val);
			//view->queue.enqueue(val);
			logDisplay->addWidget(new StaqueViewLog(QString("[Stack] push: %1").arg(val), logDisplay));
			logDisplay->addWidget(new StaqueViewLog(QString("[Queue] push: %1").arg(val), logDisplay));
		}
		update();
	});

	// Random generate
	textButton* btn_random_stack = new textButton("Random stack", defInfoPage);
	textButton* btn_random_queue = new textButton("Random queue", defInfoPage);
	textButton* btn_random_two = new textButton("Random all", defInfoPage);
	QWidget* widget_random = new QWidget(defInfoPage);
	widget_random->setObjectName("DefTextItems");
	widget_random->setStyleSheet("QWidget#DefTextItems{border:1px solid #cfcfcf;border-radius:5px;}");
	QHBoxLayout* layout_random = new QHBoxLayout(widget_random);
	widget_random->setLayout(layout_random);
	layout_random->addWidget(btn_random_stack, 3);
	layout_random->addWidget(btn_random_queue, 3);
	layout_random->addWidget(btn_random_two, 3);
	connect(btn_random_stack, &textButton::clicked, this, [=]() {
		//view->stack.clear();
		int size = QRandomGenerator::global()->bounded(1, 10);
		for (int i = 0; i < size; i++) {
			auto val = QRandomGenerator::global()->bounded(0,1000);
			//view->stack.push(val);
		}
		update();
		});
	connect(btn_random_queue, &textButton::clicked, this, [=]() {
		//view->queue.clear();
		int size = QRandomGenerator::global()->bounded(1, 10);
		for (int i = 0; i < size; i++) {
			auto val = QRandomGenerator::global()->bounded(0, 1000);
			//view->queue.enqueue(val);
		}
		update();
		});
	connect(btn_random_two, &textButton::clicked, this, [=]() {
		//view->stack.clear();
		//view->queue.clear();
		int size = QRandomGenerator::global()->bounded(1, 10);
		for (int i = 0; i < size; i++) {
			auto val = QRandomGenerator::global()->bounded(0, 1000);
			//view->stack.push(val);
			//view->queue.enqueue(val);
		}
		update();
		});

	// pop and dequeue
	textButton* btn_pop_stack = new textButton("Pop", defInfoPage);
	textButton* btn_dequeue_queue = new textButton("Dequeue", defInfoPage);
	textButton* btn_pop_dequeue = new textButton("Pop and Dequeue", defInfoPage);
	QWidget* widget_pop = new QWidget(defInfoPage);
	widget_pop->setObjectName("DefTextItems");
	widget_pop->setStyleSheet("QWidget#DefTextItems{border:1px solid #cfcfcf;border-radius:5px;}");
	QHBoxLayout* layout_pop = new QHBoxLayout(widget_pop);
	widget_pop->setLayout(layout_pop);
	layout_pop->addWidget(btn_pop_stack,3);
	layout_pop->addWidget(btn_dequeue_queue,3);
	layout_pop->addWidget(btn_pop_dequeue,3);
	connect(btn_pop_stack, &textButton::clicked, this, [=]() {
		/*if (!view->stack.isEmpty()) {
			auto val = view->stack.top();
			logDisplay->addWidget(new StaqueViewLog(QString("[Stack] pop the top: %1").arg(val), logDisplay));
			view->stack.pop();
			update();
		}*/
		});
	connect(btn_dequeue_queue, &textButton::clicked, this, [=]() {
		/*if (!view->queue.isEmpty()) {
			auto val = view->queue.front();
			logDisplay->addWidget(new StaqueViewLog(QString("[Queue] dequeue the front: %1").arg(val), logDisplay));
			view->queue.dequeue();
			update();
		}*/
		});
	connect(btn_pop_dequeue, &textButton::clicked, this, [=]() {
		/*if (!view->queue.isEmpty() && !view->stack.isEmpty()) {
			auto val1 = view->stack.top();
			auto val2 = view->queue.front();
			logDisplay->addWidget(new StaqueViewLog(QString("[Stack] pop the top: %1").arg(val1), logDisplay));
			logDisplay->addWidget(new StaqueViewLog(QString("[Queue] dequeue the front: %1").arg(val2), logDisplay));
			view->stack.pop();
			view->queue.dequeue();
			update();
		}*/
		});

	defTextLayout->addWidget(textName);
	defTextLayout->addWidget(textDesc);
	defTextLayout->addWidget(widget_push); 
	defTextLayout->addWidget(widget_random);
	defTextLayout->addWidget(widget_pop);

	defInfoLayout->addWidget(defTextItems);
	upperLayout->addWidget(defInfoPage);
	defInfoPage->show();

	//--------------------------------

	infoLayout->addWidget(upper);
	infoLayout->addWidget(lower);
}

