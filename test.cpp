#include <QApplication>
#include <QTimer>
#include <QDebug>
#include <QEventLoop>
#include "Components/framelesswindow.h"

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    //// ����һ���¼�ѭ��
    //QEventLoop* eventLoop = new QEventLoop;

    //// ���¼�ѭ���еȴ� 1 ����
    //QTimer::singleShot(1000, eventLoop, [=]() {
    //    eventLoop->quit(); //�˳�
    //});
    //qInfo() << eventLoop->exec();
    //qInfo() << "continue";
    //qInfo() << "consecutive";

    // �˳�����
    return a.exec();
}
