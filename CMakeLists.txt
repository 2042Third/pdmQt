cmake_minimum_required(VERSION 3.5)

project(pdm_qt VERSION 0.1 LANGUAGES C CXX)

option(PDM_USE_FRAMELESSHELPER "Using the framelesshelper library in PDM." ON)

cmake_policy(SET CMP0079 NEW) # allow things from other directories
#cmake_policy(SET CMP0135 NEW) # cryptoSqlite icu download prebuilt binary

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DVK_PROTOTYPES")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_PROTOTYPES")

set(PDM_QT_OPTIONS ${PDM_QT_OPTIONS} "PDM_DESKTOP_APPLICATION=1")

if(APPLE)
#    set(CMAKE_OSX_SYSROOT /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk)
    set(CMAKE_PREFIX_PATH "/Users/mikeyang/Qt/6.6.1/macos/lib/cmake")
    set(OPENSSL_ROOT_DIR /opt/homebrew/opt/openssl@3)
    set(FramelessHelper_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/framelesshelperBuild/lib64/cmake/FramelessHelper)
elseif (WIN32)
    set(CMAKE_PREFIX_PATH "C:\\Qt\\6.6.1\\mingw_64\\lib\\cmake")
    set(FramelessHelper_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/framelesshelperBuild/lib/cmake/FramelessHelper)
#    set(FramelessHelper_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/framelesshelperBuild/bin)

endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS
    Widgets
    LinguistTools
    Svg
)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
    Widgets
    LinguistTools
    Svg
)

# Find FramelessHelper:
if(APPLE)
    find_package(FramelessHelper REQUIRED COMPONENTS Core Widgets)
endif()

# check if we are on windows
if(WIN32)
    find_library(FRAMELESS_HELPER_CORE_LIB
        NAMES FramelessHelperCore
        PATHS "C:/Users/18604/Documents/pdm_qt/lib/framelesshelperBuild/lib")

    find_library(FRAMELESS_HELPER_QUICK_LIB
        NAMES FramelessHelperQuick
        PATHS "C:/Users/18604/Documents/pdm_qt/lib/framelesshelperBuild/lib")

    find_library(FRAMELESS_HELPER_WIDGETS_LIB
        NAMES FramelessHelperWidgets
        PATHS "C:/Users/18604/Documents/pdm_qt/lib/framelesshelperBuild/lib")

    find_library(SSL_LIB ssl # Openssl
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/pdm_network/lib/)

    find_library(CRYPTO_LIB crypto # Openssl
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/pdm_network/lib/)

elseif(APPLE)

    find_library(SSL_LIB ssl )

    find_library(CRYPTO_LIB crypto )
endif()

# Translation files, currently disabled.
set(TS_FILES
#    pdm_qt_zh_CN.ts
    )

