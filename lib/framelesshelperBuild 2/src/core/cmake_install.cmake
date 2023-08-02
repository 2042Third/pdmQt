# Install script for directory: /Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/core

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
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelperBuild/lib64/libFramelessHelperCore.2.5.0.dylib"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelperBuild/lib64/libFramelessHelperCore.2.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libFramelessHelperCore.2.5.0.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libFramelessHelperCore.2.dylib"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      execute_process(COMMAND /Users/mikeyang/anaconda3/bin/install_name_tool
        -delete_rpath "/Users/mikeyang/Qt/6.5.1/macos/lib"
        "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelperBuild/lib64/libFramelessHelperCore.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libFramelessHelperCore.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libFramelessHelperCore.dylib")
    execute_process(COMMAND /Users/mikeyang/anaconda3/bin/install_name_tool
      -delete_rpath "/Users/mikeyang/Qt/6.5.1/macos/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libFramelessHelperCore.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libFramelessHelperCore.dylib")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/FramelessHelper/Core" TYPE FILE FILES
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelperBuild/src/core/framelesshelper.version"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/core/../../include/FramelessHelper/Core/framelesshelpercore_global.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/core/../../include/FramelessHelper/Core/framelesshelper_qt.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/core/../../include/FramelessHelper/Core/framelessmanager.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/core/../../include/FramelessHelper/Core/utils.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/core/../../include/FramelessHelper/Core/chromepalette.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/core/../../include/FramelessHelper/Core/micamaterial.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/core/../../include/FramelessHelper/Core/windowborderpainter.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/FramelessHelper/Core/private" TYPE FILE FILES
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/core/../../include/FramelessHelper/Core/private/framelessmanager_p.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/core/../../include/FramelessHelper/Core/private/framelessconfig_p.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/core/../../include/FramelessHelper/Core/private/sysapiloader_p.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/core/../../include/FramelessHelper/Core/private/chromepalette_p.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/core/../../include/FramelessHelper/Core/private/micamaterial_p.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/core/../../include/FramelessHelper/Core/private/windowborderpainter_p.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/core/../../include/FramelessHelper/Core/private/framelesshelpercore_global_p.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/core/../../include/FramelessHelper/Core/private/versionnumber_p.h"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/core/../../include/FramelessHelper/Core/private/scopeguard_p.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/FramelessHelper/Core" TYPE FILE FILES
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/core/../../include/FramelessHelper/Core/Global"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/core/../../include/FramelessHelper/Core/FramelessHelper_Qt"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/core/../../include/FramelessHelper/Core/FramelessManager"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/core/../../include/FramelessHelper/Core/Utils"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/core/../../include/FramelessHelper/Core/ChromePalette"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/core/../../include/FramelessHelper/Core/MicaMaterial"
    "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelper/src/core/../../include/FramelessHelper/Core/WindowBorderPainter"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/FramelessHelper/FramelessHelperCoreTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/FramelessHelper/FramelessHelperCoreTargets.cmake"
         "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelperBuild/src/core/CMakeFiles/Export/1cba37343162926dbce056f834de3c1c/FramelessHelperCoreTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/FramelessHelper/FramelessHelperCoreTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/cmake/FramelessHelper/FramelessHelperCoreTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/FramelessHelper" TYPE FILE FILES "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelperBuild/src/core/CMakeFiles/Export/1cba37343162926dbce056f834de3c1c/FramelessHelperCoreTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64/cmake/FramelessHelper" TYPE FILE FILES "/Users/mikeyang/Documents/pdm/pdmQt/lib/framelesshelperBuild/src/core/CMakeFiles/Export/1cba37343162926dbce056f834de3c1c/FramelessHelperCoreTargets-release.cmake")
  endif()
endif()

