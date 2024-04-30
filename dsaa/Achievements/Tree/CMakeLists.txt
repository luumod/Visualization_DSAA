set(CMAKE_AUTOMOC ON)

include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../../Utils)
include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../../Components)

find_package(Qt6 COMPONENTS Core Widgets Svg REQUIRED)

add_library(dsaa_tree STATIC
    "bsearchtreecanvas.h"
    "bsearchtreecanvas.cpp"
    "bsearchtreeview.h"
    "bsearchtreeview.cpp" 
    "bsearchtree.h"
    "bsearchtree.cpp" 
    "bsearchtreenodeitem.cpp" 
    "bsearchtreenodeitem.h" 
    "bsearchtreeviewlog.cpp" 
    "bsearchtreeviewlog.h")

target_link_libraries(dsaa_tree PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Svg
)
