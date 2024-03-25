#ifndef HOME_PAGE
#define HOME_PAGE

#include "conponents/pagewidget.h"
#include <QGridLayout>

class QLabel;
class QHBoxLayout;
class LineEditWidget;
class bigIconButton;
class QLineEdit;
class HomePage : public PageWidget {

    Q_OBJECT

public:
    HomePage(QWidget* parent = 0);
    ~HomePage();

    // grid layout, so you should indicate the x and y.
    template <typename T>
    T* addConponent(T* widget, int x, int y) {
        widget->setParent(_mainWidget);
        _mainLayout->addWidget(widget, x, y);
        widget->show();
        return widget;
    }

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
    QLineEdit* _pageDesc = nullptr;

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
