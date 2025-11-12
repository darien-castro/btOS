cmake_minimum_required(VERSION 3.5)
project(btOS)

set(CMAKE_CXX_STANDARD 17)

# Enable Qt5 automatic features
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find all required Qt modules
find_package(Qt5 COMPONENTS Widgets Sql REQUIRED)
find_package(cpr REQUIRED)

# Source files
set(SOURCES
        main.cpp
        src/core/btShell.cpp
        src/core/btShell.h
        src/ui/btTopBar.cpp
        src/ui/btTopBar.h
        src/core/btState.cpp
        src/core/btState.h
        resources/QtCommon.h
        src/core/screenManager.cpp
        src/core/screenManager.h
        src/applications/homeScreen.cpp
        src/applications/homeScreen.h
        src/applications/notesScreen.cpp
        src/applications/notesScreen.h
        src/applications/appViewer.cpp
        src/applications/appViewer.h
        src/core/btApplication.cpp
        src/core/btApplication.h
        src/applications/phoneScreen.cpp
        src/applications/phoneScreen.h
        src/applications/toDoApp.cpp
        src/applications/toDoApp.h
        src/applications/messaging.cpp
        src/applications/messaging.h
        src/applications/settings.cpp
        src/applications/settings.h
        src/applications/calculatorScreen.cpp
        src/applications/calculatorScreen.h
        src/applications/weatherScreen.cpp
        src/applications/weatherScreen.h
)

add_executable(btOS ${SOURCES})

# Link Qt and cpr
target_link_libraries(btOS
        PRIVATE
        Qt5::Widgets
        Qt5::Sql
        cpr::cpr
)
