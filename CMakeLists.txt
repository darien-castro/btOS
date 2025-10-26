cmake_minimum_required(VERSION 3.5)
project(btOS)

set(CMAKE_CXX_STANDARD 11)

# Enable Qt5 features
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Your source files
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
)



add_executable(btOS ${SOURCES} ${HEADERS} ${UIS})
target_link_libraries(btOS Qt5::Widgets)
