set(CMAKE_AUTOMOC ON)

include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../Utils)
include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../Components)
include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../Achievements/Sort)
include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../Achievements/Graph)
include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../Achievements/Linear)
include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../Achievements/Staque)
include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../Achievements/Greed)
include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../Achievements/Tree)
include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../Achievements/Find)

find_package(Qt6 COMPONENTS Core Widgets Svg REQUIRED)

add_library(dsaa_pages STATIC
    "aboutpage.cpp" 
    "aboutpage.h" 
    "sortpage.h" 
    "sortpage.cpp" 
    "graphpage.h" 
    "graphpage.cpp"  
    "linkedlistpage.h" 
    "linkedlistpage.cpp" 
    "staquepage.h" 
    "staquepage.cpp" 
    "greedpage.h"
    "greedpage.cpp"
    "bstreepage.cpp"
    "bstreepage.h" 
    "findpage.cpp"
    "findpage.h")


target_link_libraries(dsaa_pages PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Svg
)
