set(CMAKE_AUTOMOC ON)

include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../common)

find_package(Qt6 COMPONENTS Core Widgets Svg REQUIRED)

add_library(dsaa_widgets STATIC
    ${CMAKE_CURRENT_LIST_DIR}/customWidgets.cpp
    ${CMAKE_CURRENT_LIST_DIR}/customWidgets.h
 "mainwindow.cpp" "mainwindow.h")

target_link_libraries(dsaa_widgets PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Svg
)
