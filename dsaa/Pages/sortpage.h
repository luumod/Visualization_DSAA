#ifndef GRAPH_PAGE
#define GRAPH_PAGE

#include "Components/pagewidget.h"
#include <QGridLayout>

class QLabel;
class QHBoxLayout;
class LineEditWidget;
class bigIconButton;
class QLineEdit;
class _sortThread;
class SortPage : public PageWidget {

    Q_OBJECT

public:
    SortPage(QWidget* parent = 0);
    ~SortPage();

private:
    // Push button icons
    QLabel* _iconButtonLabel = nullptr;
    QWidget* _textButtonWidget = nullptr;
    QHBoxLayout* _textButtonLayout = nullptr;
    QLabel* _textButtonIcon = nullptr;
    QLabel* _textButtonLabel = nullptr;

    // UI elements
    QVBoxLayout* _windowAreaLayout = nullptr;
    QVBoxLayout* _titleAreaLayout = nullptr;
    const QFont _titleFont = QFont("DengXian", 26, QFont::ExtraLight);
    QLabel* _titleLabel = nullptr;
    QLineEdit* _pageDesc = nullptr;

    QWidget* _mainOperateWidget = nullptr;

    // grid layout
    QHBoxLayout* _mainOperateLayout = nullptr;
    QWidget* _titleAreaWidget = nullptr;

public:
    virtual PushButton* getPageIconButton(QWidget* context) override;
    virtual PushButton* getPageTextButton(QWidget* context) override;
};


#endif // !HOME_PAGE
