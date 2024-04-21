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

        // ������ť
        button = new QPushButton("ѡ����ɫ", this);
        connect(button, &QPushButton::clicked, this, &ColorPicker::openColorDialog);

        layout->addWidget(button);
        setLayout(layout);
    }

private slots:
    void openColorDialog() {
        // ����ɫ�Ի���
        QColor color = QColorDialog::getColor(Qt::white, this, "ѡ����ɫ");
        if (color.isValid()) {
            // ����û�ѡ������ɫ��������ɫֵ�����°�ť����ɫ
            button->setStyleSheet(QString("background-color: %1").arg(color.name()));
            qDebug() << "ѡ������ɫ��" << color.name();
        }
    }

private:
    QPushButton* button;
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    ColorPicker colorPicker;
    colorPicker.setWindowTitle("��ɫѡ����");
    colorPicker.show();

    return app.exec();
}
