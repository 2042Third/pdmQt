cmake_minimum_required(VERSION 3.5)

project(pdm_qt VERSION 0.1 LANGUAGES C CXX)

cmake_policy(SET CMP0079 NEW) # allow things from other directories
#cmake_policy(SET CMP0135 NEW) # cryptoSqlite icu download prebuilt binary

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DVK_PROTOTYPES")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_PROTOTYPES")
#set(CMAKE_PREFIX_PATH "C:\\Qt\\6.4.2\\mingw_64\\lib\\cmake")

if(APPLE)
    set(CMAKE_PREFIX_PATH "/Users/mikeyang/Qt/6.4.2/macos/lib/cmake")
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS
    Widgets
    LinguistTools
#    svg
)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
    Widgets
    LinguistTools
#    svg
)

#find_library(SECUREMEM_LIB SecureMemory # PDM cryptoSQLite
#    ${CMAKE_CURRENT_SOURCE_DIR}/lib/cryptoSQLite/external/securememorybin/bin)

find_library(SSL_LIB ssl # Openssl
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/pdm_network/lib/)

find_library(CRYPTO_LIB crypto # Openssl
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/pdm_network/lib/)



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
    src/PdmRuntimeRef.cpp src/PdmRunTimeRef.h
    src/settings/userinformation.h src/settings/userinformation.cpp src/settings/userinformation.ui

    # PDM things
    src/handler/pdm_databse.cpp
    src/handler/pdm_database.h
    src/handler/pdm_status.h
    src/handler/pdm_net.cpp
    src/handler/pdm_net.h
    src/handler/pdm_net_type.cpp
    src/handler/net_convert.cpp
    src/handler/types.h
    src/crypto/pdmCryptoDB.hpp # encrypted database

    src/CustomWindow.h src/CustomWindow.cpp src/others/shadowFrameWidget.h src/others/shadowFrameWidget.cpp src/handler/pdm_qt_helpers.h src/handler/pdm_qt_helpers.cpp src/handler/pdm_settings.h src/handler/pdm_settings.cpp)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(pdm_qt
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET pdm_qt APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(pdm_qt SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
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

add_subdirectory(lib/pdm-crypt-module) # pdm encryption
add_subdirectory(lib/pdm_network) # pdm network connectivity
add_subdirectory(lib/cryptoSQLite) # encrypted database

install(FILES PDM_CURL_LOCATION DESTINATION ${PROJECT_BINARY_DIR} )
target_link_libraries(pdm_qt PUBLIC
    Qt${QT_VERSION_MAJOR}::Widgets
#    ${SSL_LIB}
#    ${CRYPTO_LIB}
    cc20 # pdm encryption
    pdm-network # pdm network connectivity
    cryptosqlite # encrypted database interface
    )

set_target_properties(pdm_qt PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
#add_custom_command(TARGET pdm_qt POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt${QT_VERSION_MAJOR}::Core> $<TARGET_FILE_DIR:pdm_qt>
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt${QT_VERSION_MAJOR}::Gui> $<TARGET_FILE_DIR:pdm_qt>
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt${QT_VERSION_MAJOR}::Widgets> $<TARGET_FILE_DIR:pdm_qt>
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt6::Svg> $<TARGET_FILE_DIR:pdm_qt>
#    )

install(TARGETS pdm_qt
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(pdm_qt)
endif()
