cmake_minimum_required(VERSION 3.5)

project(Tic-tac-toe VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_QT_GUI OFF)

set(APP_T Tic-tac-toe)

if(BUILD_QT_GUI)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
endif()



file(GLOB files_in_directory CONFIGURE_DEPENDS "src/core/*")
set(PROJECT_SOURCES
    ${files_in_directory}
    )
if(BUILD_QT_GUI)
    file(GLOB files_in_directory CONFIGURE_DEPENDS "src/gui/*")
    set(PROJECT_SOURCES
        ${PROJECT_SOURCES}
        ${files_in_directory}
        )
endif()

if(BUILD_QT_GUI)
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


if(BUILD_QT_GUI)
    target_compile_definitions(${APP_T} PUBLIC USE_GUI)
    target_link_libraries(${APP_T} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
    target_include_directories(${APP_T} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

    set_target_properties(${APP_T} PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
        )
endif()

if(BUILD_QT_GUI AND QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${APP_T})
endif()
