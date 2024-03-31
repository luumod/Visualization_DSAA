#ifndef PAGE_WIDGET
#define PAGE_WIDGET

#include <QWidget>

class PushButton;
class QVBoxLayout;
class QGraphicsOpacityEffect;
/**
 * @brief Basic widget of every page.
 */
class PageWidget : public QWidget
{

    Q_OBJECT

public:
    PageWidget(QWidget* parent = 0);
    ~PageWidget();

protected:
    // Page layout and content widget (which holds the actual page elements)
    QVBoxLayout* _stretchLayout = nullptr;
    QWidget* _contentWidget = nullptr;

    // Button widgets for side bar
    PushButton* _iconButton = nullptr;
    PushButton* _textButton = nullptr;

    // Opacity effects
    QGraphicsOpacityEffect* _pageOpacityEffect = nullptr;

    // Page position memory
    QPoint _originPagePosition = QPoint(0, 0);

public:
    /**
     * @brief provide a push button with only an icon.
     */
    virtual PushButton* getPageIconButton(QWidget* context) = 0;

    /**
     * @brief provide a push button with an icon and a description text.
     */
    virtual PushButton* getPageTextButton(QWidget* context) = 0; 

public:
    /**
     * @brief When the current page is selected, provide an on stage animation and open.
     */
    void onStage();  

    /**
     * @brief When the current page is De-selected, provide an off stage animation and close.
     */
    void offStage(); 
};

#endif // !PAGE_WIDGET

