#ifndef GREED_VIEW_H_
#define GREED_VIEW_H_

#include <QWidget>
#include <QVector>

class QTimer;
class GreedyViewLog;
class GreedyChangeView : public QWidget
{
	Q_OBJECT

public:
	struct Task {
		int start;
		int end;
	};
	int type = 0;

	GreedyChangeView(QWidget* parent = nullptr);

	void showDefault();
	void setClear();
	void pop_back();

	void addTask(Task task);
	void setValues(QVector<int> values);
	void setCurrentCoins(QVector<int> coins);
	void setTargetAmout(int amout);
	void setCurrentAmout(int cur_amout);
protected:
	void paintEvent(QPaintEvent* event) override;
signals:
	void logAdded(GreedyViewLog* log);
public slots:
	void startChange();
	void nextStep();
private:


	QFont font = QFont("Corbel", 13, QFont::Normal, true);

	//-----------------------
	// 1
	QTimer* timer{ nullptr };
	QVector<int> coinValues;
	QVector<int> currentCoins;
	int targetAmount;
	int currentAmount = 0;


	//-----------------------
	// 2
	QVector<Task> tasks_copy;
	QVector<Task> tasks;
	QVector<Task> currentSchedule;
};


#endif // !GREED_VIEW_H_
