set(CMAKE_AUTOMOC ON)

include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../../Utils)
include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../../Components)

find_package(Qt6 COMPONENTS Core Widgets Svg REQUIRED)

add_library(dsaa_find STATIC
    findview.h 
    findview.cpp 
    findcanvas.h 
    findcanvas.cpp 
    findviewlog.h 
    findviewlog.cpp 
    findnodeitem.h
    findnodeitem.cpp)

target_link_libraries(dsaa_find PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Svg
)
