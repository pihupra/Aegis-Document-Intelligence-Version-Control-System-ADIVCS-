cmake_minimum_required(VERSION 3.10)
project(AegisDocSystem)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(aegis_cli
    src/main.cpp
    src/cli.cpp
    src/storage.cpp
    src/versioning.cpp
    src/diff_myers.cpp
)

add_executable(aegis_gui
    gui/main.cpp
    gui/mainwindow.cpp
    src/storage.cpp
    src/versioning.cpp
    src/diff_myers.cpp
)

target_link_libraries(aegis_gui PRIVATE Qt6::Widgets sqlite3)
target_link_libraries(aegis_cli PRIVATE sqlite3)
