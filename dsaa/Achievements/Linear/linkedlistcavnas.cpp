#include "linkedlistcavnas.h"
#include "slidepage.h"
#include "singleSelectGroup.h"
#include "horizontalValueAdjuster.h"
#include "textInputItem.h"
#include "textButton.h"
#include <QPainter>
#include <QList>
#include <QHBoxLayout>
#include <QTimer>

LinkedListCanvas::LinkedListCanvas(int radius, QString name, QString desc, QWidget* parent)
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
	
}

void LinkedListCanvas::drawLinkedList(QPainter* painter, const QList<int>& values, int width, int height){
	 painter->setPen(QColor(200, 200, 200));

	 const int nodeWidth = 60; // �ڵ���εĿ��
	 const int nodeHeight = 30; // �ڵ���εĸ߶�
	 const int arrowSize = 10; // ��ͷ��С
	 const int textSpace = 5; // �ı�����α�Ե�ľ���
	 const int maxNodesPerRow = 5; // ÿ�������ʾ�Ľڵ�����
	 const int row_spacing = 20; //�м��

	 // 600 - 5 * 60 = 300 / 6 = 50
	 // ����ڵ���
	 int nodeSpacing{};
	 if (values.length() <= 5) {
		 nodeSpacing = (width - values.length() * nodeWidth) / (values.length() + 1);
	 }
	 else {
		 nodeSpacing = (width - maxNodesPerRow * nodeWidth) / (maxNodesPerRow + 1);
	 }

	 int dir{ 1 };

	 // ���ƽڵ�ͼ�ͷ
	 int x = nodeSpacing;
	 int y = height / 2 - nodeHeight / 2;
	 int nodesInRow = 0; // ��ǰ���ѻ��ƵĽڵ�����
	 int now_count = 0;
	 int cur_row = 0;
	 for (int i = 0; i < values.length(); ++i) {
		 // ��ǰ�еĽڵ�������1
		 nodesInRow++;
		 now_count++;
		 // ���Ƽ�ͷ���������һ���ڵ㣩
		 if (dir == 1) {
			 // ���ƽڵ�
			 painter->drawRect(x, y, nodeWidth, nodeHeight);

			 // ���ƽڵ�ֵ
			 QString text = QString::number(values[i]);
			 painter->drawText(x + textSpace, y + nodeHeight / 2 + painter->fontMetrics().height() / 2, text);

			 if (now_count == values.length()) {
				 break;
			 }
			 if (now_count != 0 && now_count % 5 == 0) {
				 //����һ�����µļ�ͷ
				 painter->drawLine(x + nodeWidth / 2, y + nodeHeight, x + nodeWidth / 2, y + nodeHeight + row_spacing);
				 painter->drawLine(x + nodeWidth / 2, y + nodeHeight + row_spacing, x + nodeWidth / 2 + 10, y + nodeHeight + row_spacing - 10);
				 painter->drawLine(x + nodeWidth / 2, y + nodeHeight + row_spacing, x + nodeWidth / 2 - 10, y + nodeHeight + row_spacing - 10);
			 }
			 else {
				 painter->drawLine(x + nodeWidth, y + nodeHeight / 2, x + nodeWidth + nodeSpacing, y + nodeHeight / 2);
				 painter->drawLine(x + nodeWidth + nodeSpacing, y + nodeHeight / 2, x + nodeWidth + nodeSpacing - 10, y + nodeHeight / 2 - arrowSize / 2);
				 painter->drawLine(x + nodeWidth + nodeSpacing, y + nodeHeight / 2, x + nodeWidth + nodeSpacing - 10, y + nodeHeight / 2 + arrowSize / 2);
			 }
			 // ��������
			 x += nodeWidth + nodeSpacing;
		 }
		 else {
			 //��������
			 painter->drawRect(x, y, nodeWidth, nodeHeight);

			 QString text = QString::number(values[i]);
			 painter->drawText(x + textSpace, y + nodeHeight / 2 + painter->fontMetrics().height() / 2, text);

			 if (now_count == values.length()) {
				 break;
			 }
			 if (now_count != 0 && now_count % 5 == 0) {
				 //����һ�����µļ�ͷ
				 painter->drawLine(x + nodeWidth / 2, y + nodeHeight, x + nodeWidth / 2, y + nodeHeight + row_spacing);
				 painter->drawLine(x + nodeWidth / 2, y + nodeHeight + row_spacing, x + nodeWidth / 2 + 10, y + nodeHeight + row_spacing - 10);
				 painter->drawLine(x + nodeWidth / 2, y + nodeHeight + row_spacing, x + nodeWidth / 2 - 10, y + nodeHeight + row_spacing - 10);
			 }
			 else {
				 painter->drawLine(x, y + nodeHeight / 2, x - nodeSpacing, y + nodeHeight / 2);
				 painter->drawLine(x - nodeSpacing, y + nodeHeight / 2, x - nodeSpacing + 10, y + nodeHeight / 2 - arrowSize / 2);
				 painter->drawLine(x - nodeSpacing, y + nodeHeight / 2, x - nodeSpacing + 10, y + nodeHeight / 2 + arrowSize / 2);
			 }
			 // ��������
			 x -= nodeWidth + nodeSpacing;
		 }

		 // �����ǰ�еĽڵ������Ѿ��ﵽ���ֵ������x���겢����һ�п�ʼ����
		 if (nodesInRow == maxNodesPerRow) {
			 cur_row++;
			 nodesInRow = 0;
			 dir = 1 - dir;
			 if (dir == 1) {
				 // ��������
				 x += nodeWidth + nodeSpacing;
			 }
			 else {
				 // ��������
				 x -= nodeWidth + nodeSpacing;
			 }
			 y = height / 2 - nodeHeight / 2 + cur_row * (nodeHeight + row_spacing);
		 }
	 }
}
