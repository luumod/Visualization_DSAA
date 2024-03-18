cmake_minimum_required(VERSION 3.12)

project(Visual_DSAA)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/dsaa)

# file(GLOB_RECURSE Widget_Header ${CMAKE_CURRENT_SOURCE_DIR}/dsaa/widget/ *.h)
# file(GLOB_RECURSE Widget_Src ${CMAKE_CURRENT_SOURCE_DIR}/dsaa/widget/ *.cpp)
# message("****************** ", ${CMAKE_CURRENT_SOURCE_DIR})
# message("****************** ", ${Widget_Header})
# message("****************** ", ${Widget_Src})
add_executable(Visual_DSAA "main.cpp" "dsaa/common/common.h")

find_package(Qt6 COMPONENTS Core Widgets Svg REQUIRED)

add_subdirectory(dsaa)

target_link_libraries(Visual_DSAA
    PRIVATE
    dsaa_widgets
    Qt6::Core
    Qt6::Widgets
    Qt6::Svg
)