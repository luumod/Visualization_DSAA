#include "greedview.h"
#include "greedyviewlog.h"
#include <QTimer>
#include <QPainter>
#include <QDebug>

GreedyChangeView::GreedyChangeView(QWidget* parent) : 
	QWidget(parent)
{
	showDefault();
}

void GreedyChangeView::showDefault()
{
	if (type == 0) {
		coinValues.clear();
		coinValues << 50 << 25 << 10 << 5 << 2;
		targetAmount = 99;
		currentCoins.clear();
	}
	else if (type == 1) {
		tasks_copy.clear();
		tasks.clear();
		tasks = { {0,6},{1,4},{2,13},{3,5},{3,8},{5,7},{5,9},{6,10},{8,11},{8,12},{12,14} };
		for (auto& x : tasks) {
			tasks_copy.push_back(x);
		}
		currentSchedule.clear();
	}
	update();
}

void GreedyChangeView::setClear()
{
	if (type == 0) {

	}
	else if (type == 1) {
		tasks.clear();
		tasks_copy.clear();
		currentSchedule.clear();
	}
	update();
}

void GreedyChangeView::pop_back()
{
	if (type == 0) {

	}
	else if (type == 1) {
		if (!tasks_copy.isEmpty()) {
			tasks_copy.pop_back();
		}
		if (!currentSchedule.isEmpty()) {
			currentSchedule.clear();
		}
	}
	update();
}

void GreedyChangeView::addTask(Task task)
{
	tasks.emplace_back(task);
	tasks_copy.emplace_back(task);
	currentSchedule.clear();
	update();
}

void GreedyChangeView::setValues(QVector<int> values)
{
	coinValues = std::move(values);
	currentAmount = 0;
	currentCoins.clear();
	update();
}

void GreedyChangeView::setCurrentCoins(QVector<int> coins)
{
	currentCoins = std::move(coins);
	update();
}

void GreedyChangeView::setTargetAmout(int amount)
{
	targetAmount = amount;
	currentAmount = 0;
	currentCoins.clear();
	update();
}

void GreedyChangeView::setCurrentAmout(int cur_amout)
{
	currentAmount = cur_amout;
	update();
}

void GreedyChangeView::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	int x = 10;
	int y = 10;
	int rectWidth = 40;
	int rectHeight = 40;
	int spacing = 10;
	QPainter painter(this);
	painter.setFont(font);
	painter.fillRect(0, 0, width(), height(), Qt::white);

	if (type == 0) {
		painter.setPen(Qt::black);
		for (int i = 0; i < coinValues.size(); ++i)
		{
			if (x + rectWidth > width())
			{
				x = 10;
				y += rectHeight + spacing;
			}

			painter.drawRect(x, y, rectWidth, rectHeight);
			painter.drawText(x + 20, y + rectHeight / 2, QString::number(coinValues[i]));

			x += rectWidth + spacing;
		}

		painter.setPen(Qt::red);
		painter.drawText(width() / 2 - 40, height() - 100, "Target Amount: " + QString::number(targetAmount));

		painter.setPen(Qt::blue);
		painter.drawText(width() / 2 - 40, height() - 75, "Current Amount: " + QString::number(currentAmount));

		painter.setPen(Qt::darkGreen);
		x = 10;
		y += 100;
		for (int i = 0; i < currentCoins.size(); ++i)
		{
			if (x + rectWidth > width())
			{
				x = 10;
				y += rectHeight + spacing;
			}

			painter.drawRect(x, y, rectWidth, rectHeight);
			painter.drawText(x + 20, y + rectHeight / 2, QString::number(currentCoins[i]));
			x += rectWidth + spacing;
		}
	}
	else if (type == 1) {
		painter.setPen(Qt::black);
		for (int i = 0; i < tasks_copy.size(); ++i)
		{
			if (x + rectWidth > width())
			{
				x = 10;
				y += rectHeight + spacing;
			}

			painter.drawRect(x, y, rectWidth, rectHeight);
			painter.drawText(x, y + rectHeight / 2, QString::number(tasks_copy[i].start));
			painter.drawText(x + 20, y + rectHeight / 2, QString::number(tasks_copy[i].end));

			x += rectWidth + spacing;
		}

		painter.setPen(Qt::darkGreen);
		x = 10;
		y += 100;
		for (int i = 0; i < currentSchedule.size(); ++i)
		{
			if (x + rectWidth > width())
			{
				x = 10;
				y += rectHeight + spacing;
			}

			painter.drawRect(x, y, rectWidth, rectHeight);
			//painter.drawText(x + 10, y + rectHeight / 2, QString::number(i + 1));
			painter.drawText(x, y - 10, QString::number(currentSchedule[i].start));
			painter.drawText(x + rectWidth - 20, y - 10, QString::number(currentSchedule[i].end));
			x += rectWidth + spacing;
		}
	}
}

void GreedyChangeView::startChange() {
	if (!timer) {
		timer = new QTimer(this);
		connect(timer, &QTimer::timeout, this, &GreedyChangeView::nextStep);
	}
	timer->start(300);
	if (type == 0) {
		currentCoins.clear();
		currentAmount = 0;
		std::sort(coinValues.begin(), coinValues.begin(), std::greater<>());
	}
	else if (type == 1) {
		currentSchedule.clear();
		tasks = tasks_copy;
		std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
			return a.end < b.end;
			});
	}
}

void GreedyChangeView::nextStep()
{
	if (type == 0) {
		if (currentAmount == targetAmount)
		{
			timer->stop();
			QString str;
			for (auto& x : currentCoins) {
				str += QString::number(x) + " ";
			}
			emit logAdded(new GreedyViewLog(QString("[coin] best ways: %1").arg(str)));
			return;
		}

		for (int i = 0; i < coinValues.size(); ++i)
		{
			if (currentAmount + coinValues[i] <= targetAmount)
			{
				currentCoins.push_back(coinValues[i]);
				currentAmount += coinValues[i];
				break;
			}
		}
	}
	else if (type == 1) {
		if (tasks.empty())
		{
			timer->stop();
			QString str;
			for (auto& x : currentSchedule) {
				str += QString::number(x.start) + "-" + QString::number(x.end) + " ";
			}
			emit logAdded(new GreedyViewLog(QString("[task] most doing: %1 task").arg(currentSchedule.size())));
			emit logAdded(new GreedyViewLog(QString("[task] detail: %1").arg(str)));
			return;
		}

		Task currentTask = tasks.front();
		tasks.erase(tasks.begin());
		currentSchedule.push_back(currentTask);

		tasks.erase(std::remove_if(tasks.begin(), tasks.end(), [currentTask](const Task& t) {
			return t.start < currentTask.end;
			}), tasks.end());
	}

	update();
}