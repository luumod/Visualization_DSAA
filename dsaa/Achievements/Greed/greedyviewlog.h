#ifndef BSEARCHTREEVIEWLOG_H_
#define BSEARCHTREEVIEWLOG_H_

#include <QLabel>

class GreedyViewLog : public QLabel {
    Q_OBJECT

private:
    QFont logFont = QFont("Corbel", 12);
    QString logText;
    void resizeEvent(QResizeEvent* event);
public:
    GreedyViewLog(QString log, QWidget* parent = nullptr);
};

#endif // !


