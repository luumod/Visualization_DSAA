#include "greedcanvas.h"
#include "greedview.h"
#include "slidepage.h"
#include "singleSelectGroup.h"
#include "spinbox.h"
#include "horizontalValueAdjuster.h"
#include "textInputItem.h"
#include "textButton.h"
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

GreedCanvas::GreedCanvas(int radius, QString name, QString desc, QWidget* parent)
	:QWidget(parent),
	canvasName(name),
	canvasDescription(desc)
{
	setAttribute(Qt::WA_StyledBackground, true);

	mainLayout = new QHBoxLayout(this);
	mainLayout->setContentsMargins(0, 0, 0, 0);
	this->setLayout(mainLayout);

	//QScrollArea* scrollArea = new QScrollArea(this);
	//scrollArea->setWidgetResizable(true);

	view = new GreedyChangeView(this);
	view->setStyleSheet("background-color: #FFFFFF;border:1px solid #cfcfcf;border-radius:10px;");
	

	//scrollArea->setWidget(view);
	mainLayout->addWidget(view);
	
	this->setFocusPolicy(Qt::ClickFocus);

	CreateSettings(radius);
}

GreedCanvas::~GreedCanvas()
{
}
void GreedCanvas::CreateSettings(int radius)
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
	//SpinBoxGroup* adjust_spin_group = new SpinBoxGroup("Adjust panel", settings);
	//SpinBox* spin_node_width = new SpinBox("Node Width",40,100,60, settings);
	//SpinBox* spin_node_height = new SpinBox("Node Height",30,100,30, settings);
	//SpinBox* spin_arrow_length = new SpinBox("Arrow Length",1,100,10, settings);
	//SpinBox* spin_text_size = new SpinBox("Text Size",1,20,5, settings);
	//SpinBox* spin_max_number = new SpinBox("Max number",1,10,5, settings);
	//SpinBox* spin_row_spacing = new SpinBox("Row spacing",10,100,20, settings);
	//adjust_spin_group->AddItem(spin_node_width);
	//adjust_spin_group->AddItem(spin_node_height);
	//adjust_spin_group->AddItem(spin_arrow_length);
	//adjust_spin_group->AddItem(spin_text_size);
	//adjust_spin_group->AddItem(spin_max_number);
	//adjust_spin_group->AddItem(spin_row_spacing);
	//connect(adjust_spin_group, &SpinBoxGroup::spinBoxItemChange, this, [=](int unused) {
	//	// Update all inborn attributes actually, not care if your whether modified it.
	//	/*view->updateSettings(
	//		spin_node_width->value(),
	//		spin_node_height->value(),
	//		spin_arrow_length->value(),
	//		spin_text_size->value(),
	//		spin_max_number->value(),
	//		spin_row_spacing->value());*/
	//});
	//connect(adjust_spin_group, &SpinBoxGroup::spinBoxReset, this, [=]() {
	//	//view->resetSettings();
	//});


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
	//connect(this, &GreedCanvas::brushColorChanged, view, &GreedyChangeView::freshNodeBrushColor);
	connect(btn_node_brush, &textButton::clicked, this, [=]() {
		QColor color = QColorDialog::getColor(Qt::white, this, "Choose a color for the node to brush.");
		if (color.isValid()) {
			btn_node_brush->setDefaultColor(color);
			emit brushColorChanged(color);
		}
	});
	//connect(this, &GreedCanvas::lineColorChanged, view, &LinkedListView::freshNodeLineColor);
	connect(btn_arrow_color, &textButton::clicked, this, [=]() {
		QColor color = QColorDialog::getColor(Qt::white, this, "Choose a color for the connection line.");
		if (color.isValid()) {
			btn_arrow_color->setDefaultColor(color);
			emit lineColorChanged(color);
		}
		});
	//connect(this, &GreedCanvas::textColorChanged, view, &LinkedListView::freshNodeTextColor);
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

void GreedCanvas::Init()
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
	connect(this, &GreedCanvas::nameChanged, this, [=]() {textName->setValue(canvasName); });
	textName->setEnabled(false);
	// Canvas description.
	textInputItem* textDesc = new textInputItem("Detail", defInfoPage);
	textDesc->setValue(canvasDescription);
	connect(this, &GreedCanvas::descChanged, this, [=]() {textDesc->setValue(canvasDescription); });
	textDesc->setEnabled(false);

	connect(this, &GreedCanvas::startGreed, view, &GreedyChangeView::startChange);

	// show default
	textButton* btn_start = new textButton("Start change", defInfoPage);
	QWidget* widget_push = new QWidget(defInfoPage);
	widget_push->setObjectName("DefTextItems");
	widget_push->setStyleSheet("QWidget#DefTextItems{border:1px solid #cfcfcf;border-radius:5px;}");
	QHBoxLayout* layout_push = new QHBoxLayout(widget_push);
	widget_push->setLayout(layout_push);
	layout_push->addWidget(btn_start);
	connect(btn_start, &textButton::clicked, this, [=]() {
		emit startGreed();
		});

	// input
	textInputItem* input_data = new textInputItem("Values", defInfoPage);
	input_data->lineEditor()->setPlaceholderText("50 25 10 5 2");
	textButton* btn_update_values = new textButton("update", defInfoPage);
	QWidget* widget_values = new QWidget(defInfoPage);
	widget_values->setObjectName("DefTextItems");
	widget_values->setStyleSheet("QWidget#DefTextItems{border:1px solid #cfcfcf;border-radius:5px;}");
	QHBoxLayout* layout_values = new QHBoxLayout(widget_values);
	widget_values->setLayout(layout_values);
	layout_values->addWidget(input_data);
	layout_values->addWidget(btn_update_values);
	layout_values->setStretch(0, 7);
	layout_values->setStretch(1, 3);
	connect(btn_update_values, &textButton::clicked, this, [=]() {
		if (!input_data->value().isEmpty()) {
			QStringList vec = input_data->value().split(' ');
			QVector<int> intVector;
			if (vec.isEmpty()) {
				intVector << 50 << 25 << 10 << 5 << 2;
			}
			else {
				for (const QString& str : vec) {
					intVector.append(str.toInt());
				}
				intVector.removeAll(0);
				std::sort(intVector.begin(), intVector.end(), std::greater<int>());
			}
			qInfo() << intVector;
			view->setValues(intVector);
		}
		});


	// Amount
	textInputItem* input_amount = new textInputItem("Amount", defInfoPage);
	input_amount->lineEditor()->setPlaceholderText("99");
	textButton* btn_update_amount = new textButton("update", defInfoPage);
	QWidget* widget_amount = new QWidget(defInfoPage);
	widget_amount->setObjectName("DefTextItems");
	widget_amount->setStyleSheet("QWidget#DefTextItems{border:1px solid #cfcfcf;border-radius:5px;}");
	QHBoxLayout* layout_amount = new QHBoxLayout(widget_amount);
	widget_amount->setLayout(layout_amount);
	layout_amount->addWidget(input_amount);
	layout_amount->addWidget(btn_update_amount);
	layout_amount->setStretch(0, 7);
	layout_amount->setStretch(1, 3);
	connect(btn_update_amount, &textButton::clicked, this, [=]() {
		if (!input_amount->value().isEmpty()) {
			int targetAmount = input_amount->value().split(' ')[0].toInt();
			view->setTargetAmout(targetAmount);
		}
		});



	defTextLayout->addWidget(textName);
	defTextLayout->addWidget(textDesc);
	defTextLayout->addWidget(widget_push);
	defTextLayout->addWidget(widget_values);
	defTextLayout->addWidget(widget_amount);

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

