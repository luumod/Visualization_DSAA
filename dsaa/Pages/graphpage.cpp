#include "graphpage.h"
#include "bigIconButton.h"
#include "pushbutton.h"
#include "logger.h"
#include "common.h"
#include "fontawesomeicons.h"
#include "MainCanvas.h"
#include "SortFactory.h"
#include "graphcanvas.h"
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

GraphPage::GraphPage(QWidget* parent) :
	PageWidget(parent)
{
#if DEBUG
	Logger::debug("------- Begin initialized GraphPage -------");
#endif // DEBUG
	_contentWidget->setMouseTracking(true);

	// Create the main layout for this window.
	_windowAreaLayout = new QVBoxLayout(_contentWidget);
	_contentWidget->setLayout(_windowAreaLayout); // Set for the main layout.

	// Construct title layout
	_titleAreaWidget = new QWidget(_contentWidget);
	_titleAreaLayout = new QVBoxLayout(_titleAreaWidget);
	_titleAreaLayout->setContentsMargins(28, 46, 22, 22);
	_titleAreaLayout->setSpacing(1);
	_titleAreaLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	_titleAreaWidget->setLayout(_titleAreaLayout);
	_titleAreaWidget->show();
	// Add to main window.
	_windowAreaLayout->addWidget(_titleAreaWidget);

	// Construct title
	_titleLabel = new QLabel("Sort", _contentWidget);
	_titleLabel->setFont(_titleFont);

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

	_titleAreaLayout->addWidget(_titleLabel);
	_titleAreaLayout->addWidget(_pageDesc);
	_titleLabel->show();
	_pageDesc->show();

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
	// Add to main window.
	_windowAreaLayout->addWidget(_mainOperateWidget);

	MyCanvas* graphCanvas = new MyCanvas(20,
		"rename->value()",
		"re-describe->value()",
		true ? MyCanvas::AL : MyCanvas::AML,
		true ? MyCanvas::DG : MyCanvas::UDG, _contentWidget);

	_mainOperateLayout->addWidget(graphCanvas);
	graphCanvas->show();

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
