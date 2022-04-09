set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(APP_T Tic-tac-toe-gui)
file(GLOB project_sources CONFIGURE_DEPENDS "*.h" "*.cpp" "*.ui")
source_group(src FILES ${project_sources})

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${APP_T} MANUAL_FINALIZATION ${project_sources})
else()
    add_executable(${APP_T} ${project_sources})
endif()

target_link_libraries(${APP_T}
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        Tic-tac-toe-core
)

set_target_properties(${APP_T} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    )

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${APP_T})
endif()
