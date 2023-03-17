# From: https://cliutils.gitlab.io/modern-cmake/chapters/basics.html

## Vesion and policy setup
# Debian stable 2023
cmake_minimum_required(VERSION 3.18)

if(${CMAKE_VERSION} VERSION_LESS 3.25)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.25)
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(TEST_ROOFIT_COMPILE_FLAGS -Werror -Wall -Wextra -pedantic)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(TEST_ROOFIT_COMPILE_FLAGS "${TEST_ROOFIT_COMPILE_FLAGS}" -O3)
else()
  set(TEST_ROOFIT_COMPILE_FLAGS "${TEST_ROOFIT_COMPILE_FLAGS}" -g)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(TEST_ROOFIT_COMPILE_FLAGS "${TEST_ROOFIT_COMPILE_FLAGS}" -ferror-limit=5)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  set(TEST_ROOFIT_COMPILE_FLAGS "${TEST_ROOFIT_COMPILE_FLAGS}" -fmax-errors=5)
endif()


## Project setup
project(TestRooFit
  LANGUAGES CXX
)
set(TEST_ROOFIT_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(TEST_ROOFIT_INC "${CMAKE_CURRENT_SOURCE_DIR}/include")

## find and link dependancies
find_package(ROOT 6.20 CONFIG REQUIRED)

## Make the libraries

## Make the executables
add_executable(
    main "${TEST_ROOFIT_SRC}/main.cpp"
    "${TEST_ROOFIT_SRC}/sampling.cpp" "${TEST_ROOFIT_SRC}/fitting.cpp"
    "${TEST_ROOFIT_INC}/sampling.hpp" "${TEST_ROOFIT_INC}/fitting.hpp"
    )
target_include_directories(main PRIVATE "${TEST_ROOFIT_INC}")
target_link_libraries(main PRIVATE ROOT::RooFit ROOT::RooStats ROOT::Core)
target_compile_options(main PRIVATE "${TEST_ROOFIT_COMPILE_FLAGS}")
target_compile_features(main PUBLIC cxx_std_17)
set_target_properties(main PROPERTIES CXX_EXTENSIONS OFF)
