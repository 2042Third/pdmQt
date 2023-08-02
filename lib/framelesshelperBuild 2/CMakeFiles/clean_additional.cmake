# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "src/core/CMakeFiles/FramelessHelperCore_autogen.dir/AutogenUsed.txt"
  "src/core/CMakeFiles/FramelessHelperCore_autogen.dir/ParseCache.txt"
  "src/core/FramelessHelperCore_autogen"
  "src/quick/CMakeFiles/FramelessHelperQuick_autogen.dir/AutogenUsed.txt"
  "src/quick/CMakeFiles/FramelessHelperQuick_autogen.dir/ParseCache.txt"
  "src/quick/CMakeFiles/FramelessHelperQuickplugin_autogen.dir/AutogenUsed.txt"
  "src/quick/CMakeFiles/FramelessHelperQuickplugin_autogen.dir/ParseCache.txt"
  "src/quick/FramelessHelperQuick_autogen"
  "src/quick/FramelessHelperQuickplugin_autogen"
  "src/widgets/CMakeFiles/FramelessHelperWidgets_autogen.dir/AutogenUsed.txt"
  "src/widgets/CMakeFiles/FramelessHelperWidgets_autogen.dir/ParseCache.txt"
  "src/widgets/FramelessHelperWidgets_autogen"
  )
endif()
