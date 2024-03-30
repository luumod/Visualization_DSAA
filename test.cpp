#include <QApplication>
#include <QTimer>
#include <QDebug>
#include <QEventLoop>
#include "Components/framelesswindow.h"

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    //// 创建一个事件循环
    //QEventLoop* eventLoop = new QEventLoop;

    //// 在事件循环中等待 1 秒钟
    //QTimer::singleShot(1000, eventLoop, [=]() {
    //    eventLoop->quit(); //退出
    //});
    //qInfo() << eventLoop->exec();
    //qInfo() << "continue";
    //qInfo() << "consecutive";

    // 退出程序
    return a.exec();
}
