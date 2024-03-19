#ifndef BIG_ICON_BUTTON
#define BIG_ICON_BUTTON

#include <QWidget>

class QPixmap;
class QLabel;
class bigIconButton : public QWidget {
    Q_OBJECT

private:
    QPixmap* iconImg;
    QLabel* text;
    QLabel* icon;
    QWidget* bgWidget;
    QWidget* indicator;

    int cornerRadius;
    QString radiusStyle;

    bool selectable = false;
    bool mousePressed = false;
    bool onSelected = false;

    void enterEvent(QEnterEvent* event);
    void leaveEvent(QEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void resizeEvent(QResizeEvent* event);

public:
    bigIconButton(const QString& iconPath, const QString& description, int radius, QWidget* parent = nullptr);
    void setSelectable(bool sel = true) { selectable = sel; }
    void setScale(qreal scale);

signals:
    void clicked();
    void selected();
};

#endif // !BIG_ICON_BUTTON
