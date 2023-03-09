# From: https://cliutils.gitlab.io/modern-cmake/chapters/basics.html

## Vesion and policy setup
# Debian stable 2023
cmake_minimum_required(VERSION 3.18)

if(${CMAKE_VERSION} VERSION_LESS 3.25)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.25)
endif()

## Project setup
project(TestRooFit
  LANGUAGES CXX
)
set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INC "${CMAKE_CURRENT_SOURCE_DIR}/include")

## find and link dependancies
find_package(ROOT 6.20 CONFIG REQUIRED)
# If you want to support <6.20, add this line:
# include("${ROOT_DIR}/modules/RootNewMacros.cmake")
# However, it was moved and included by default in 6.201

## Make the libraries

## Make the executables
add_executable(
    main "${SRC}/main.cpp"
    "${SRC}/sampling.cpp" "${SRC}/fitting.cpp"
    "${INC}/sampling.hpp" "${INC}/fitting.hpp"
    )

target_include_directories(main PRIVATE "${INC}")

target_compile_options(main PRIVATE -Werror -Wall -Wextra -fmax-errors=5)

target_link_libraries(main PUBLIC ROOT::RooFit ROOT::RooStats ROOT::Core)

## cmake and build flags 
set(CMAKE_CXX_STANDARD 17 CACHE STRING "C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_PLATFORM_INDEPENDENT_CODE ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")