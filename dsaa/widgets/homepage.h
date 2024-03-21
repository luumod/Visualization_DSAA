#ifndef HOME_PAGE
#define HOME_PAGE

#include "conponents/pagewidget.h"

class QLabel;
class QHBoxLayout;
class LineEditWidget;
class bigIconButton;
class QGridLayout;
class HomePage : public PageWidget {

    Q_OBJECT

public:
    HomePage(QWidget* parent = 0);
    ~HomePage();

private:
    // Push button icons
    QLabel* _iconButtonLabel = nullptr;
    QWidget* _textButtonWidget = nullptr;
    QHBoxLayout* _textButtonLayout = nullptr;
    QLabel* _textButtonIcon = nullptr;
    QLabel* _textButtonLabel = nullptr;

    // UI elements
    QVBoxLayout* _titleLayout = nullptr;
    const QFont _titleFont = QFont("DengXian", 26, QFont::ExtraLight);
    QLabel* _titleLabel = nullptr;

    QWidget* _mainWidget = nullptr;

    // grid layout
    QGridLayout* _mainLayout = nullptr;


    // widgets
    bigIconButton* btn1 = nullptr;
    bigIconButton* btn2 = nullptr;
    bigIconButton* btn3 = nullptr;
    bigIconButton* btn4 = nullptr;

public:
    virtual PushButton* getPageIconButton(QWidget* context) override;
    virtual PushButton* getPageTextButton(QWidget* context) override;
};


#endif // !HOME_PAGE
