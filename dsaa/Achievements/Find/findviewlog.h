#ifndef FIND_VIEWLOG_H_
#define FIND_VIEWLOG_H_

#include <QLabel>

class FindViewLog : public QLabel {
    Q_OBJECT

private:
    QFont logFont = QFont("Corbel", 12);
    QString logText;
    void resizeEvent(QResizeEvent* event);
public:
    FindViewLog(QString log, QWidget* parent = nullptr);
};

#endif // !


