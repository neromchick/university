# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\MillionaireGame_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\MillionaireGame_autogen.dir\\ParseCache.txt"
  "MillionaireGame_autogen"
  )
endif()
