set(CMAKE_AUTOMOC ON)

include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../../Utils)
include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../../Components)

find_package(Qt6 COMPONENTS Core Widgets Svg REQUIRED)

add_library(dsaa_staque STATIC
    queue.h
    queue.cpp
    stack.h
    stack.cpp
    staqueview.h 
    staqueview.cpp 
    staquecanvas.h 
    staquecanvas.cpp)

target_link_libraries(dsaa_staque PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Svg
)
