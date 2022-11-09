cmake_minimum_required(VERSION 3.10)

project(HTTP)

add_subdirectory(third_party/json)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/json/include
)

add_library(http
    ${CMAKE_CURRENT_SOURCE_DIR}/include/http/Server.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Server.cpp
)
