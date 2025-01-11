cmake_minimum_required(VERSION 3.10)

project(meta LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include_directories(include)

add_custom_target(meta_tests)

add_subdirectory(include/meta)
add_subdirectory(tests)

