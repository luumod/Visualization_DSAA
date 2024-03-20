#ifndef MAIN_WINDOW
#define MAIN_WINDOW

#include <QMainWindow>
#include "conponents/framelesswindow.h"

class customIcon;
class MainWindow: public FramelessWindow {
	Q_OBJECT;
public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

	void init();

	void testFrameLessWindow();
private:
	customIcon* icon_settings{nullptr};
	customIcon* icon_back{ nullptr };
};

#endif