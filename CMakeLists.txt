cmake_minimum_required(VERSION 3.5)

project(Tic-tac-toe VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_QT_UI OFF)

set(APP_T Tic-tac-toe)

if(BUILD_QT_UI)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
endif()



set(PROJECT_SOURCES
    main.cpp
    )
if(BUILD_QT_UI)
    set(PROJECT_SOURCES
        ${PROJECT_SOURCES}
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        )
endif()

if(BUILD_QT_UI)
    if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
        qt_add_executable(${APP_T}
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
            )
    else()
        add_executable(${APP_T}
            ${PROJECT_SOURCES}
            )
    endif()
else()
    add_executable(${APP_T}
        ${PROJECT_SOURCES}
        )
endif()


if(BUILD_QT_UI)
    target_compile_definitions(${APP_T} PUBLIC USE_UI)
    target_link_libraries(${APP_T} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

    set_target_properties(${APP_T} PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
        )
endif()

if(BUILD_QT_UI AND QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${APP_T})
endif()
