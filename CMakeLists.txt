cmake_minimum_required(VERSION 3.15)
project(cchess C)

# Set source and test directories
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(TEST_DIR "${CMAKE_SOURCE_DIR}/tests")

include_directories(SRC_DIR)

# Collect all source files
file(GLOB SRC_FILES "${SRC_DIR}/*.c")
file(GLOB TEST_FILES "${TEST_DIR}/*.c")

# Separate main.c from other sources
set(MAIN_FILE "${SRC_DIR}/main.c")
list(REMOVE_ITEM SRC_FILES ${MAIN_FILE})

# Add executable for main application
add_executable(app ${MAIN_FILE} ${SRC_FILES})

# Add executable for tests
add_executable(test_app ${SRC_FILES} ${TEST_FILES})
target_include_directories(test_app PRIVATE src tests)

