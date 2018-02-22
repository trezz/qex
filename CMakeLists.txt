cmake_minimum_required(VERSION 3.6)

# project name
project("qex")

# required C++ version
set (CMAKE_CXX_STANDARD 17)

# Additional cmake modules path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
include(GTest)

# Default installation directory
set(CMAKE_INSTALL_DIR "${CMAKE_BINARY_DIR}/_install")

# Default compilation flags for all targets
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -O3")

add_executable(qex
  ${CMAKE_SOURCE_DIR}/src/main.cpp
  ${CMAKE_SOURCE_DIR}/src/range.cpp
  ${CMAKE_SOURCE_DIR}/src/qex.cpp
)

install(
  TARGETS
    qex
  DESTINATION
    "${CMAKE_INSTALL_DIR}"
)

# Testing #####################################################################

add_executable(qex-tests
  ${CMAKE_SOURCE_DIR}/tests/range.cpp
  ${CMAKE_SOURCE_DIR}/tests/main.cpp
  ${CMAKE_SOURCE_DIR}/src/range.cpp
)

target_link_libraries(qex-tests
  gtest_main
)

target_include_directories(qex-tests
  PRIVATE
  "${CMAKE_SOURCE_DIR}/src"
)
