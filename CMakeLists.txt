# CMakeLists.txt for your C library
cmake_minimum_required(VERSION 3.10)
project(ctuix VERSION 1.0.0 LANGUAGES C)

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

# Create library
add_library(ctuix STATIC ${CTUIX_SOURCES})

# Include paths (PUBLIC = users also need these)
target_include_directories(ctuix PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Private includes for your code only
target_include_directories(ctuix PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link dependencies
target_link_libraries(ctuix PUBLIC ${LIBXML2_LIBRARIES} ${NCURSES_LIBRARIES})

# Remove installed files
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
    COMMENT "Remove entire build directory"
)

# Add executable from demo folder
add_executable(ctuix_demo EXCLUDE_FROM_ALL demo/ctuix_demo.c)
target_link_libraries(ctuix_demo PRIVATE ctuix)

# Build-only target
add_custom_target(demo
    DEPENDS ctuix_demo
    COMMENT "Build the demo program from demo/ folder"
)

# Install the static library
install(TARGETS ctuix
    ARCHIVE DESTINATION lib
)

# Install headers manually (alternative to PUBLIC_HEADER above)
install(DIRECTORY include/ DESTINATION include/ctuix)