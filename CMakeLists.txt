cmake_minimum_required(VERSION 3.12)

project(Visual_DSAA)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/dsaa)

add_executable(Visual_DSAA "main.cpp" )

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

add_subdirectory(dsaa)

target_link_libraries(Visual_DSAA
    PRIVATE
    dsaa_window
    dsaa_pages
    dsaa_components
    dsaa_utils
    dsaa_sort
    dsaa_graph
    dsaa_linear
    dsaa_staque
    dsaa_greed
    dsaa_tree
    Qt6::Core
    Qt6::Widgets
)