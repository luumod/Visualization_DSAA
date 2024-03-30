set(CMAKE_AUTOMOC ON)

include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../../Utils)
include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../../Components)

find_package(Qt6 COMPONENTS Core Widgets Svg REQUIRED)

add_library(dsaa_graph STATIC
    "graph_implement.h"
    "graph_implement.cpp"
    "graph_view.h"
    "graph_view.cpp"
    "graphcanvas.h"
    "graphcanvas.cpp"
)

target_link_libraries(dsaa_graph PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Svg
)
