set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

add_library(dsaa_utils STATIC
    "common.h"
    "logger.h"
    "logger.cpp")

target_link_libraries(dsaa_utils PRIVATE
    Qt6::Core
    Qt6::Widgets
)
