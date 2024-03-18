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
	icon_settings->move(10,10);

	icon_back = new customIcon(ICON_FILE "back.svg", "back_icon", 10, this);
	icon_back->move(30,10);


	singleSelectGroup* structureSel = new singleSelectGroup("Structure", this);
	selectionItem* item_1 = new selectionItem("AL", "Use adjacent list for canvas", this);
	selectionItem* item_2 = new selectionItem("AML", "Use multiple adjacent list for canvas", this);
	structureSel->AddItem(item_1);
	structureSel->AddItem(item_2);

	structureSel->move(10, 50);
}
