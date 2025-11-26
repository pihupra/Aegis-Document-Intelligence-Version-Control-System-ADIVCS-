cmake_minimum_required(VERSION 3.10)
project(AegisQtGUI)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_executable(aegis_gui
    main_qt.cpp
    mainwindow.cpp
    ../src/storage.cpp
    ../src/versioning.cpp
    ../src/diff_myers.cpp
)

target_link_libraries(aegis_gui PRIVATE Qt5::Widgets sqlite3)
set_target_properties(aegis_gui PROPERTIES AUTOMOC ON AUTOUIC ON)
