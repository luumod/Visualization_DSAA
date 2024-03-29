#ifndef SORT_TASK
#define SORT_TASK

#include <QObject>

class SortObject;
class SortTask : public QObject {
    Q_OBJECT
public:
    explicit SortTask(SortObject* bubbleSort, int count, int interval);

public slots:
    void run();

signals:
    void finished();

private:
    SortObject* sort{ nullptr };
    int count;
    int interval;
};

#endif // !SORT_TASK
