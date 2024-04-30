#ifndef BSEARCH_PAGE
#define BSEARCH_PAGE

#include "Components/pagewidget.h"
#include <QGridLayout>

class QLabel;
class QHBoxLayout;
class LineEditWidget;
class bigIconButton;
class QLineEdit;
class BSearchTreeCanvas;
class BSearchTreePage : public PageWidget {

    Q_OBJECT

public:
    BSearchTreePage(QWidget* parent = 0);
    ~BSearchTreePage();

private:
    // Push button icons
    QLabel* _iconButtonLabel = nullptr;
    QWidget* _textButtonWidget = nullptr;
    QHBoxLayout* _textButtonLayout = nullptr;
    QLabel* _textButtonIcon = nullptr;
    QLabel* _textButtonLabel = nullptr;

    // Canvas
    BSearchTreeCanvas* bstreeCanvas = nullptr;

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
