# CMakeLists.txt for your C library – works with GCC and Clang
cmake_minimum_required(VERSION 3.10)
project(ctuix VERSION 1.0.0 LANGUAGES C)

# Set C standard (adjust to your needs: 99, 11, 17, etc.)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Common warning flags for both GCC and Clang
add_compile_options(-Wall -Wextra)

# Dependencies
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBXML2 REQUIRED libxml-2.0)
pkg_check_modules(NCURSES REQUIRED ncurses)

# Source files
set(CTUIX_SOURCES
    src/ctuix_core.c
    src/ctuix_draw.c
    src/ctuix_error.c
    src/ctuix_key.c
    src/ctuix_nav.c
    src/ctuix_parse.c
    src/ctuix_tree.c
    src/ctuix_utils.c
)

# Create static library
add_library(ctuix STATIC ${CTUIX_SOURCES})

# Include paths (PUBLIC for users of the library)
target_include_directories(ctuix PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Private includes for the library itself (including dependencies)
target_include_directories(ctuix PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${LIBXML2_INCLUDE_DIRS}
    ${NCURSES_INCLUDE_DIRS}
)

# Link dependencies
target_link_libraries(ctuix PUBLIC
    ${LIBXML2_LIBRARIES}
    ${NCURSES_LIBRARIES}
)

# Add demo executable (built by default)
add_executable(ctuix_demo demo/ctuix_demo.c)
target_link_libraries(ctuix_demo PRIVATE ctuix)

# The demo needs the library’s public headers
target_include_directories(ctuix_demo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Install the static library
install(TARGETS ctuix
    ARCHIVE DESTINATION lib
)

# Install headers
install(DIRECTORY include/ DESTINATION include/ctuix)