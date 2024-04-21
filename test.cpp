#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QColorDialog>
#include <QDebug>
#include <QMainWindow>
#include <vector>
#include <QPainter>

template <typename T>
class Stack {
public:
	void push(const T& item);
	void pop();
	T& top();
	bool isEmpty() const;
	size_t size() const;

private:
	std::vector<T> data;
};

template <typename T>
void Stack<T>::push(const T& item) {
	data.push_back(item);
}

template <typename T>
void Stack<T>::pop() {
	if (!isEmpty()) {
		data.pop_back();
	}
}

template <typename T>
T& Stack<T>::top() {
	return data.back();
}

template <typename T>
bool Stack<T>::isEmpty() const {
	return data.empty();
}

template <typename T>
size_t Stack<T>::size() const {
	return data.size();
}

template <typename T>
class Queue {
public:
	void enqueue(const T& item);
	void dequeue();
	T& front();
	bool isEmpty() const;
	size_t size() const;

private:
	std::vector<T> data;
};

template <typename T>
void Queue<T>::enqueue(const T& item) {
	data.push_back(item);
}

template <typename T>
void Queue<T>::dequeue() {
	if (!isEmpty()) {
		data.erase(data.begin());
	}
}

template <typename T>
T& Queue<T>::front() {
	return data.front();
}

template <typename T>
bool Queue<T>::isEmpty() const {
	return data.empty();
}

template <typename T>
size_t Queue<T>::size() const {
	return data.size();
}

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

protected:
	void paintEvent(QPaintEvent* event) override;

private slots:
	void on_pushButton_clicked();
	void on_popButton_clicked();
	void on_enqueueButton_clicked();
	void on_dequeueButton_clicked();

private:
	Stack<int> stack;
	Queue<int> queue;
	QLineEdit* stackLineEdit;
	QLineEdit* queueLineEdit;
	QPushButton* pushButton;
	QPushButton* popButton;
	QPushButton* enqueueButton;
	QPushButton* dequeueButton;
};

void MainWindow::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	int x = 50;
	int y = 50;
	int width = 50;
	int height = 30;
	int spacing = 10;

	// 绘制栈
	painter.drawText(x, y - 20, "Stack");
	for (int i = 0; i < stack.size(); ++i) {
		painter.drawRect(x, y, width, height);
		painter.drawText(x + 10, y + 20, QString::number(stack.top()));
		y += height + spacing;
	}

	// 绘制队列
	x = 200;
	y = 50;
	painter.drawText(x, y - 20, "Queue");
	for (int i = 0; i < queue.size(); ++i) {
		painter.drawRect(x, y, width, height);
		painter.drawText(x + 10, y + 20, QString::number(queue.front()));
		queue.dequeue();
		queue.enqueue(queue.front());
		x += width + spacing;
	}
}

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent) {
	resize(640, 480);
	stackLineEdit = new QLineEdit(this);
	stackLineEdit->move(10, 10);

	queueLineEdit = new QLineEdit(this);
	queueLineEdit->move(10, 100);

	QPushButton* pushButton = new QPushButton("入栈",this);
	pushButton->move(100, 10);
	QPushButton* popButton = new QPushButton("出栈", this);
	pushButton->move(100, 50);
	QPushButton* enqueueButton = new QPushButton("入队", this);
	pushButton->move(200, 10);;
	QPushButton* dequeueButton = new QPushButton("出队", this);
	pushButton->move(200, 50);

	connect(pushButton, &QPushButton::clicked, this, on_pushButton_clicked);
	connect(popButton, &QPushButton::clicked, this, on_popButton_clicked);
	connect(enqueueButton, &QPushButton::clicked, this, on_enqueueButton_clicked);
	connect(dequeueButton, &QPushButton::clicked, this, on_dequeueButton_clicked);
}

MainWindow::~MainWindow() {
}

void MainWindow::on_pushButton_clicked() {
	int value = stackLineEdit->text().toInt();
	stack.push(value);
	stackLineEdit->clear();
	update();
}

void MainWindow::on_popButton_clicked() {
	if (!stack.isEmpty()) {
		stack.pop();
		update();
	}
}

void MainWindow::on_enqueueButton_clicked() {
	int value = queueLineEdit->text().toInt();
	queue.enqueue(value);
	queueLineEdit->clear();
	update();
}

void MainWindow::on_dequeueButton_clicked() {
	if (!queue.isEmpty()) {
		queue.dequeue();
		update();
	}
}

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	MainWindow w;
	w.show();
	return app.exec();
}
