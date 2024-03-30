set(CMAKE_AUTOMOC ON)

include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../Pages)
include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../Utils)
include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../Components)
include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../Achievements/Sort)
include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../Achievements/Graph)

find_package(Qt6 COMPONENTS Core Widgets Svg REQUIRED)

add_library(dsaa_window STATIC
    "mainwindow.cpp" 
    "mainwindow.h"
)

target_link_libraries(dsaa_window PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Svg
)
