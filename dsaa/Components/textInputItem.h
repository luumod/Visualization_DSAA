#ifndef TEXT_INPUT_ITEM
#define TEXT_INPUT_ITEM

#include <QWidget>

class QLabel;
class QLineEdit;
class QGraphicsOpacityEffect;
class QValidator;
class textInputItem : public QWidget {
    Q_OBJECT

private:
    const int margin = 10;
    const int spacing = 10;
    QLabel* itemName;
    QLineEdit* editor;
    QWidget* bgWidget;
    QWidget* indicator;
    QGraphicsOpacityEffect* opac;

    QString curText = "";
    bool mousePressed = false;
    bool onEditing = false;

    bool enabled = true;

    void enterEditEffect();
    void leaveEditEffect();

    void enterEvent(QEnterEvent* event);
    void leaveEvent(QEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void resizeEvent(QResizeEvent* event);

public:
    textInputItem(const QString& name, QWidget* parent = nullptr);
    QLineEdit* lineEditor();
    QString value();

    void setValue(const QString& text);
    void setValidator(QValidator* vali);
    void setEnabled(bool enable = true);

signals:
    void textEdited(QString text);
};

#endif // !TEXT_INPUT_ITEM
