#include "mainwindow.h"
#include "customWidgets.h"
#include "common.h"

MainWindow::MainWindow(QWidget* parent)
	:QMainWindow(parent){
	resize(640, 480);
	init();
}

MainWindow::~MainWindow(){

}

void MainWindow::init(){
	icon_settings = new customIcon(ICON_FILE QString("settings.svg"), "", 10, this);
	icon_settings->move(100, 100);

	icon_back = new customIcon(ICON_FILE "back.svg", "", 10, this);
	icon_back->move(200, 100);
}
