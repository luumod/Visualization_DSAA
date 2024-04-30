#include "greedview.h"
#include <QTimer>
#include <QPainter>

GreedyChangeView::GreedyChangeView(QWidget* parent) : 
	QWidget(parent)
{
	setWindowTitle("Greedy Change Demo");

	showDefault();
}

void GreedyChangeView::showDefault()
{
	coinValues.clear();
	coinValues << 50 << 25 << 10 << 5 << 2;
	targetAmount = 99;
	currentCoins.clear();
}

void GreedyChangeView::setValues(QVector<int> values)
{
	coinValues = std::move(values);
}

void GreedyChangeView::setCurrentCoins(QVector<int> coins)
{
	currentCoins = std::move(coins);
}

void GreedyChangeView::setTargetAmout(int amout)
{
	targetAmount = amout;
}

void GreedyChangeView::setCurrentAmout(int cur_amout)
{
	currentAmount = cur_amout;
}

void GreedyChangeView::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	QPainter painter(this);

	painter.fillRect(0, 0, width(), height(), Qt::white);

	// 绘制零钱
	painter.setPen(Qt::black);
	for (int i = 0; i < coinValues.size(); ++i)
	{
		painter.drawRect(100 + i * 50, height() - 50, 40, 40);
		painter.drawText(120 + i * 50, height() - 25, QString::number(coinValues[i]));
	}

	// 绘制目标金额
	painter.setPen(Qt::red);
	painter.drawText(width() / 2 - 40, height() - 100, "Target Amount: " + QString::number(targetAmount));

	// 绘制当前找零的金额
	painter.setPen(Qt::blue);
	painter.drawText(width() / 2 - 40, height() - 75, "Current Amount: " + QString::number(currentAmount));

	// 绘制已经找到的硬币
	painter.setPen(Qt::darkGreen);
	int x = 50;
	int y = height() - 150;
	for (int i = 0; i < currentCoins.size(); ++i)
	{
		painter.drawRect(x, y, 40, 40);
		painter.drawText(x + 20, y + 25, QString::number(currentCoins[i]));
		x += 50;
	}
}

void GreedyChangeView::startChange() {
	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &GreedyChangeView::nextStep);
	timer->start(1000);
}

void GreedyChangeView::nextStep()
{
	if (currentAmount == targetAmount)
	{
		// 找零完成，停止动画
		timer->stop();
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

	update();
}