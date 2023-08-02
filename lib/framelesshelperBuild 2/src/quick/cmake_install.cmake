# Install script for directory: /Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/quick

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelperBuild")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/qml/org/wangwenx190/FramelessHelper" TYPE MODULE FILES "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelperBuild/imports/org/wangwenx190/FramelessHelper/libFramelessHelperQuickplugin.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/qml/org/wangwenx190/FramelessHelper/libFramelessHelperQuickplugin.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/qml/org/wangwenx190/FramelessHelper/libFramelessHelperQuickplugin.dylib")
    execute_process(COMMAND /Users/mikeyang/anaconda3/bin/install_name_tool
      -delete_rpath "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelperBuild/lib64"
      -delete_rpath "/Users/mikeyang/Qt/6.5.1/macos/lib"
      -add_rpath "@loader_path/../Frameworks"
      -add_rpath "@loader_path/../../../../lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/qml/org/wangwenx190/FramelessHelper/libFramelessHelperQuickplugin.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/qml/org/wangwenx190/FramelessHelper/libFramelessHelperQuickplugin.dylib")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/qml/org/wangwenx190/FramelessHelper" TYPE FILE FILES "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelperBuild/imports/org/wangwenx190/FramelessHelper/qmldir")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/qml/org/wangwenx190/FramelessHelper" TYPE FILE FILES "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelperBuild/imports/org/wangwenx190/FramelessHelper/plugins.qmltypes")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelperBuild/lib64/libFramelessHelperQuick.2.5.0.dylib"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelperBuild/lib64/libFramelessHelperQuick.2.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libFramelessHelperQuick.2.5.0.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libFramelessHelperQuick.2.dylib"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      execute_process(COMMAND /Users/mikeyang/anaconda3/bin/install_name_tool
        -delete_rpath "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelperBuild/lib64"
        -delete_rpath "/Users/mikeyang/Qt/6.5.1/macos/lib"
        "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelperBuild/lib64/libFramelessHelperQuick.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libFramelessHelperQuick.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libFramelessHelperQuick.dylib")
    execute_process(COMMAND /Users/mikeyang/anaconda3/bin/install_name_tool
      -delete_rpath "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelperBuild/lib64"
      -delete_rpath "/Users/mikeyang/Qt/6.5.1/macos/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libFramelessHelperQuick.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libFramelessHelperQuick.dylib")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/FramelessHelper/Quick" TYPE FILE FILES
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/quick/../../include/FramelessHelper/Quick/framelesshelperquick_global.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/quick/../../include/FramelessHelper/Quick/framelessquickmodule.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/quick/../../include/FramelessHelper/Quick/framelessquickhelper.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/quick/../../include/FramelessHelper/Quick/framelessquickutils.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/quick/../../include/FramelessHelper/Quick/quickchromepalette.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/quick/../../include/FramelessHelper/Quick/quickmicamaterial.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/quick/../../include/FramelessHelper/Quick/quickimageitem.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/quick/../../include/FramelessHelper/Quick/quickwindowborder.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/FramelessHelper/Quick/private" TYPE FILE FILES
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/quick/../../include/FramelessHelper/Quick/private/quickstandardsystembutton_p.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/quick/../../include/FramelessHelper/Quick/private/quickstandardtitlebar_p.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/quick/../../include/FramelessHelper/Quick/private/framelessquickhelper_p.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/quick/../../include/FramelessHelper/Quick/private/framelessquickwindow_p.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/quick/../../include/FramelessHelper/Quick/private/framelessquickwindow_p_p.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/quick/../../include/FramelessHelper/Quick/private/framelessquickapplicationwindow_p.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/quick/../../include/FramelessHelper/Quick/private/framelessquickapplicationwindow_p_p.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/quick/../../include/FramelessHelper/Quick/private/quickmicamaterial_p.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/quick/../../include/FramelessHelper/Quick/private/quickimageitem_p.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/quick/../../include/FramelessHelper/Quick/private/quickwindowborder_p.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/FramelessHelper/Quick" TYPE FILE FILES
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/quick/../../include/FramelessHelper/Quick/Global"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/quick/../../include/FramelessHelper/Quick/FramelessQuickModule"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/quick/../../include/FramelessHelper/Quick/FramelessQuickHelper"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/quick/../../include/FramelessHelper/Quick/FramelessQuickUtils"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/quick/../../include/FramelessHelper/Quick/QuickChromePalette"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/quick/../../include/FramelessHelper/Quick/QuickMicaMaterial"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/quick/../../include/FramelessHelper/Quick/QuickImageItem"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/quick/../../include/FramelessHelper/Quick/QuickWindowBorder"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/FramelessHelper/FramelessHelperQuickTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/FramelessHelper/FramelessHelperQuickTargets.cmake"
         "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelperBuild/src/quick/CMakeFiles/Export/1cba37343162926dbce056f834de3c1c/FramelessHelperQuickTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/FramelessHelper/FramelessHelperQuickTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/FramelessHelper/FramelessHelperQuickTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/FramelessHelper" TYPE FILE FILES "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelperBuild/src/quick/CMakeFiles/Export/1cba37343162926dbce056f834de3c1c/FramelessHelperQuickTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/FramelessHelper" TYPE FILE FILES "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelperBuild/src/quick/CMakeFiles/Export/1cba37343162926dbce056f834de3c1c/FramelessHelperQuickTargets-release.cmake")
  endif()
endif()

