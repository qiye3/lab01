# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\main_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\main_autogen.dir\\ParseCache.txt"
  "main_autogen"
  "src\\qt_interface\\CMakeFiles\\QtInterface_autogen.dir\\AutogenUsed.txt"
  "src\\qt_interface\\CMakeFiles\\QtInterface_autogen.dir\\ParseCache.txt"
  "src\\qt_interface\\QtInterface_autogen"
  "src\\task\\CMakeFiles\\Task_autogen.dir\\AutogenUsed.txt"
  "src\\task\\CMakeFiles\\Task_autogen.dir\\ParseCache.txt"
  "src\\task\\Task_autogen"
  "src\\task_manager\\CMakeFiles\\Task_Manager_autogen.dir\\AutogenUsed.txt"
  "src\\task_manager\\CMakeFiles\\Task_Manager_autogen.dir\\ParseCache.txt"
  "src\\task_manager\\Task_Manager_autogen"
  "src\\utils\\CMakeFiles\\Utils_autogen.dir\\AutogenUsed.txt"
  "src\\utils\\CMakeFiles\\Utils_autogen.dir\\ParseCache.txt"
  "src\\utils\\Utils_autogen"
  )
endif()
