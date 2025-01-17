# set the minimum required version of cmake needed by this CMake project.
# this command is needed to set version and policy
# settings before invoking other commands
cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set the name of the project, the version and which languages
# are needed to build this project
# this command must immediately follow the cmake_minimum_required command
project (Scrabble)

# GTK 3 dependency
find_package(PkgConfig)
pkg_check_modules(gtkmm gtkmm-3.0)

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

# Add other flags to the compiler
# ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})

# some test warning levels for GCC
set(WARNING_LEVELS_GCC
    -Werror
)
set(WARNING_LEVELS_GCC_DEBUG
    -Wfloat-equal
    -Wextra
    -Wall
    -Wundef
    -Wshadow
    -Wpointer-arith
    -Wcast-align
    -Wstrict-overflow=5
    -Wwrite-strings
    #-Waggregate-return
    -Wcast-qual
    -Wswitch-default
    -Wswitch-enum
    -Wconversion
)    

# include directory for third party libraries
include_directories(include/)

# add an executable target with one source file
add_executable(${CMAKE_PROJECT_NAME} 
    src/main.cpp
    src/menu.cpp
    src/game.cpp
    src/trie.cpp
)

# Link the target to the GTK+ libraries
TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME} ${GTKMM_LIBRARIES})
# target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE ${WARNING_LEVELS_GCC} $<$<CONFIG:DEBUG>:${WARNING_LEVELS_GCC_DEBUG}>)