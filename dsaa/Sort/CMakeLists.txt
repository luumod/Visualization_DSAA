set(CMAKE_AUTOMOC ON)

include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../utils)

find_package(Qt6 COMPONENTS Core Widgets Svg REQUIRED)

add_library(dsaa_sort STATIC
    "BubbleSimple.h" 
    "BubbleSimple.cpp" 
    "BubbleSort.h" 
    "BubbleSort.cpp"
    "InsertionSort.cpp"
    "InsertionSort.h"
    "MainCanvas.h"
    "MainCanvas.cpp"
    "QuickSort.cpp"
    "QuickSort.h"
    "SelectionSort.h"
    "SelectionSort.cpp"

    "ShellSort.h"
    "ShellSort.cpp" 
    "SortFactory.cpp" 
    "SortFactory.h"
    "SortObject.h"
    "SortObject.cpp")

target_link_libraries(dsaa_sort PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Svg
)
