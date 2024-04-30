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
	QPainter painter(this);

	painter.fillRect(0, 0, width(), height(), Qt::white);

	int x = 10;
	int y = 10;
	int rectWidth = 40;
	int rectHeight = 40;
	int spacing = 10;

	// ªÊ÷∆¡„«Æ
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

void GreedyChangeView::startChange() {
	if (!timer) {
		timer = new QTimer(this);
		connect(timer, &QTimer::timeout, this, &GreedyChangeView::nextStep);
	}
	timer->start(300);
	currentCoins.clear();
	currentAmount = 0;
	std::sort(coinValues.begin(), coinValues.begin(), std::greater<>());
}

void GreedyChangeView::nextStep()
{
	if (currentAmount == targetAmount)
	{
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