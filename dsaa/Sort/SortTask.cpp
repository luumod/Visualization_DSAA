#include "SortTask.h"
#include "SortObject.h"

SortTask::SortTask(SortObject* bubbleSort, int count, int interval)
    : sort(bubbleSort), count(count), interval(interval) {

}

void SortTask::run() {
    sort->sort(count, interval);
    emit finished();
}