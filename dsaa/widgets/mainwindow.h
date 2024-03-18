#include <QMainWindow>

class customIcon;
class MainWindow: public QMainWindow{
	Q_OBJECT;
public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

	void init();
private:
	customIcon* icon_settings{nullptr};
	customIcon* icon_back{ nullptr };
};