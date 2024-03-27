#ifndef SORT_PAGE_H
#define SORT_PAGE_H

#include "conponents/pagewidget.h"

class QLabel;
class QHBoxLayout;
class QLineEdit;
class QGridLayout;
class SortPage : public PageWidget
{
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
    QVBoxLayout* _titleAreaLayout = nullptr;
    const QFont _titleFont = QFont("DengXian", 26, QFont::ExtraLight);
    QLabel* _titleLabel = nullptr;
    QLineEdit* _pageDesc = nullptr;

    QWidget* _mainWidget = nullptr;

    // grid layout
    QGridLayout* _mainLayout = nullptr;

public:
    virtual PushButton* getPageIconButton(QWidget* context) override;  // provide a push button with only an icon
    virtual PushButton* getPageTextButton(QWidget* context) override;  // provide a push button with an icon and a description text

signals:
    void nameChanged(QString name);
    void descChanged(QString desc);
};

#endif // MYCANVAS_H
