cmake_minimum_required(VERSION 3.15)
project(cchess C)

# Export compiler commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set source and test directories
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(TEST_DIR "${CMAKE_SOURCE_DIR}/tests")

# Include Unity
add_library(unity "${TEST_DIR}/unity/unity.c")
target_include_directories(unity PUBLIC tests/unity)

include_directories(SRC_DIR)

# Collect all source files
file(GLOB SRC_FILES "${SRC_DIR}/*.c")
file(GLOB TEST_FILES "${TEST_DIR}/*.c")

# Separate main.c from other sources
set(MAIN_FILE "${SRC_DIR}/main.c")
list(REMOVE_ITEM SRC_FILES ${MAIN_FILE})

# Add executable for main application
add_executable(app ${MAIN_FILE} ${SRC_FILES})
target_compile_options(app PRIVATE -O3 -Wall -Wextra)

# Add executable for tests
add_executable(test_app ${SRC_FILES} ${TEST_FILES})
target_include_directories(test_app PRIVATE src tests)
target_link_libraries(test_app PRIVATE unity)
target_compile_options(test_app PRIVATE -Og -g -Wall -Wextra)