set(PROJECT_SOURCES
    resources.qrc
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/mainwindow.ui
    src/settings/settingsmainwindow.h src/settings/settingsmainwindow.cpp src/settings/settingsmainwindow.ui
    src/settings/accountwidget.h src/settings/accountwidget.cpp src/settings/accountwidget.ui
    src/settings/informationwidget.h src/settings/informationwidget.cpp src/settings/informationwidget.ui
    src/settings/loginwidget.h src/settings/loginwidget.cpp
    src/others/debugwindow.h src/others/debugwindow.cpp src/others/debugwindow.ui
    src/PdmRunTime.h src/PdmRunTime.cpp
        ${TS_FILES}
    src/PdmRunTimeRef.cpp src/PdmRunTimeRef.h
    src/settings/userinformation.h src/settings/userinformation.cpp src/settings/userinformation.ui

    # PDM things
    src/handler/db/pdm_databse.cpp
    src/handler/db/pdm_database.h
    src/handler/pdm_status.h
    src/handler/pdm_net.cpp
    src/handler/pdm_net.h
    src/handler/pdm_net_type.cpp
    src/handler/net_convert.cpp
    src/handler/types.h
    src/crypto/pdmCryptoDB.hpp # encrypted database

    src/others/CustomTitleBar.h src/others/CustomTitleBar.cpp src/others/shadowFrameWidget.h
    src/others/shadowFrameWidget.cpp src/handler/pdm_qt_helpers.h src/handler/pdm_qt_helpers.cpp
    src/handler/pdm_settings.h src/handler/pdm_settings.cpp src/handler/dao/pdmLocalDao.h
    src/handler/dao/pdmLocalDao.cpp src/handler/db/PdmDBType.h src/handler/pdmqt/pdm_qt_net.h
    src/handler/pdmqt/pdm_qt_net.cpp src/notesView/NotesScroll.h src/notesView/NotesScroll.cpp
    src/notesView/Note.h src/notesView/pdmListView.h src/notesView/pdmListView.cpp src/handler/dao/pdmNotesCache.h
    src/handler/dao/pdmNotesCache.cpp src/notesView/NoteEdit.cpp src/notesView/NoteEdit.h src/helpers/PdmUpdateTimer.h
    src/helpers/PdmUpdateTimer.cpp src/settings/settingsmenuWidget.h src/settings/settingsmenuWidget.cpp
    src/notesView/NotesScrollDelegate.h src/others/PasswordDialog.h
    src/others/MacCustomWindow.h
    src/others/macOSWindowBridge.h
    src/helpers/FlashingCircle.h
    src/helpers/Animated.h
    src/others/tools/pdmQtWidgets.h
    src/others/tools/pdmQtHelpers.cpp
    src/others/tools/pdmQtHelpers.h
    src/helpers/FlashingCircle.cpp
    src/others/tools/pdmExtraQtWidgets.h
    src/handler/pdm_status_qt.cpp
    src/handler/pdm_status_qt.h
    src/mainwindowui.h
    src/others/tools/pdmQtWidgets.cpp
    src/handler/pdm_commands.cpp
    src/handler/pdm_commands.h
    src/handler/pdm_command.cpp
    src/handler/pdm_command.h
    src/others/debugwindowCommandWidget.cpp
    src/others/debugwindowCommandWidget.h
    src/notesView/pdmListViewSortFilterProxyModel.cpp
    src/notesView/pdmListViewSortFilterProxyModel.h
    src/notesView/pdmListSortingMenu.cpp
    src/notesView/pdmListSortingMenu.h
)

# Compile the macOS Objective-C bridge only on macOS
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    list(APPEND PROJECT_SOURCES src/others/macOSWindowBridge.mm)
endif()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(pdm_qt
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

    )

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(pdm_qt SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(pdm_qt
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_include_directories(pdm_qt PUBLIC
    ./
    src/ # For the "crypto/pdmCryptoDB.hpp" include only
    lib/
    lib/json/single_include
    lib/pdm-crypt-module
    lib/pdm-crypt-module/src/lib
    lib/cryptoSQLite
    lib/pdm_network

)

if(APPLE)
    target_include_directories(pdm_qt PUBLIC
        lib/framelesshelperBuild/include
        lib/framelesshelperBuild/lib
        lib/framelesshelperBuild/bin
    )
elseif(WIN32)
    target_include_directories(pdm_qt PUBLIC
        lib/framelesshelperBuild/include
        lib/framelesshelperBuild/lib
    )
    set(PDM_QT_OPTIONS ${PDM_QT_OPTIONS} "USING_MACOS_FRAMELESS_HELPER=0")
endif()

if(PDM_USE_FRAMELESSHELPER)
    set(PDM_QT_OPTIONS ${PDM_QT_OPTIONS} "PDM_USE_FRAMELESSHELPER=1")
endif()

set(PDM_TEST_PLATFORM_DESKTOP 1)

add_subdirectory(lib/pdm-crypt-module) # pdm encryption
add_subdirectory(lib/pdm_network) # pdm network connectivity
add_subdirectory(lib/cryptoSQLite) # encrypted database

install(FILES PDM_CURL_LOCATION DESTINATION ${PROJECT_BINARY_DIR} )
target_compile_definitions(pdm_qt PRIVATE ${PDM_QT_OPTIONS})

target_link_libraries(pdm_qt PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt6::Svg
    cc20 # pdm encryption
    pdm-network # pdm network connectivity
    cryptosqlite # encrypted database interface

)

if(APPLE)
    target_link_libraries(pdm_qt PUBLIC
        FramelessHelper::Core
        FramelessHelper::Widgets
    )
elseif(WIN32)
    target_link_libraries(pdm_qt PUBLIC
        ${FRAMELESS_HELPER_CORE_LIB}
        ${FRAMELESS_HELPER_QUICK_LIB}
        ${FRAMELESS_HELPER_WIDGETS_LIB}
    )

endif()

set_target_properties(pdm_qt PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER pdm.notes.pw
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS pdm_qt
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(pdm_qt)
endif()
