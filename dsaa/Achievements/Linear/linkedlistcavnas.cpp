#include "linkedlistcavnas.h"
#include "slidepage.h"
#include "singleSelectGroup.h"
#include "spinbox.h"
#include "horizontalValueAdjuster.h"
#include "textInputItem.h"
#include "textButton.h"
#include "customScrollContainer.h"
#include "doubly_linked_list.h"
#include "linkedlistview.h"
#include "logger.h"
#include "common.h"
#include <QPainter>
#include <QList>
#include <QHBoxLayout>
#include <QTimer>
#include <QLabel>
#include <QPaintEvent>
#include <QLineEdit>
#include <QRegularExpressionValidator>
#include <QRandomGenerator>

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
		// Update all inborn attributes actually, not care if your whether modified it.
		view->updateSettings(
			spin_node_width->value(),
			spin_node_height->value(),
			spin_arrow_length->value(),
			spin_text_size->value(),
			spin_max_number->value(),
			spin_row_spacing->value());
	});
	connect(adjust_spin_group, &SpinBoxGroup::spinBoxReset, this, [=]() {
		view->resetSettings();
	});


	textInputItem* rename = new textInputItem("Name", settings);
	rename->setValue(canvasName);
	connect(rename, &textInputItem::textEdited, this, [=](QString text) {
		canvasName = text;
		emit nameChanged(text);
#if DEBUG
		Logger::debug(QString(" page rename: %1").arg(text));
#endif
		});

	textInputItem* redesc = new textInputItem("Detail", settings);
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

	settings->AddContent(btnStop);
	settings->AddContent(btnStart);
	settings->AddContent(whiteSpace2);
	settings->AddContent(structureSetting);
	settings->AddContent(whiteSpace);
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
	textInputItem* textName = new textInputItem(canvasName, defInfoPage);
	connect(this, &LinkedListCanvas::nameChanged, this, [=]() {textName->setValue(canvasName); });
	textName->setEnabled(false);
	// Canvas description.
	textInputItem* textDesc = new textInputItem("Detail", defInfoPage);
	textDesc->setValue(canvasDescription);
	connect(this, &LinkedListCanvas::descChanged, this, [=]() {textDesc->setValue(canvasDescription); });
	textDesc->setEnabled(false);


	// Implement two push methods and its input editor.
	textInputItem* input_push = new textInputItem("input", defInfoPage);
	textButton* btn_push_back = new textButton("Push back", defInfoPage);
	textButton* btn_push_front = new textButton("Push front", defInfoPage);
	QWidget* widget_push = new QWidget(defInfoPage);
	widget_push->setObjectName("DefTextItems");
	widget_push->setStyleSheet("QWidget#DefTextItems{border:1px solid #cfcfcf;border-radius:5px;}");
	QHBoxLayout* layout_push = new QHBoxLayout(widget_push);
	widget_push->setLayout(layout_push);
	layout_push->addWidget(input_push);
	layout_push->addWidget(btn_push_back);
	layout_push->addWidget(btn_push_front);
	layout_push->setStretch(0, 6);
	layout_push->setStretch(1, 2);
	layout_push->setStretch(2, 2);
	connect(btn_push_back, &textButton::clicked, this, [=]() {
		if (!input_push->value().isEmpty()) {
			view->listObj()->push_back(input_push->value().toInt());
			view->update();
		}
		});
	connect(btn_push_front, &textButton::clicked, this, [=]() {
		if (!input_push->value().isEmpty()) {
			view->listObj()->push_front(input_push->value().toInt());
			view->update();
		}
		});
	
	// Implement two pop methods.
	QWidget* pop_btn = new QWidget(defInfoPage);
	pop_btn->setObjectName("DefTextItems");
	pop_btn->setStyleSheet("QWidget#DefTextItems{border:1px solid #cfcfcf;border-radius:5px;}");
	QHBoxLayout* layout_del = new QHBoxLayout(pop_btn);
	textButton* btn_pop_front = new textButton("Pop front", defInfoPage);
	textButton* btn_pop_back = new textButton("Pop back", defInfoPage);
	textButton* btn_clear = new textButton("Clear", defInfoPage);
	layout_del->addWidget(btn_pop_front);
	layout_del->addWidget(btn_pop_back);
	layout_del->addWidget(btn_clear);
	layout_del->setStretch(0, 3);
	layout_del->setStretch(1, 3);
	layout_del->setStretch(2, 3);
	connect(btn_pop_front, &textButton::clicked, this, [=]() {
		view->listObj()->pop_front();
		view->update();
		});
	connect(btn_pop_back, &textButton::clicked, this, [=]() {
		view->listObj()->pop_back();
		view->update();
		});
	connect(btn_clear, &textButton::clicked, this, [=]() {
		view->listObj()->clear();
		view->update();
		});

	// Random generate one node or whole linked list.
	QWidget* random_gen = new QWidget(defInfoPage);
	random_gen->setObjectName("DefTextItems");
	random_gen->setStyleSheet("QWidget#DefTextItems{border:1px solid #cfcfcf;border-radius:5px;}");
	QHBoxLayout* layout_random_gen = new QHBoxLayout(random_gen);
	textButton* random_one_node = new textButton("Random gen", defInfoPage);
	textButton* random_whole_ls = new textButton("Random list", defInfoPage);
	layout_random_gen->addWidget(random_one_node);
	layout_random_gen->addWidget(random_whole_ls);
	layout_random_gen->setStretch(0, 5);
	layout_random_gen->setStretch(1, 5);
	connect(random_one_node, &textButton::clicked, this, [=]() {
		int random = QRandomGenerator::global()->bounded(0, 10000);
		view->listObj()->push_back(random);
		view->update();
		});
	connect(random_whole_ls, &textButton::clicked, this, [=]() {
		view->listObj()->clear();
		int size = QRandomGenerator::global()->bounded(1, 30);
		for (int i = 0; i < size; i++) {
			int random = QRandomGenerator::global()->bounded(0, 10000);
			view->listObj()->push_back(random);
		}
		view->update();
		});

	// Insert node
	textInputItem* input_insert = new textInputItem("pos", defInfoPage);
	input_insert->lineEditor()->setPlaceholderText("e.g. 0 10");
	QRegularExpressionValidator* validator_insert = new QRegularExpressionValidator(QRegularExpression("\\d+ \\d+"), input_insert);
	input_insert->lineEditor()->setValidator(validator_insert);
	textButton* btn_insert = new textButton("Insert", defInfoPage);
	QWidget* widget_insert = new QWidget(defInfoPage);
	widget_insert->setObjectName("DefTextItems");
	widget_insert->setStyleSheet("QWidget#DefTextItems{border:1px solid #cfcfcf;border-radius:5px;}");
	QHBoxLayout* layout_insert = new QHBoxLayout(widget_insert);
	layout_insert->addWidget(input_insert);
	layout_insert->addWidget(btn_insert);
	layout_insert->setStretch(0, 7);
	layout_insert->setStretch(1, 3);
	connect(btn_insert, &textButton::clicked, this, [=]() {
		QString s_input =input_insert->value();
		auto s_list = s_input.split(" ");
		if (s_list.size() == 2) {
			view->listObj()->insert(s_list[0].toInt(),s_list[1].toInt());
			view->update();
		}
	});

	// Delete node
	textInputItem* input_delete = new textInputItem("pos", defInfoPage);
	input_delete->lineEditor()->setPlaceholderText("e.g. 0");
	textButton* btn_delete = new textButton("delete", defInfoPage);
	QWidget* widget_delete = new QWidget(defInfoPage);
	widget_delete->setObjectName("DefTextItems");
	widget_delete->setStyleSheet("QWidget#DefTextItems{border:1px solid #cfcfcf;border-radius:5px;}");
	QHBoxLayout* layout_delete = new QHBoxLayout(widget_delete);
	layout_delete->addWidget(input_delete);
	layout_delete->addWidget(btn_delete);
	layout_delete->setStretch(0, 7);
	layout_delete->setStretch(1, 3);
	connect(btn_delete, &textButton::clicked, this, [=]() {
		if (!input_delete->value().isEmpty()) {
			view->listObj()->remove(input_delete->value().toInt());
			view->update();
		}
		});

	defTextLayout->addWidget(textName);
	defTextLayout->addWidget(textDesc);
	defTextLayout->addWidget(widget_push);
	defTextLayout->addWidget(pop_btn);
	defTextLayout->addWidget(random_gen);
	defTextLayout->addWidget(widget_insert);
	defTextLayout->addWidget(widget_delete);

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

