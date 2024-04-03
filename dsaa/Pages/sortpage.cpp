#include "sortpage.h"
#include "bigIconButton.h"
#include "pushbutton.h"
#include "logger.h"
#include "common.h"
#include "fontawesomeicons.h"
#include "SortCanvas.h"
#include "SortFactory.h"
#include "slidepage.h"
#include "customIcon.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QSpacerItem>
#include <QComboBox>
#include <QSpinBox>
#include <QListView>
#include <QThread>
#include <QPropertyAnimation>

SortPage::SortPage(QWidget* parent) :
	PageWidget(parent)
{
#if DEBUG
	Logger::debug("Begin initialized SortPage");
#endif // DEBUG
	_contentWidget->setMouseTracking(true);

	// Create the main layout for this window.
	_windowAreaLayout = new QVBoxLayout(_contentWidget);
	_contentWidget->setLayout(_windowAreaLayout); // Set for the main layout.

	// Construct operate widget.
	_mainOperateWidget = new QWidget(_contentWidget);
	_mainOperateWidget->setObjectName("homePageMainWidget");
	_mainOperateWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	_mainOperateLayout = new QHBoxLayout(_mainOperateWidget);
	_mainOperateLayout->setAlignment(Qt::AlignTop);
	_mainOperateLayout->setContentsMargins(8, 1, 8, 8);
	_mainOperateLayout->setSpacing(20);
	_mainOperateWidget->setLayout(_mainOperateLayout);

	QWidget* canvasWrap = new QWidget(_contentWidget);
	QVBoxLayout* canvasWrap_layout = new QVBoxLayout(canvasWrap);
	// Construct the visual window.
	sortCanvas = new SortCanvas(20, this->parentWidget());
	canvasWrap_layout->addWidget(sortCanvas);

	QWidget* panel = new QWidget(_contentWidget);
	QVBoxLayout* panel_layout = new QVBoxLayout(panel);

	auto h2 = new QHBoxLayout;
	auto combo = new QComboBox(panel);
	combo->setView(new QListView(panel));
	combo->addItems(SortFactory::getInstance()->getSortList());
	auto lab = new QLabel("Sort type", panel);
	h2->addWidget(lab);
	h2->addWidget(combo);

	auto h3 = new QHBoxLayout;
	auto spinCount = new QSpinBox(panel);
	spinCount->setRange(1, 100);
	spinCount->setValue(10);
	auto lab2 = new QLabel("Number of data:", panel);
	h3->addWidget(lab2);
	h3->addWidget(spinCount);

	auto h4 = new QHBoxLayout;
	auto spinInterval = new QSpinBox(panel);
	spinInterval->setValue(10);
	auto lab3 = new QLabel("Operate interval", panel);
	h4->addWidget(lab3);
	h4->addWidget(spinInterval);

	auto h1 = new QHBoxLayout;
	QPushButton* btnSort = new QPushButton("begin", panel);
	QPushButton* btnStop = new QPushButton("stop", panel);
	QSpacerItem* horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	// Clicked to start sort.
	connect(btnSort, &QPushButton::clicked, this, [=] {
		const int type = combo->currentIndex();
		if (type != sortCanvas->getSortType()) {
			SortObject* obj = SortFactory::getInstance()->createSortObject(type, parent);
			sortCanvas->setSortObject(type, obj);
		}
		sortCanvas->sort(spinCount->value(), spinInterval->value());
		});
	// Clicked to stop sort.
	connect(btnStop, &QPushButton::clicked, this, [=] {
		sortCanvas->stop();
		});

	// When sorting, user can't modified these thing.
	connect(sortCanvas, &SortCanvas::runFlagChanged,
		this, [=](bool running) {
			combo->setEnabled(!running);
			spinCount->setEnabled(!running);
			spinInterval->setEnabled(!running);
			btnSort->setEnabled(!running);
		});
	h1->addWidget(btnSort);
	h1->addSpacerItem(horizontalSpacer);
	h1->addWidget(btnStop);

	QSpacerItem* verticalSpacer = new QSpacerItem(20, 232, QSizePolicy::Minimum, QSizePolicy::Expanding);

	panel_layout->addLayout(h4);
	panel_layout->addLayout(h3);
	panel_layout->addLayout(h2);
	panel_layout->addSpacerItem(verticalSpacer);
	panel_layout->addLayout(h1);

	_mainOperateLayout->addWidget(canvasWrap, 4);
	_mainOperateLayout->addWidget(panel, 1);

	// -------------------------------------------------------

	// Main title area layout.
	_titleAreaWidget = new QWidget(_contentWidget);
	_titleAreaLayout = new QVBoxLayout(_titleAreaWidget);
	_titleAreaLayout->setContentsMargins(18, 36, 22, 22);
	_titleAreaLayout->setSpacing(1);
	_titleAreaLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	_titleAreaWidget->setLayout(_titleAreaLayout);

	// Construct title layout
	_titleOneWidget = new QWidget(_contentWidget);
	_titleOneLayout = new QHBoxLayout(_titleOneWidget);
	_titleOneLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	_titleOneWidget->setLayout(_titleOneLayout);

	// Construct the first row of title area.
	_titleLabel = new QLabel("Sort", _contentWidget);
	_titleLabel->setFont(_titleFont);
	SlidePage* page = sortCanvas->settingPage();
	customIcon* settingsIcon = new customIcon(ICON_FILE "settings.svg", "settings", 5, _contentWidget);
	settingsIcon->setMinimumHeight(_titleLabel->height() * 0.7);
	settingsIcon->setMaximumWidth(_titleLabel->width() * 0.7);
	connect(settingsIcon, &customIcon::clicked, this, [=]() {
		QPropertyAnimation* rotate = new QPropertyAnimation(settingsIcon, "rotationAngle", this);
		rotate->setDuration(750);
		rotate->setStartValue(0);
		rotate->setEndValue(90);
		rotate->setEasingCurve(QEasingCurve::InOutExpo);
		rotate->start();
		page->slideIn();
		});
	_titleOneLayout->addWidget(_titleLabel);
	_titleOneLayout->addWidget(settingsIcon);

	// Construct page description.
	QFont descFont = QFont("Corbel Light", 12);
	QFontMetrics descFm(descFont);
	_pageDesc = new QLineEdit(_contentWidget);
	_pageDesc->setFont(descFont);
	_pageDesc->setText("Visualization of sort algorithm");
	_pageDesc->setMaxLength(128);
	_pageDesc->setReadOnly(true);
	_pageDesc->setMinimumHeight(descFm.lineSpacing());
	_pageDesc->setStyleSheet("background-color:#00000000;border-style:none;border-width:0px;");

	_titleAreaLayout->addWidget(_titleOneWidget);
	_titleAreaLayout->addWidget(_pageDesc);

	//-----------------------------Separate------------------------------------

	// Add title area to main window.
	_windowAreaLayout->addWidget(_titleAreaWidget);

	// Add operate area to main window.
	_windowAreaLayout->addWidget(_mainOperateWidget);

	_titleOneWidget->show();
	_pageDesc->show();
	_titleOneWidget->show();
	_titleAreaWidget->show();
	_mainOperateWidget->show();
	canvasWrap->show();
	panel->show();

#if DEBUG
	Logger::debug("------- End initialized SortPage -------");
#endif // DEBUG
}

