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
        resources/QtCommon.h
        src/core/screenManager.h
        src/applications/homeScreen/homeScreen.h
        src/applications/Notes/notesScreen.h
        src/applications/appViewer/appViewer.h
        src/core/btApplication.h
        src/applications/phone/phoneScreen.h
        src/applications/toDoApp.h
        src/applications/messaging.h
        src/applications/Settings/settings.h
        src/applications/calculatorScreen.h
        src/applications/Weather/weatherScreen.h
        resources/models/notesApp/noteCard.h
        resources/models/notesApp/noteTag.h
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
        src/applications/Notes/notesScreen.cpp
        src/applications/appViewer/appViewer.cpp
        src/core/btApplication.cpp
        src/applications/phone/phoneScreen.cpp
        src/applications/toDoApp.cpp
        src/applications/messaging.cpp
        src/applications/Settings/settings.cpp
        src/applications/calculatorScreen.cpp
        src/applications/Weather/weatherScreen.cpp
        resources/models/notesApp/noteCard.cpp
        resources/models/notesApp/noteTag.cpp
        src/core/btApplicationManager.cpp
        src/applications/Notes/windows/note_edit_view.cpp
        src/applications/Notes/windows/note_edit_view.h
        resources/models/notesApp/NoteStruct.h
        resources/models/weatherApp/weatherWebApp.cpp
        resources/models/weatherApp/weatherWebApp.h
        resources/models/weatherApp/qmlFiles/weatherObj.cpp
        resources/models/weatherApp/qmlFiles/weatherObj.h
        resources/models/weatherApp/FutureData.h
)

add_executable(btOS ${SOURCES} ${HEADERS})

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
