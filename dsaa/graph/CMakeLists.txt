set(CMAKE_AUTOMOC ON)

include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../utils)
include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../conponents)

find_package(Qt6 COMPONENTS Core Widgets Svg REQUIRED)

add_library(dsaa_graph STATIC
    "graph_implement.h"
    "graph_implement.cpp"
    "graph_view.h"
    "graph_view.cpp"
    "mycanvas.h"
    "mycanvas.cpp"
)

target_link_libraries(dsaa_graph PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Svg
)
