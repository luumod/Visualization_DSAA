#ifndef TEXT_BUTTON
#define TEXT_BUTTON

#include <QWidget>

class QLabel;
class textButton : public QWidget {
    Q_OBJECT

public:
    QString defaultColor = "#0a0078d4";
private:
    QLabel* btnText;
    QWidget* bgWidget;
    QString hoverColor = "#1a0078d4";
    QString pressedColor = "#2a0078d4";

    bool mousePressed;

    void enterEvent(QEnterEvent* event);
    void leaveEvent(QEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void resizeEvent(QResizeEvent* event);

public:
    textButton(QString text, QWidget* parent = nullptr, qreal ratio = 0.5);
    textButton(QString text, QString defaultColor, QWidget* parent = nullptr, qreal ratio = 0.5);
    textButton(QString text, QString defC, QString hoverC, QString pressedC, QWidget* parent = nullptr, qreal ratio = 0.5);

    void setDefaultColor(const QString& color_text) {
        defaultColor = color_text;
        bgWidget->setStyleSheet(QString("background-color: %1").arg(defaultColor));
    }
    void setDefaultColor(QColor color) {
        defaultColor = color.name();
        bgWidget->setStyleSheet(QString("background-color: %1").arg(defaultColor));
    }
signals:
    void clicked();
};

#endif // !TEXT_BUTTON
