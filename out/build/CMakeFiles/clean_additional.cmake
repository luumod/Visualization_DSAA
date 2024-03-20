# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Visual_DSAA_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Visual_DSAA_autogen.dir\\ParseCache.txt"
  "Visual_DSAA_autogen"
  "dsaa\\conponents\\CMakeFiles\\dsaa_conponents_autogen.dir\\AutogenUsed.txt"
  "dsaa\\conponents\\CMakeFiles\\dsaa_conponents_autogen.dir\\ParseCache.txt"
  "dsaa\\conponents\\dsaa_conponents_autogen"
  "dsaa\\utils\\CMakeFiles\\dsaa_utils_autogen.dir\\AutogenUsed.txt"
  "dsaa\\utils\\CMakeFiles\\dsaa_utils_autogen.dir\\ParseCache.txt"
  "dsaa\\utils\\dsaa_utils_autogen"
  "dsaa\\widgets\\CMakeFiles\\dsaa_widgets_autogen.dir\\AutogenUsed.txt"
  "dsaa\\widgets\\CMakeFiles\\dsaa_widgets_autogen.dir\\ParseCache.txt"
  "dsaa\\widgets\\dsaa_widgets_autogen"
  )
endif()
