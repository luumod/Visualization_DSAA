#ifndef ABOUT_PAGE
#define ABOUT_PAGE

#include "conponents/pagewidget.h"

class QLabel;
class QHBoxLayout;
class LineEditWidget;
class AboutPage : public PageWidget {

    Q_OBJECT

public:
    AboutPage(QWidget* parent = 0);
    ~AboutPage();

private:
    // Push button icons
    QLabel* _iconButtonLabel = nullptr;
    QWidget* _textButtonWidget = nullptr;
    QHBoxLayout* _textButtonLayout = nullptr;
    QLabel* _textButtonIcon = nullptr;
    QLabel* _textButtonLabel = nullptr;

    // UI elements
    QVBoxLayout* _titleAreaLayout = nullptr;
    const QFont _titleFont = QFont("DengXian", 26, QFont::ExtraLight);
    QLabel* _titleLabel = nullptr;

    QWidget* _mainWidget = nullptr;
    QVBoxLayout* _mainLayout = nullptr;

    LineEditWidget* _authorLabel = nullptr;
    LineEditWidget* _versionLabel = nullptr;
    LineEditWidget* _dateLabel = nullptr;

    LineEditWidget* _skyTerDev = nullptr;
    LineEditWidget* _lightingDev = nullptr;
    LineEditWidget* _coreDev = nullptr;
    LineEditWidget* _uiDesigner = nullptr;

    LineEditWidget* _license = nullptr;
    LineEditWidget* _qtVersion = nullptr;
    LineEditWidget* _usedLibraries = nullptr;
    LineEditWidget* _githubLink = nullptr;

public:
    virtual PushButton* getPageIconButton(QWidget* context) override;
    virtual PushButton* getPageTextButton(QWidget* context) override;
};

#endif