SortPage::~SortPage() {}

void SortPage::autoResizeSettingsPage() {
	sortCanvas->settingPage()->autoResize();
}

PushButton* SortPage::getPageIconButton(QWidget* context) {
	// Check for existed button
	if (_iconButton != nullptr) {
		return _iconButton;
	}

	// Generate new icon button
	_iconButton = new PushButton(nullptr, context);
	_iconButton->setMargin(20, 18, 16, 18);
	_iconButtonLabel = new QLabel(_iconButton);
	_iconButtonLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	QFont font = FontAwesomeIcons::Instance()->getFont();
	_iconButtonLabel->setFont(font);
	_iconButtonLabel->setText(FontAwesomeIcons::Instance()->getIconChar(FontAwesomeIcons::IconIdentity::icon_sort));
	_iconButtonLabel->setAlignment(Qt::AlignLeft);
	_iconButton->setChildWidget(_iconButtonLabel);

	// Return newly generated icon
	return _iconButton;
}

PushButton* SortPage::getPageTextButton(QWidget* context) {
	// Check for existed button
	if (_textButton != nullptr) {
		return _textButton;
	}

	// Generate new text button
	_textButton = new PushButton(nullptr, context);
	_textButton->setMargin(20, 18, 16, 18);
	_textButtonWidget = new QWidget(_textButton);
	_textButtonLayout = new QHBoxLayout(_textButtonWidget);
	_textButtonLayout->setContentsMargins(0, 0, 0, 0);
	_textButtonLayout->setSpacing(12);
	_textButtonWidget->setLayout(_textButtonLayout);

	// Generate text button contents
	_textButtonIcon = new QLabel(_textButtonWidget);
	QFont font = FontAwesomeIcons::Instance()->getFont();
	_textButtonIcon->setFont(font);
	_textButtonIcon->setText(FontAwesomeIcons::Instance()->getIconChar(FontAwesomeIcons::IconIdentity::icon_sort));
	_textButtonIcon->setAlignment(Qt::AlignLeft);

	_textButtonLabel = new QLabel(_textButtonWidget);
	_textButtonLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	_textButtonLabel->setText("Sort");
	_textButtonLabel->setAlignment(Qt::AlignLeft);

	// Add text button contents to layout
	_textButtonLayout->addWidget(_textButtonIcon);
	_textButtonLayout->addWidget(_textButtonLabel);
	_textButtonIcon->show();
	_textButtonLabel->show();

	// Set text button child widget
	_textButton->setChildWidget(_textButtonWidget);
	_textButtonWidget->show();

	// Return newly generated text button
	return _textButton;
}
