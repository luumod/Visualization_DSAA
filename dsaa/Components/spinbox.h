#ifndef SPINBOX_H
#define SPINBOX_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QGraphicsOpacityEffect>
#include <QPushButton>

class SpinBox : public QWidget
{
    Q_OBJECT

public:
    explicit SpinBox(const QString& name, QWidget* parent = nullptr);

    void setValue(int value);
    int value() const;

    void setRange(int min, int max);
    void setEnabled(bool enable);

signals:
    void valueChanged(int value);

protected:
    void resizeEvent(QResizeEvent* event) override;
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private slots:
    void onUpButtonClicked();
    void onDownButtonClicked();

private:
    QLabel* itemName;
    QLineEdit* editor;
    QWidget* bgWidget;
    QWidget* indicator;
    QGraphicsOpacityEffect* opac;
    QPushButton* upButton;
    QPushButton* downButton;

    int margin = 10;
    int spacing = 5;
    int curValue;
    int minValue;
    int maxValue;
    bool enabled = true;
    bool mousePressed = false;

    void updateEditor();
    void enterEditEffect();
    void leaveEditEffect();
};

#endif // SPINBOX_H