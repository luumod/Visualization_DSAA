#include "greedyviewlog.h"

GreedyViewLog::GreedyViewLog(QString log, QWidget* parent) :
    QLabel(parent)
{
    logText = log;
    this->setFont(logFont);
    this->setText(log);
    this->setFixedHeight(QFontMetrics(logFont).lineSpacing());
}

void GreedyViewLog::resizeEvent(QResizeEvent* event) {
    QString elideText = QFontMetrics(logFont).elidedText(logText, Qt::ElideRight, this->width() - 5);
    this->setText(elideText);
    this->show();
}