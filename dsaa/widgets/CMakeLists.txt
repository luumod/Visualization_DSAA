set(CMAKE_AUTOMOC ON)

include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../utils)
include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../conponents)
include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../Sort)

find_package(Qt6 COMPONENTS Core Widgets Svg REQUIRED)

add_library(dsaa_widgets STATIC
    "mainwindow.cpp" 
    "mainwindow.h"  
    "aboutpage.cpp" 
    "aboutpage.h" 
    "homepage.h" 
    "homepage.cpp" 
    "slidepage.cpp" 
    "slidepage.h" 
    "sortpage.cpp" 
    "sortpage.h")

target_link_libraries(dsaa_widgets PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Svg
)
