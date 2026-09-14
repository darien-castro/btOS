cmake_minimum_required(VERSION 3.5)
project(btOS)

set(CMAKE_CXX_STANDARD 17)

# Enable Qt5 automatic features
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find all required Qt modules
find_package(Qt5 COMPONENTS
        Widgets
        Gui
        Core
        Sql
        Quick
        Qml
        QuickWidgets
        REQUIRED
)

find_package(cpr REQUIRED)

# Header files
set(HEADERS
        src/core/btShell.h
        src/ui/btTopBar.h
        src/core/btState.h
        assets/QtCommon.h
        src/core/screenManager.h
        src/applications/homeScreen/homeScreen.h
        src/core/btApplication.h
        src/applications/Settings/settings.h
        src/core/btApplicationManager.h
)

# Source files
set(SOURCES
        main.cpp
        src/core/btShell.cpp
        src/ui/btTopBar.cpp
        src/core/btState.cpp
        src/core/screenManager.cpp
        src/applications/homeScreen/homeScreen.cpp
        src/core/btApplication.cpp
        src/applications/Settings/settings.cpp
        src/core/btApplicationManager.cpp
)

add_executable(btOS ${SOURCES} ${HEADERS})

target_compile_options(btOS PRIVATE -Wall -Wextra -Wpedantic)

# Link Qt and cpr
target_link_libraries(btOS
        Qt5::Widgets
        Qt5::Gui
        Qt5::Core
        Qt5::Sql
        Qt5::Quick
        Qt5::Qml
        Qt5::QuickWidgets    # <-- REQUIRED
        cpr::cpr
)
