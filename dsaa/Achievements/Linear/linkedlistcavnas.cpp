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
#include <QPainter>
#include <QList>
#include <QHBoxLayout>
#include <QTimer>
#include <QLabel>
#include <QPaintEvent>
#include <QLineEdit>
#include <QRegularExpressionValidator>

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
	SpinBox* spin = new SpinBox("input: ", settings);


	// Adjust node width.

	// Adjust node height.

	// Adjust arrow size.

	// Adjust text space.

	// Adjust row spacing.

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
	settings->AddContent(whiteSpace);
	settings->AddContent(spin);
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

