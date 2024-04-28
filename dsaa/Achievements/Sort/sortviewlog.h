#ifndef SORTVIEWLOG_H_
#define SORTVIEWLOG_H_

#include <QLabel>

class SortViewLog : public QLabel {
    Q_OBJECT

private:
    QFont logFont = QFont("Corbel", 12);
    QString logText;
    void resizeEvent(QResizeEvent* event);
public:
    SortViewLog(QString log, QWidget* parent = nullptr);
};

#endif // !


