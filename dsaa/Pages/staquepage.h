#ifndef STAQUE_PAGE
#define STAQUE_PAGE

#include "Components/pagewidget.h"
#include <QGridLayout>

class QLabel;
class QHBoxLayout;
class LineEditWidget;
class bigIconButton;
class QLineEdit;
class StaqueCanvas;
class StaquePage : public PageWidget {

    Q_OBJECT

public:
    StaquePage(QWidget* parent = 0);
    ~StaquePage();

private:
    // Push button icons
    QLabel* _iconButtonLabel = nullptr;
    QWidget* _textButtonWidget = nullptr;
    QHBoxLayout* _textButtonLayout = nullptr;
    QLabel* _textButtonIcon = nullptr;
    QLabel* _textButtonLabel = nullptr;

    // Canvas
    StaqueCanvas* staqueCanvas = nullptr;

    // Entire area.
    QVBoxLayout* _windowAreaLayout = nullptr;
    const QFont _titleFont = QFont("DengXian", 26, QFont::ExtraLight);
    QLabel* _titleLabel = nullptr;
    QLineEdit* _pageDesc = nullptr;


    // first row
    QWidget* _titleOneWidget = nullptr;
    QHBoxLayout* _titleOneLayout = nullptr;

    // second row
    QWidget* _titleTwoWidget = nullptr;

    // main title area
    QWidget* _titleAreaWidget = nullptr;
    QVBoxLayout* _titleAreaLayout = nullptr;

    // operate area.
    QWidget* _mainOperateWidget = nullptr;
    QHBoxLayout* _mainOperateLayout = nullptr;


public:
    void autoResizeSettingsPage();

public:
    virtual PushButton* getPageIconButton(QWidget* context) override;
    virtual PushButton* getPageTextButton(QWidget* context) override;
};


#endif // !HOME_PAGE
