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

QString SortFactory::sortCode(int row)
{
    QString bubbleSortCode =
        "void bubble_sort(int arr[], int size)\n"
        "{\n"
        "    for (int i = 0; i < size - 1; i++) {\n"
        "        for (int j = 0; j < size - 1 - i; j++) {\n"
        "            if (arr[j] > arr[j + 1]) {\n"
        "                std::swap(arr[j], arr[j + 1]);\n"
        "            }\n"
        "        }\n"
        "    }\n"
        "}\n";

    QString selectionSortCode =
        "void selection_sort(int arr[], int size)\n"
        "{\n"
        "    for (int i = 0; i < size - 1; i++) {\n"
        "        int min = i;\n"
        "        for (int j = i + 1; j < size; j++) {\n"
        "            if (arr[j] < arr[min]) {\n"
        "                min = j;\n"
        "            }\n"
        "        }\n"
        "        std::swap(arr[i], arr[min]);\n"
        "    }\n"
        "}\n";

    QString insertionSortCode =
        "void insertion_sort(int arr[], int size)\n"
        "{\n"
        "    for (int i = 1; i < size; i++) {\n"
        "        for (int j = i; j > 0; j--) {\n"
        "            if (arr[j] < arr[j - 1]) {\n"
        "                std::swap(arr[j], arr[j - 1]);\n"
        "            }\n"
        "        }\n"
        "    }\n"
        "}\n";

    QString quickSortCode =
        "void quick_sort(int arr[], int low, int high)\n"
        "{\n"
        "    if (low >= high) {\n"
        "        return;\n"
        "    }\n"
        "    int begin = low;\n"
        "    int end = high;\n"
        "    int key = arr[begin];\n"
        "    while (begin < end){\n"
        "        while (begin < end && arr[end] >= key) {\n"
        "            end--;\n"
        "        }\n"
        "        if (begin < end) {\n"
        "            arr[begin] = arr[end];\n"
        "        }\n"
        "        while (begin < end && arr[begin] <= key) {\n"
        "            begin++;\n"
        "        }\n"
        "        if (begin < end) {\n"
        "            arr[end] = arr[begin];\n"
        "        }\n"
        "    }\n"
        "    arr[begin] = key;\n"
        "    quick_sort(arr, low, begin - 1);\n"
        "    quick_sort(arr, begin + 1, high);\n"
        "}\n";

    QString shellSortCode =
        "void shell_sort(int arr[], int size)\n"
        "{\n"
        "    for (int gap = size / 2; gap > 0; gap /= 2) {\n"
        "        for (int i = gap; i < size; i++) {\n"
        "            int j = i;\n"
        "            while (j - gap >= 0 && arr[j] < arr[j - gap]) {\n"
        "                std::swap(arr[j], arr[j - gap]);\n"
        "                j -= gap;\n"
        "            }\n"
        "        }\n"
        "    }\n"
        "}\n";


	switch (row) {
	case 0: return bubbleSortCode;
	case 1: return selectionSortCode;
	case 2: return insertionSortCode;
	case 3: return quickSortCode;
	case 4: return shellSortCode;
	default: break;
	}
}
