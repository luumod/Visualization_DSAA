#include "SortFactory.h"
#include "BubbleSort.h"
#include "SelectionSort.h"
#include "InsertionSort.h"
#include "QuickSort.h"
#include "ShellSort.h"

SortFactory::SortFactory(QObject *parent)
    : QObject(parent)
{

}

SortFactory *SortFactory::getInstance()
{
    static SortFactory instance;
    return &instance;
}

SortObject *SortFactory::createSortObject(int row, QObject *parent)
{
    switch (row) {
    case 0: return new BubbleSort(parent);
    case 1: return new SelectionSort(parent);
    case 2: return new InsertionSort(parent);
    case 3: return new QuickSort(parent);
    case 4: return new ShellSort(parent);
    default: break;
    }
    return nullptr;
}

QStringList SortFactory::getSortList() const
{
    return QStringList{
        "Bubble sort"
        , "Selection sort"
        , "Insert sort"
        , "Quick sort"
        , "Shell sort"
    };
}
