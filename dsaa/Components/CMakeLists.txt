set(CMAKE_AUTOMOC ON)

include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../Utils)

find_package(Qt6 COMPONENTS Core Widgets Svg REQUIRED)

add_library(dsaa_components STATIC
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
    "framelesswindow.cpp" 
    "sidebar.cpp" 
    "sidebar.h"
    "pushbutton.h"
    "pushbutton.cpp"
    "pagewidget.h"
    "pagewidget.cpp" 
    "lineeditwidget.cpp" 
    "lineeditwidget.h" 
    "customScrollContainer.cpp" 
    "customScrollContainer.h"
    "slidepage.h"
    "slidepage.cpp"
    "spinbox.h"
    "spinbox.cpp")

target_link_libraries(dsaa_components PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Svg
)
