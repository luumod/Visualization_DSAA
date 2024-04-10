set(CMAKE_AUTOMOC ON)

include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../../Utils)
include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../../Components)

find_package(Qt6 COMPONENTS Core Widgets Svg REQUIRED)

add_library(dsaa_linear STATIC
    base_list.h
    base_list.cpp
    doubly_linked_list.h
    doubly_linked_list.cpp
    linkedlistcavnas.h
    linkedlistcavnas.cpp
    lineardatafactory.h
    lineardatafactory.cpp
)

target_link_libraries(dsaa_linear PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Svg
)
