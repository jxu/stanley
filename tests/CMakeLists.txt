# Collect all test source files in this directory
file(GLOB TEST_SOURCES *.cpp)

# Create the test executable with doctest main
add_executable(chess_tests ${TEST_SOURCES})

# Link against my library
target_link_libraries(chess_tests PRIVATE chesslib)

# Debug options
target_compile_options(chess_tests PRIVATE
        $<$<CONFIG:Debug>:-D_GLIBCXX_DEBUG>
)

target_link_options(chess_tests PRIVATE
        $<$<CONFIG:Debug>:-D_GLIBCXX_DEBUG>
)

# Register with CTest
add_test(NAME chess_unit_tests COMMAND chess_tests)