#include "graphpage.h"
#include "bigIconButton.h"
#include "pushbutton.h"
#include "logger.h"
#include "common.h"
#include "fontawesomeicons.h"
#include "MainCanvas.h"
#include "SortFactory.h"
#include "graphcanvas.h"
#include "common.h"
#include "Components/customIcon.h"
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

GraphPage::GraphPage(QWidget* parent) :
	PageWidget(parent)
{
#if DEBUG
	Logger::debug("------- Begin initialized GraphPage -------");
#endif // DEBUG
	_contentWidget->setMouseTracking(true);

	//-------------------------------------
	this->setObjectName("ylh_1");
	MyCanvas* graphCanvas = new MyCanvas(20,
		"rename->value()",
		"re-describe->value()",
		true ? MyCanvas::AL : MyCanvas::AML,
		true ? MyCanvas::DG : MyCanvas::UDG, this->parentWidget());
	//-------------------------------------


	// Create the main layout for this window.
	_windowAreaLayout = new QVBoxLayout(_contentWidget);
	_contentWidget->setLayout(_windowAreaLayout); // Set for the main layout.

	// Main title area layout.
	_titleAreaWidget = new QWidget(_contentWidget);
	_titleAreaLayout = new QVBoxLayout(_titleAreaWidget);
	_titleAreaLayout->setContentsMargins(18, 36, 22, 22);
	_titleAreaLayout->setSpacing(1);
	_titleAreaLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	_titleAreaWidget->setLayout(_titleAreaLayout);
	_titleAreaWidget->show();

	// Construct title layout
	_titleOneWidget = new QWidget(_contentWidget);
	_titleOneLayout = new QHBoxLayout(_titleOneWidget);
	_titleOneLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	_titleOneWidget->setLayout(_titleOneLayout);
	_titleOneWidget->show();

	// Construct the first row of title area.
	_titleLabel = new QLabel("Graph", _contentWidget);
	_titleLabel->setFont(_titleFont);
	SlidePage* page = graphCanvas->settingPage();
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

	// Construct the second row of the title area.
	QFont descFont = QFont("Corbel Light", 12);
	QFontMetrics descFm(descFont);
	_pageDesc = new QLineEdit(_contentWidget);
	_pageDesc->setFont(descFont);
	_pageDesc->setText("Visualization of graph algorithm");
	_pageDesc->setMaxLength(128);
	_pageDesc->setReadOnly(true);
	_pageDesc->setMinimumHeight(descFm.lineSpacing());
	_pageDesc->setStyleSheet("background-color:#00000000;border-style:none;border-width:0px;");

	_titleAreaLayout->addWidget(_titleOneWidget);
	_titleAreaLayout->addWidget(_pageDesc);
	_titleOneWidget->show();
	_pageDesc->show();

	// Add to main window.
	_windowAreaLayout->addWidget(_titleAreaWidget);

	// Construct main layout
	_mainOperateWidget = new QWidget(_contentWidget);
	_mainOperateWidget->setObjectName("homePageMainWidget");
	_mainOperateWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	_mainOperateWidget->setStyleSheet("QWidget#mainWidget { background-color: #ff0000; border-radius: 8px; }");
	_mainOperateLayout = new QHBoxLayout(_mainOperateWidget);
	_mainOperateLayout->setAlignment(Qt::AlignTop);
	_mainOperateLayout->setContentsMargins(8, 8, 8, 8);
	_mainOperateLayout->setSpacing(20);
	_mainOperateWidget->setLayout(_mainOperateLayout);
	_mainOperateWidget->show();
	_mainOperateLayout->addWidget(graphCanvas);
	graphCanvas->show();

	// Add to main window.
	_windowAreaLayout->addWidget(_mainOperateWidget);


	update();

#if DEBUG
	Logger::debug("------- End initialized GraphPage -------");
#endif // DEBUG
}

GraphPage::~GraphPage() {}

PushButton* GraphPage::getPageIconButton(QWidget* context) {
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
	_iconButtonLabel->setText(FontAwesomeIcons::Instance()->getIconChar(FontAwesomeIcons::IconIdentity::icon_map_marker));
	_iconButtonLabel->setAlignment(Qt::AlignLeft);
	_iconButton->setChildWidget(_iconButtonLabel);

	// Return newly generated icon
	return _iconButton;
}

PushButton* GraphPage::getPageTextButton(QWidget* context) {
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
	_textButtonIcon->setText(FontAwesomeIcons::Instance()->getIconChar(FontAwesomeIcons::IconIdentity::icon_map_marker));
	_textButtonIcon->setAlignment(Qt::AlignLeft);

	_textButtonLabel = new QLabel(_textButtonWidget);
	_textButtonLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	_textButtonLabel->setText("Graph");
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
