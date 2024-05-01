set(CMAKE_AUTOMOC ON)

include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../../Utils)
include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../../Components)

find_package(Qt6 COMPONENTS Core Widgets Svg REQUIRED)

add_library(dsaa_greed STATIC
    "greedcanvas.h"
    "greedcanvas.cpp"
    "greedview.h"
    "greedview.cpp" "greedyviewlog.cpp" "greedyviewlog.h")

target_link_libraries(dsaa_greed PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Svg
)
