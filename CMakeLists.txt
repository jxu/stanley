cmake_minimum_required(VERSION 3.15)
project(cppchess CXX)

set(CMAKE_CXX_STANDARD 17)

# Define main chess functionality as library
add_library(chesslib
        src/board.cpp
        src/move.cpp
        src/movegen.cpp
)

# Include header files
target_include_directories(chesslib PUBLIC src)

# Different builds: Release and Debug
# Debug uses _GLIBCXX_DEBUG which changes all standard class templates
# https://gcc.gnu.org/onlinedocs/libstdc++/manual/debug_mode_using.html
# Debug mode must be applied for all compilation and linking
target_compile_options(chesslib PRIVATE
        $<$<CONFIG:Release>:-O3>
        $<$<CONFIG:Debug>:-Og -g -D_GLIBCXX_DEBUG>
)

target_link_options(chesslib PRIVATE
        $<$<CONFIG:Debug>:-D_GLIBCXX_DEBUG>
)

# Main executable: links in my library
add_executable(chess app/main.cpp)
target_link_libraries(chess PRIVATE chesslib)

# Enable CTest (see tests/CMakeLists.txt)
enable_testing()
add_subdirectory(tests)
