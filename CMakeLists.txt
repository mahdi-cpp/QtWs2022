cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 11)

# QC Custom config
set(QC_PROJECT_NAME "QtWs2022")
set(QC_PROJECT_VERSION 0.1)


# Project declare
project(${QC_PROJECT_NAME} VERSION ${QC_PROJECT_VERSION} LANGUAGES CXX)
message(STATUS "[${PROJECT_NAME}] Project ${PROJECT_NAME} ${PROJECT_VERSION}")

# CMake set
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler set
message(STATUS "[${PROJECT_NAME}] C++ compiler ID is: ${CMAKE_CXX_COMPILER_ID}")

message(STATUS "[${PROJECT_NAME}] Set warnings as error")
# lots of warnings and all warnings as errors
add_compile_options(-Wall -Wextra -pedantic -Werror)

# disable some warning
add_compile_options(-Wno-nested-anon-types -Wno-c++17-extensions -Wno-overloaded-virtual)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Network Multimedia WebSockets Quick Qml REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Network Multimedia WebSockets Quick Qml REQUIRED)

find_package(QT NAMES Qt6 Qt5 COMPONENTS X11Extras REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS X11Extras REQUIRED)


message(STATUS "[${PROJECT_NAME}] Qt version is: ${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}")


# main
set(QC_MAIN_SOURCES main.cpp)

# source
set(QC_SCENE_SOURCES
        scene/Scene.h
        scene/Scene.cpp
        scene/SceneRenderer.h
        scene/SceneRenderer.cpp
        scene/SceneProvider.h
        scene/SceneProvider.cpp
        scene/SceneProviderRenderer.h
        scene/SceneProviderRenderer.cpp
        )

set(QC_SERVICE_SOURCES
        service/ServiceManager.h
        service/ServiceManager.cpp
        service/ResourceService.h
        service/ResourceService.cpp
        )

# all sources
set(QC_PROJECT_SOURCES
        ${QC_MAIN_SOURCES}
        ${QC_SERVICE_SOURCES}
        ${QC_SCENE_SOURCES})

add_executable(${PROJECT_NAME} ${QC_RUNTIME_TYPE} ${QC_PROJECT_SOURCES})

# Qt
target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Network
        Qt${QT_VERSION_MAJOR}::Multimedia
        Qt${QT_VERSION_MAJOR}::Quick
        Qt${QT_VERSION_MAJOR}::Qml
        )

find_package(Threads REQUIRED)



set(LIBS ${LIBS})


target_link_libraries(${PROJECT_NAME} PRIVATE
        ${LIBS}
        Qt${QT_VERSION_MAJOR}::X11Extras
        # xcb https://doc.qt.io/qt-5/linux-requirements.html
        xcb
        # pthread
        Threads::Threads
        )
