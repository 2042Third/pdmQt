# Install script for directory: /Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/widgets

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelperBuild/lib64/libFramelessHelperWidgets.2.5.0.dylib"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelperBuild/lib64/libFramelessHelperWidgets.2.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libFramelessHelperWidgets.2.5.0.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libFramelessHelperWidgets.2.dylib"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      execute_process(COMMAND /Users/mikeyang/anaconda3/bin/install_name_tool
        -delete_rpath "/Users/mikeyang/Qt/6.5.1/macos/lib"
        -delete_rpath "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelperBuild/lib64"
        "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelperBuild/lib64/libFramelessHelperWidgets.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libFramelessHelperWidgets.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libFramelessHelperWidgets.dylib")
    execute_process(COMMAND /Users/mikeyang/anaconda3/bin/install_name_tool
      -delete_rpath "/Users/mikeyang/Qt/6.5.1/macos/lib"
      -delete_rpath "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelperBuild/lib64"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libFramelessHelperWidgets.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libFramelessHelperWidgets.dylib")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/FramelessHelper/Widgets" TYPE FILE FILES
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/widgets/../../include/FramelessHelper/Widgets/framelesshelperwidgets_global.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/widgets/../../include/FramelessHelper/Widgets/framelesswidget.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/widgets/../../include/FramelessHelper/Widgets/framelessmainwindow.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/widgets/../../include/FramelessHelper/Widgets/standardsystembutton.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/widgets/../../include/FramelessHelper/Widgets/framelesswidgetshelper.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/widgets/../../include/FramelessHelper/Widgets/standardtitlebar.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/widgets/../../include/FramelessHelper/Widgets/framelessdialog.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/FramelessHelper/Widgets/private" TYPE FILE FILES
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/widgets/../../include/FramelessHelper/Widgets/private/framelesswidgetshelper_p.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/widgets/../../include/FramelessHelper/Widgets/private/standardsystembutton_p.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/widgets/../../include/FramelessHelper/Widgets/private/standardtitlebar_p.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/widgets/../../include/FramelessHelper/Widgets/private/framelesswidget_p.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/widgets/../../include/FramelessHelper/Widgets/private/framelessmainwindow_p.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/widgets/../../include/FramelessHelper/Widgets/private/widgetssharedhelper_p.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/widgets/../../include/FramelessHelper/Widgets/private/framelessdialog_p.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/FramelessHelper/Widgets" TYPE FILE FILES
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/widgets/../../include/FramelessHelper/Widgets/Global"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/widgets/../../include/FramelessHelper/Widgets/FramelessWidget"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/widgets/../../include/FramelessHelper/Widgets/FramelessMainWindow"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/widgets/../../include/FramelessHelper/Widgets/StandardSystemButton"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/widgets/../../include/FramelessHelper/Widgets/FramelessWidgetsHelper"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/widgets/../../include/FramelessHelper/Widgets/StandardTitleBar"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/widgets/../../include/FramelessHelper/Widgets/FramelessDialog"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/FramelessHelper/FramelessHelperWidgetsTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/FramelessHelper/FramelessHelperWidgetsTargets.cmake"
         "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelperBuild/src/widgets/CMakeFiles/Export/1cba37343162926dbce056f834de3c1c/FramelessHelperWidgetsTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/FramelessHelper/FramelessHelperWidgetsTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/FramelessHelper/FramelessHelperWidgetsTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/FramelessHelper" TYPE FILE FILES "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelperBuild/src/widgets/CMakeFiles/Export/1cba37343162926dbce056f834de3c1c/FramelessHelperWidgetsTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/FramelessHelper" TYPE FILE FILES "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelperBuild/src/widgets/CMakeFiles/Export/1cba37343162926dbce056f834de3c1c/FramelessHelperWidgetsTargets-release.cmake")
  endif()
endif()

