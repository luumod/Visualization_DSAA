#ifndef SPINBOX_H
#define SPINBOX_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QGraphicsOpacityEffect>
#include <QPushButton>

class QVBoxLayout;
class QHBoxLayout;
class SpinBox : public QWidget
{
    Q_OBJECT

public:
    explicit SpinBox(const QString& name, int minValue, int maxValue, int curValue, QWidget* parent = nullptr);

    void setValue(int value);
    int value() const;

    void setRange(int min, int max);
    void setEnabled(bool enable);
    void recoverDefaultValue();
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

    QWidget* indicator_left;
    QGraphicsOpacityEffect* opac_left;

    QWidget* indicator_edit;
    QGraphicsOpacityEffect* opac_edit;

    QPushButton* upButton;
    QPushButton* downButton;

    QHBoxLayout* main_layout{ nullptr };
    QWidget* main_widget{ nullptr };

    int margin = 10;
    int spacing = 5;
    int defaultValue;
    int curValue;
    int minValue;
    int maxValue;
    bool enabled = true;
    bool mousePressed = false;

    void updateEditor();
    void enterEditEffect();
    void leaveEditEffect();
};


class SpinBoxGroup : public QWidget {
    Q_OBJECT

private:
    const int middleSpacing = 5;
    const int bottomSpacing = 30;
    QLabel* groupName;
    QVBoxLayout* mainLayout;
    int selectedID = -1;
    QVector<SpinBox*> spinboxs;

public:
    SpinBoxGroup(QString name = "", QWidget* parent = nullptr);
    void AddItem(SpinBox* item);
    qreal value() { return selectedID; }

signals:
    void spinBoxItemChange(int changeID);
    void spinBoxReset();
};

#endif // SPINBOX_H