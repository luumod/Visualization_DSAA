#include "aboutpage.h"
#include "logger.h"
#include "common.h"
#include "fontawesomeicons.h"
#include "lineeditwidget.h"
#include "pushbutton.h"
#include <QVBoxLayout>
#include <QLabel>

AboutPage::AboutPage(QWidget* parent) :
	PageWidget(parent) 
{
#if DEBUG
		Logger::debug("------- Begin initialized AboutPage -------");
#endif // DEBUG
	_contentWidget->setMouseTracking(true);

	// Create the main layout for this window.
	_windowAreaLayout = new QVBoxLayout(_contentWidget);
	_windowAreaLayout->setContentsMargins(10, 0, 10, 0);
	_windowAreaLayout->setAlignment(Qt::AlignTop);
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
	_titleLabel = new QLabel("ABOUT", _contentWidget);
	_titleLabel->setFont(_titleFont);
	_titleAreaLayout->addWidget(_titleLabel);
	_titleLabel->show();

	// Construct main layout
	_mainOperateWidget = new QWidget(_contentWidget);
	_mainOperateWidget->setObjectName("mainWidget");
	_mainOperateWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	_mainOperateWidget->setStyleSheet("QWidget#mainWidget { background-color: #efefef; border-radius: 8px; }");
	_mainOperateLayout = new QVBoxLayout(_mainOperateWidget);
	_mainOperateLayout->setAlignment(Qt::AlignTop);
	_mainOperateLayout->setContentsMargins(0, 8, 0, 8);
	_mainOperateLayout->setSpacing(8);
	_mainOperateWidget->setLayout(_mainOperateLayout);
	_mainOperateWidget->show();
	// Add to main window.
	_windowAreaLayout->addWidget(_mainOperateWidget);
	
	// Construct contents
	_authorLabel = new LineEditWidget(_contentWidget);
	_authorLabel->mainLayout()->insertWidget(0, new QLabel("Authored by"));
	_authorLabel->mainLayout()->insertSpacing(1, 8);
	_authorLabel->setBackgroundColor(QColor(0, 0, 0, 0));
	_authorLabel->setHoverColor(QColor(0, 0, 0, 10));
	_authorLabel->setPressedColor(QColor(0, 0, 0, 20));
	_authorLabel->setText(DSAA_AUTHOR);
	_authorLabel->setEnabled(false);
	_mainOperateLayout->addWidget(_authorLabel);
	_authorLabel->show();

	_versionLabel = new LineEditWidget(_contentWidget);
	_versionLabel->mainLayout()->insertWidget(0, new QLabel("Version"));
	_versionLabel->mainLayout()->insertSpacing(1, 8);
	_versionLabel->setBackgroundColor(QColor(0, 0, 0, 0));
	_versionLabel->setHoverColor(QColor(0, 0, 0, 10));
	_versionLabel->setPressedColor(QColor(0, 0, 0, 20));
	_versionLabel->setText(DSAA_VERSION);
	_versionLabel->setEnabled(false);
	_mainOperateLayout->addWidget(_versionLabel);
	_versionLabel->show();

	_dateLabel = new LineEditWidget(_contentWidget);
	_dateLabel->mainLayout()->insertWidget(0, new QLabel("Last Update"));
	_dateLabel->mainLayout()->insertSpacing(1, 8);
	_dateLabel->setBackgroundColor(QColor(0, 0, 0, 0));
	_dateLabel->setHoverColor(QColor(0, 0, 0, 10));
	_dateLabel->setPressedColor(QColor(0, 0, 0, 20));
	_dateLabel->setText(DSAA_DATE);
	_dateLabel->setEnabled(false);
	_mainOperateLayout->addWidget(_dateLabel);
	_dateLabel->show();

	// insert line break
	QWidget* _line = new QWidget(_contentWidget);
	_line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	_line->setFixedHeight(1);
	_line->setStyleSheet("background-color: #c2c2c2;");
	_mainOperateLayout->addWidget(_line);
	_line->show();
	
	_lightingDev = new LineEditWidget(_contentWidget);
	_lightingDev->mainLayout()->insertWidget(0, new QLabel("Project developers"));
	_lightingDev->mainLayout()->insertSpacing(1, 8);
	_lightingDev->setBackgroundColor(QColor(0, 0, 0, 0));
	_lightingDev->setHoverColor(QColor(0, 0, 0, 10));
	_lightingDev->setPressedColor(QColor(0, 0, 0, 20));
	_lightingDev->setText(DSAA_DEVELOPERS);
	_lightingDev->setEnabled(false);
	_mainOperateLayout->addWidget(_lightingDev);
	_lightingDev->show();
	
	_coreDev = new LineEditWidget(_contentWidget);
	_coreDev->mainLayout()->insertWidget(0, new QLabel("Core developer"));
	_coreDev->mainLayout()->insertSpacing(1, 8);
	_coreDev->setBackgroundColor(QColor(0, 0, 0, 0));
	_coreDev->setHoverColor(QColor(0, 0, 0, 10));
	_coreDev->setPressedColor(QColor(0, 0, 0, 20));
	_coreDev->setText(DSAA_CORE_DEVELOP);
	_coreDev->setEnabled(false);
	_mainOperateLayout->addWidget(_coreDev);
	_coreDev->show();
	
	_uiDesigner = new LineEditWidget(_contentWidget);
	_uiDesigner->mainLayout()->insertWidget(0, new QLabel("UI designed by"));
	_uiDesigner->mainLayout()->insertSpacing(1, 8);
	_uiDesigner->setBackgroundColor(QColor(0, 0, 0, 0));
	_uiDesigner->setHoverColor(QColor(0, 0, 0, 10));
	_uiDesigner->setPressedColor(QColor(0, 0, 0, 20));
	_uiDesigner->setText(DSAA_UI_DEVELOP);
	_uiDesigner->setEnabled(false);
	_mainOperateLayout->addWidget(_uiDesigner);
	_uiDesigner->show();
	
	// add line break
	_line = new QWidget(_contentWidget);
	_line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	_line->setFixedHeight(1);
	_line->setStyleSheet("background-color: #c2c2c2;");
	_mainOperateLayout->addWidget(_line);
	_line->show();
	
	_license = new LineEditWidget(_contentWidget);
	_license->mainLayout()->insertWidget(0, new QLabel("License"));
	_license->mainLayout()->insertSpacing(1, 8);
	_license->setBackgroundColor(QColor(0, 0, 0, 0));
	_license->setHoverColor(QColor(0, 0, 0, 10));
	_license->setPressedColor(QColor(0, 0, 0, 20));
	_license->setText("GPLv3 (According to Qt6 Documents)");
	_license->setEnabled(false);
	_mainOperateLayout->addWidget(_license);
	_license->show();
	
	_qtVersion = new LineEditWidget(_contentWidget);
	_qtVersion->mainLayout()->insertWidget(0, new QLabel("Qt Version"));
	_qtVersion->mainLayout()->insertSpacing(1, 8);
	_qtVersion->setBackgroundColor(QColor(0, 0, 0, 0));
	_qtVersion->setHoverColor(QColor(0, 0, 0, 10));
	_qtVersion->setPressedColor(QColor(0, 0, 0, 20));
	_qtVersion->setText(DSAA_QT_VERSION);
	_qtVersion->setEnabled(false);
	_mainOperateLayout->addWidget(_qtVersion);
	_qtVersion->show();
	
	_usedLibraries = new LineEditWidget(_contentWidget);
	_usedLibraries->mainLayout()->insertWidget(0, new QLabel("Special thanks to"));
	_usedLibraries->mainLayout()->insertSpacing(1, 8);
	_usedLibraries->setBackgroundColor(QColor(0, 0, 0, 0));
	_usedLibraries->setHoverColor(QColor(0, 0, 0, 10));
	_usedLibraries->setPressedColor(QColor(0, 0, 0, 20));
	_usedLibraries->setText(DSAA_THANKS_TO);
	_usedLibraries->setEnabled(false);
	_mainOperateLayout->addWidget(_usedLibraries);
	_usedLibraries->show();
	
	_githubLink = new LineEditWidget(_contentWidget);
	_githubLink->mainLayout()->insertWidget(0, new QLabel("Open-source Repositories"));
	_githubLink->mainLayout()->insertSpacing(1, 8);
	_githubLink->setBackgroundColor(QColor(0, 0, 0, 0));
	_githubLink->setHoverColor(QColor(0, 0, 0, 10));
	_githubLink->setPressedColor(QColor(0, 0, 0, 20));
	_githubLink->setText(DSAA_GITHUB_REPO);
	_githubLink->setEnabled(false);
	_mainOperateLayout->addWidget(_githubLink);
	_githubLink->show();

#if DEBUG
	Logger::debug("------- End initialized AboutPage -------");
#endif // DEBUG
}

AboutPage::~AboutPage() {}

PushButton* AboutPage::getPageIconButton(QWidget* context) {
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

PushButton* AboutPage::getPageTextButton(QWidget* context) {
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
	//_textButtonIcon->setFont(textButtonFont);
	QFont font = FontAwesomeIcons::Instance()->getFont();
	_textButtonIcon->setFont(font);
	_textButtonIcon->setText(FontAwesomeIcons::Instance()->getIconChar(FontAwesomeIcons::IconIdentity::icon_tags));    // set icon to "pen" icon
	//qInfo() << FontAwesomeIcons::Instance()->getIconChar(FontAwesomeIcons::IconIdentity::icon_tags);
	_textButtonIcon->setAlignment(Qt::AlignLeft);

	_textButtonLabel = new QLabel(_textButtonWidget);
	_textButtonLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	_textButtonLabel->setText("About");
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
