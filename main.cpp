#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QString>
#include "widgets/mainwindow.h"

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	MainWindow* window = new MainWindow;
	window->show();

	return app.exec();
}