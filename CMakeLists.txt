cmake_minimum_required(VERSION 3.12)

project(Visual_DSAA)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/dsaa)

add_executable(Visual_DSAA "main.cpp" "dsaa/graph/mycanvas.cpp" "dsaa/graph/mycanvas.h" "dsaa/graph/graph_implement.cpp" "dsaa/graph/graph_implement.h" "dsaa/graph/graph_view.cpp" "dsaa/graph/graph_view.h")

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

add_subdirectory(dsaa)

target_link_libraries(Visual_DSAA
    PRIVATE
    dsaa_widgets
    dsaa_conponents
    dsaa_utils
    dsaa_sort
    dsaa_graph
    Qt6::Core
    Qt6::Widgets
)