#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QColorDialog>
#include <QDebug>

class ColorPicker : public QWidget {
public:
    ColorPicker(QWidget* parent = nullptr) : QWidget(parent) {
        QVBoxLayout* layout = new QVBoxLayout(this);

        // 创建按钮
        button = new QPushButton("选择颜色", this);
        connect(button, &QPushButton::clicked, this, &ColorPicker::openColorDialog);

        layout->addWidget(button);
        setLayout(layout);
    }

private slots:
    void openColorDialog() {
        // 打开颜色对话框
        QColor color = QColorDialog::getColor(Qt::white, this, "选择颜色");
        if (color.isValid()) {
            // 如果用户选择了颜色，保存颜色值并更新按钮背景色
            button->setStyleSheet(QString("background-color: %1").arg(color.name()));
            qDebug() << "选定的颜色：" << color.name();
        }
    }

private:
    QPushButton* button;
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    ColorPicker colorPicker;
    colorPicker.setWindowTitle("颜色选择器");
    colorPicker.show();

    return app.exec();
}
