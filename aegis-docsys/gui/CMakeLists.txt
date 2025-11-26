cmake_minimum_required(VERSION 3.16)
project(aegis-docsys LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Wpedantic)


# find sqlite3
find_package(SQLite3 REQUIRED)


add_executable(aegis-cli
src/main.cpp
src/cli.cpp
src/storage.cpp
src/versioning.cpp
src/diff_myers.cpp
)


target_include_directories(aegis-cli PRIVATE src)


target_link_libraries(aegis-cli PRIVATE SQLite::SQLite3)


# Tests
enable_testing()
add_executable(tests tests/test_versioning.cpp src/versioning.cpp src/diff_myers.cpp src/storage.cpp)
add_test(NAME versioning_tests COMMAND tests)


# Qt GUI
add_subdirectory(gui)