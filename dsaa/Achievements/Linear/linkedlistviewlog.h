#ifndef STAQUEVIEWLOG_H_
#define STAQUEVIEWLOG_H_

#include <QLabel>

class LinkedListViewLog : public QLabel {
    Q_OBJECT

private:
    QFont logFont = QFont("Corbel", 12);
    QString logText;
    void resizeEvent(QResizeEvent* event);
public:
    LinkedListViewLog(QString log, QWidget* parent = nullptr);
};

#endif // !


