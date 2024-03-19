set(CMAKE_AUTOMOC ON)

include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../common)

find_package(Qt6 COMPONENTS Core Widgets Svg REQUIRED)

add_library(dsaa_conponents STATIC
    "customIcon.h" 
    "customIcon.cpp" 
    "singleSelectGroup.h" 
    "singleSelectGroup.cpp"
    "bigIconButton.cpp"
    "bigIconButton.h"
    "horizontalValueAdjuster.h"
    "horizontalValueAdjuster.cpp"
    "textInputItem.cpp"
    "textInputItem.h"
    "textButton.h"
    "textButton.cpp"

    "framelesswindow.h"
    "framelesswindow.cpp")

target_link_libraries(dsaa_conponents PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Svg
)
