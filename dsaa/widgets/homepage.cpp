#include "homepage.h"
#include "bigIconButton.h"
#include "pushbutton.h"
#include "common.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

HomePage::HomePage(QWidget* parent) :
	PageWidget(parent)
{
	_contentWidget->setMouseTracking(true);

	// Construct title layout
	_titleAreaLayout = new QVBoxLayout(_contentWidget);
	_titleAreaLayout->setContentsMargins(28, 46, 22, 22);
	_titleAreaLayout->setSpacing(1);
	_titleAreaLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	_contentWidget->setLayout(_titleAreaLayout);

	// Construct title
	_titleLabel = new QLabel("Home", _contentWidget);
	_titleLabel->setFont(_titleFont);
	
	// Construct page description.
	QFont descFont = QFont("Corbel Light", 12);
	QFontMetrics descFm(descFont);
	_pageDesc = new QLineEdit(_contentWidget);
	_pageDesc->setFont(descFont);
	_pageDesc->setText("Select an operation.");
	_pageDesc->setMaxLength(128);
	_pageDesc->setReadOnly(true);
	_pageDesc->setMinimumHeight(descFm.lineSpacing());
	_pageDesc->setStyleSheet("background-color:#00000000;border-style:none;border-width:0px;");

	_titleAreaLayout->addWidget(_titleLabel);
	_titleAreaLayout->addWidget(_pageDesc); 
	_titleLabel->show();
	_pageDesc->show();

	// Construct main layout
	_mainWidget = new QWidget(_contentWidget);
	_mainWidget->setObjectName("homePageMainWidget");
	_mainWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	_mainWidget->setStyleSheet("QWidget#mainWidget { background-color: #efefef; border-radius: 8px; }");
	_mainLayout = new QGridLayout(_mainWidget);
	_mainLayout->setAlignment(Qt::AlignTop);
	_mainLayout->setContentsMargins(8, 8, 8, 8);
	_mainLayout->setSpacing(20);
	_mainWidget->setLayout(_mainLayout);
	_titleAreaLayout->addWidget(_mainWidget);
	_mainWidget->show();
}

HomePage::~HomePage() {}

PushButton* HomePage::getPageIconButton(QWidget* context) {
	// Check for existed button
	if (_iconButton != nullptr) {
		return _iconButton;
	}

	// Generate new icon button
	_iconButton = new PushButton(nullptr, context);
	_iconButton->setMargin(20, 18, 16, 18);
	_iconButtonLabel = new QLabel(_iconButton);
	_iconButtonLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	QFont iconButtonFont("Font Awesome 6 Free Regular", 12);
	iconButtonFont.setStyleStrategy(QFont::PreferAntialias);
	_iconButtonLabel->setFont(iconButtonFont);
	_iconButtonLabel->setText("\uf059");
	_iconButtonLabel->setAlignment(Qt::AlignLeft);
	_iconButton->setChildWidget(_iconButtonLabel);

	// Return newly generated icon
	return _iconButton;
}

PushButton* HomePage::getPageTextButton(QWidget* context) {
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
	QFont textButtonFont("Font Awesome 6 Free Regular", 12);
	textButtonFont.setStyleStrategy(QFont::PreferQuality);
	_textButtonIcon->setFont(textButtonFont);
	_textButtonIcon->setText("\uf059");    // set icon to "pen" icon
	_textButtonIcon->setAlignment(Qt::AlignLeft);

	_textButtonLabel = new QLabel(_textButtonWidget);
	_textButtonLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	_textButtonLabel->setText("Home");
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
