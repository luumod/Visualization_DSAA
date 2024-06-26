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
#include <QTextEdit>

LinkedListCanvas::LinkedListCanvas(int radius, QString name, QString desc, QWidget* parent)
	:QWidget(parent),
	canvasName(name),
	canvasDescription(desc)
{
	setAttribute(Qt::WA_StyledBackground, true);

	mainLayout = new QHBoxLayout(this);
	mainLayout->setContentsMargins(0, 0, 0, 0);
	this->setLayout(mainLayout);

	view = new LinkedListView;
	view->setSceneRect(view->rect());
	view->setStyleSheet("background-color: #FFFFFF;border:1px solid #cfcfcf;border-radius:10px;");
	mainLayout->addWidget(view);

	QWidget* text_view = new QWidget(this);
	QHBoxLayout* layout_text_view = new QHBoxLayout(text_view);
	text_view->setLayout(layout_text_view);
	text_view->setStyleSheet("border:1px solid #cfcfcf; border-radius: 10px");
	text_view->setAutoFillBackground(true);
	QPalette palette;
	palette.setColor(QPalette::Window, Qt::white);
	text_view->setPalette(palette);
	mainLayout->addWidget(text_view);

	textEdit = new QTextEdit(text_view);
	textEdit->setReadOnly(true);
	textEdit->setStyleSheet("border:0px");

	layout_text_view->addWidget(textEdit);
	
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

	QWidget* spacingLine = new QWidget(this);
	spacingLine->setFixedHeight(1);
	spacingLine->setStyleSheet("background-color:#0a000000");

	QWidget* whiteSpace = new QWidget(settings);
	whiteSpace->setFixedHeight(30);

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
	connect(this, &LinkedListCanvas::brushColorChanged, view, &LinkedListView::freshNodeBrushColor);
	connect(btn_node_brush, &textButton::clicked, this, [=]() {
		QColor color = QColorDialog::getColor(Qt::white, this, "Choose a color for the node to brush.");
		if (color.isValid()) {
			btn_node_brush->setDefaultColor(color);
			emit brushColorChanged(color);
		}
	});
	connect(this, &LinkedListCanvas::lineColorChanged, view, &LinkedListView::freshNodeLineColor);
	connect(btn_arrow_color, &textButton::clicked, this, [=]() {
		QColor color = QColorDialog::getColor(Qt::white, this, "Choose a color for the connection line.");
		if (color.isValid()) {
			btn_arrow_color->setDefaultColor(color);
			emit lineColorChanged(color);
		}
		});
	connect(this, &LinkedListCanvas::textColorChanged, view, &LinkedListView::freshNodeTextColor);
	connect(btn_text_color, &textButton::clicked, this, [=]() {
		QColor color = QColorDialog::getColor(Qt::white, this, "Choose a color for text that located in the middle of node.");
		if (color.isValid()) {
			btn_text_color->setDefaultColor(color);
			emit textColorChanged(color);
		}
		});

	settings->AddContent(whiteSpace2);
	settings->AddContent(structureSetting);
	settings->AddContent(spacingLine);
	settings->AddContent(color_group_widget);
	//settings->AddContent(adjust_spin_group);
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
	textInputItem* textName = new textInputItem("Title", defInfoPage);
	textName->setValue(canvasName);
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
			view->push_back(input_push->value().toInt());

			QString pushBackCode =
				"void push_back(const int& elem) {\n"
				"    if (empty()) {\n"
				"        init_first_element(elem);\n"
				"        return;\n"
				"    }\n"
				"\n"
				"    m_tail->next = new Node{ elem, m_tail, nullptr };\n"
				"    m_tail = m_tail->next;\n"
				"    ++m_size;\n"
				"}\n";
			textEdit->setText(pushBackCode);
		}
		});
	connect(btn_push_front, &textButton::clicked, this, [=]() {
		if (!input_push->value().isEmpty()) {
			view->push_front(input_push->value().toInt());

			QString pushFrontCode =
				"void push_front(const int& elem) {\n"
				"    if (empty()) {\n"
				"        init_first_element(elem);\n"
				"        return;\n"
				"    }\n"
				"\n"
				"    m_head->prev = new Node{ elem, nullptr, m_head };\n"
				"    m_head = m_head->prev;\n"
				"    ++m_size;\n"
				"}\n";

			textEdit->setText(pushFrontCode);
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
		view->pop_front();

		QString popFrontCode =
			"void pop_front() {\n"
			"    if (size() <= 1) {\n"
			"        clean_up();\n"
			"        return;\n"
			"    }\n"
			"\n"
			"    m_head = m_head->next;\n"
			"    delete m_head->prev;\n"
			"    m_head->prev = nullptr;\n"
			"    --m_size;\n"
			"}\n";
		textEdit->setText(popFrontCode);

		});
	connect(btn_pop_back, &textButton::clicked, this, [=]() {
		view->pop_back();

		QString popBackCode =
			"void pop_back() {\n"
			"    if (size() <= 1) {\n"
			"        clean_up();\n"
			"        return;\n"
			"    }\n"
			"\n"
			"    m_tail = m_tail->prev;\n"
			"    delete m_tail->next;\n"
			"    m_tail->next = nullptr;\n"
			"    --m_size;\n"
			"}\n";

		textEdit->setText(popBackCode);

		});
	connect(btn_clear, &textButton::clicked, this, [=]() {
		view->clear();
	
		QString popBackLoopCode =
			"while (!list->empty()) {\n"
			"    list->pop_back();\n"
			"}\n";
		textEdit->setText(popBackLoopCode);

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
		view->push_back(random);

		QString pushBackCode =
			"void push_back(const int& elem) {\n"
			"    if (empty()) {\n"
			"        init_first_element(elem);\n"
			"        return;\n"
			"    }\n"
			"\n"
			"    m_tail->next = new Node{ elem, m_tail, nullptr };\n"
			"    m_tail = m_tail->next;\n"
			"    ++m_size;\n"
			"}\n";
		textEdit->setText(pushBackCode);

		});
	connect(random_whole_ls, &textButton::clicked, this, [=]() {
		view->clear();
		int size = QRandomGenerator::global()->bounded(5, 10);
		view->random_gen(size);

		QString pushBackCode =
			"void push_back(const int& elem) {\n"
			"    if (empty()) {\n"
			"        init_first_element(elem);\n"
			"        return;\n"
			"    }\n"
			"\n"
			"    m_tail->next = new Node{ elem, m_tail, nullptr };\n"
			"    m_tail = m_tail->next;\n"
			"    ++m_size;\n"
			"}\n";
		textEdit->setText(pushBackCode);
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

			QString insertAtIndexCode =
				"Node_ptr insert(int index, const int& elem) {\n"
				"    if (index == 0) {\n"
				"        push_front(elem);\n"
				"        return m_head;\n"
				"    }\n"
				"    if (index >= m_size) {\n"
				"        push_back(elem);\n"
				"        return m_tail;\n"
				"    }\n"
				"    Node_ptr ptr = find(index);\n"
				"    auto new_node = new Node{ elem, ptr->prev, ptr };\n"
				"    ptr->prev->next = new_node;\n"
				"    ptr->prev = new_node;\n"
				"    ++m_size;\n"
				"    return new_node;\n"
				"}\n";
			
			textEdit->setText(insertAtIndexCode);
			view->insert(s_list[0].toInt(),s_list[1].toInt());
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
			QString removeAtIndexCode =
				"Node_ptr remove(int index) {\n"
				"    if (index >= m_size) {\n"
				"        return nullptr;\n"
				"    }\n"
				"    if (index == 0) {\n"
				"        pop_front();\n"
				"        return m_head;\n"
				"    }\n"
				"    if (index + 1 == m_size) {\n"
				"        pop_back();\n"
				"        return nullptr;\n"
				"    }\n"
				"    Node_ptr ptr = find(index);\n"
				"    Node_ptr ret = ptr->next;\n"
				"    ptr->next->prev = ptr->prev;\n"
				"    ptr->prev->next = ptr->next;\n"
				"    delete ptr;\n"
				"    --m_size;\n"
				"    return ret;\n"
				"}\n";

			textEdit->setText(removeAtIndexCode);
			view->remove(input_delete->value().toInt());
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

