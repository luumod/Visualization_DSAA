#include "greedcanvas.h"
#include "greedview.h"
#include "slidepage.h"
#include "greedyviewlog.h"
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
#include <QTextEdit>

GreedCanvas::GreedCanvas(int radius, QString name, QString desc, QWidget* parent)
	:QWidget(parent),
	canvasName(name),
	canvasDescription(desc)
{
	setAttribute(Qt::WA_StyledBackground, true);

	mainLayout = new QHBoxLayout(this);
	mainLayout->setContentsMargins(0, 0, 0, 0);
	this->setLayout(mainLayout);

	view = new GreedyChangeView(this);
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

	QString nextStepGreedyChangeCode =
		"void GreedyChangeView::nextStep()\n"
		"{\n"
		"    if (currentAmount == targetAmount)\n"
		"    {\n"
		"        timer->stop();\n"
		"        return;\n"
		"    }\n"
		"    std::sort(coinValues.begin(), coinValues.end(), std::greater<>());\n"
		"    for (int i = 0; i < coinValues.size(); ++i)\n"
		"    {\n"
		"        if (currentAmount + coinValues[i] <= targetAmount)\n"
		"        {\n"
		"            currentCoins.push_back(coinValues[i]);\n"
		"            currentAmount += coinValues[i];\n"
		"            break;\n"
		"        }\n"
		"    }\n"
		"    update();\n"
		"}\n";

	textEdit->setText(nextStepGreedyChangeCode);

	layout_text_view->addWidget(textEdit);

	this->setFocusPolicy(Qt::ClickFocus);
	connect(this, &GreedCanvas::typeChanged, this, &GreedCanvas::on_changed_algorithm);
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
	selectionItem* greedy_1 = new selectionItem("Coin change", "Adjacent list structure", settings);
	selectionItem* greedy_2 = new selectionItem("Task scheduling", "Adjacent multiple list", settings);
	structureSetting->AddItem(greedy_1);
	structureSetting->AddItem(greedy_2);
	connect(structureSetting, &singleSelectGroup::selectedItemChange, this, [=](int index) {
		switch (index)
		{
		case 0:
			emit typeChanged(index);
			break;
		case 1:
			emit typeChanged(index);
			break;
		}
		settings->slideOut();
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

	settings->AddContent(whiteSpace2);
	settings->AddContent(structureSetting);
	settings->AddContent(spacingLine);
	settings->AddContent(whiteSpace);
	settings->AddContent(redesc);
	settings->AddContent(rename);
	settings->show();

	QTimer* delay = new QTimer(this);
	connect(delay, &QTimer::timeout, this, [=]() {Init(); });
	delay->setSingleShot(true);
	delay->start(10);
}

void GreedCanvas::on_changed_algorithm(int row) {
	view->type = row;
	if (row == 0) {
		// coin
		widget_1_values->show();
		widget_1_amount->show();

		widget_2_add->hide();
		widget_2_control->hide();

		QString nextStepGreedyChangeCode =
			"void GreedyChangeView::nextStep()\n"
			"{\n"
			"    if (currentAmount == targetAmount)\n"
			"    {\n"
			"        timer->stop();\n"
			"        return;\n"
			"    }\n"
			"    std::sort(coinValues.begin(), coinValues.end(), std::greater<>());\n"
			"    for (int i = 0; i < coinValues.size(); ++i)\n"
			"    {\n"
			"        if (currentAmount + coinValues[i] <= targetAmount)\n"
			"        {\n"
			"            currentCoins.push_back(coinValues[i]);\n"
			"            currentAmount += coinValues[i];\n"
			"            break;\n"
			"        }\n"
			"    }\n"
			"    update();\n"
			"}\n";

		textEdit->setText(nextStepGreedyChangeCode);

	}
	else if (row == 1) {
		// schedule
		widget_2_add->show();
		widget_2_control->show();

		widget_1_values->hide();
		widget_1_amount->hide();
		QString schedulingGreedyCode =
			"void schedule(){\n"
			" int n;\n"
			" cin >> n; \n"
			" vector<Contest> cons(n); \n"
			" for (int i = 0; i < n; ++i)\n"
			"     cin >> cons[i].start >> cons[i].end;\n"
			" sort(cons.begin(), cons.end()); \n"
			" int ans = 0, end = 0, next = 0; \n"
			" while (next < n) {\n"
			"     ++ans;\n"
			"     end = cons[next].end;\n"
			"     while (next < n && cons[next].start < end) ++next;\n"
			" }\n"
			" cout << ans << endl;\n"
			"}\n";
		textEdit->setText(schedulingGreedyCode);
	}	
	view->showDefault();
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
	defTextLayout = new QVBoxLayout(defTextItems);
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
	textButton* btn_start = new textButton("Start greedy", defInfoPage);
	QWidget* widget_push = new QWidget(defInfoPage);
	widget_push->setObjectName("DefTextItems");
	widget_push->setStyleSheet("QWidget#DefTextItems{border:1px solid #cfcfcf;border-radius:5px;}");
	QHBoxLayout* layout_push = new QHBoxLayout(widget_push);
	widget_push->setLayout(layout_push);
	layout_push->addWidget(btn_start);
	connect(btn_start, &textButton::clicked, this, [=]() {
		emit startGreed();
		});


	// 1
	{
		// input
		textInputItem* input_data = new textInputItem("Values", defInfoPage);
		input_data->lineEditor()->setPlaceholderText("50 25 10 5 2");
		textButton* btn_update_values = new textButton("update", defInfoPage);
		widget_1_values = new QWidget(defInfoPage);
		widget_1_values->setObjectName("DefTextItems");
		widget_1_values->setStyleSheet("QWidget#DefTextItems{border:1px solid #cfcfcf;border-radius:5px;}");
		QHBoxLayout* layout_values = new QHBoxLayout(widget_1_values);
		widget_1_values->setLayout(layout_values);
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
		widget_1_amount = new QWidget(defInfoPage);
		widget_1_amount->setObjectName("DefTextItems");
		widget_1_amount->setStyleSheet("QWidget#DefTextItems{border:1px solid #cfcfcf;border-radius:5px;}");
		QHBoxLayout* layout_amount = new QHBoxLayout(widget_1_amount);
		widget_1_amount->setLayout(layout_amount);
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
	}

	// 2
	{
		// input
		textInputItem* input_data = new textInputItem("s & e:", defInfoPage);
		textButton* btn_add = new textButton("Add", defInfoPage);
		widget_2_add = new QWidget(defInfoPage);
		widget_2_add->setObjectName("DefTextItems");
		widget_2_add->setStyleSheet("QWidget#DefTextItems{border:1px solid #cfcfcf;border-radius:5px;}");
		QHBoxLayout* layout_add = new QHBoxLayout(widget_2_add);
		widget_2_add->setLayout(layout_add);
		widget_2_add->hide();
		layout_add->addWidget(input_data);
		layout_add->addWidget(btn_add);
		layout_add->setStretch(0, 7);
		layout_add->setStretch(1, 3);
		connect(btn_add, &textButton::clicked, this, [=]() {
			if (!input_data->value().isEmpty()) {
				QStringList vec = input_data->value().split(' ');
				GreedyChangeView::Task task;
				if (vec.size() != 2) {
					task = GreedyChangeView::Task{1,2};
				}
				else {
					task = GreedyChangeView::Task{ vec[0].toInt(),vec[1].toInt() };
				}
				view->addTask(task);
			}
			});


		// input
		textButton* btn_pop_last = new textButton("remove last", defInfoPage);
		textButton* btn_clear = new textButton("Clear", defInfoPage);
		widget_2_control = new QWidget(defInfoPage);
		widget_2_control->setObjectName("DefTextItems");
		widget_2_control->setStyleSheet("QWidget#DefTextItems{border:1px solid #cfcfcf;border-radius:5px;}");
		QHBoxLayout* layout_control = new QHBoxLayout(widget_2_control);
		widget_2_control->setLayout(layout_control);
		widget_2_control->hide();
		layout_control->addWidget(btn_pop_last, 5);
		layout_control->addWidget(btn_clear, 5);
		connect(btn_pop_last, &textButton::clicked, this, [=]() {
			view->pop_back();
			});
		connect(btn_clear, &textButton::clicked, this, [=]() {
			view->setClear();
			});
	}




	defTextLayout->addWidget(textName);
	defTextLayout->addWidget(textDesc);
	defTextLayout->addWidget(widget_push);
	defTextLayout->addWidget(widget_1_values);
	defTextLayout->addWidget(widget_1_amount);
	defTextLayout->addWidget(widget_2_add);
	defTextLayout->addWidget(widget_2_control);

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

	connect(view, &GreedyChangeView::logAdded, this, [=](GreedyViewLog* log) {logDisplay->addWidget(log); });
}