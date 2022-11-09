cmake_minimum_required(VERSION 3.10)

project(PROJECT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

enable_language(C)
enable_language(CXX)

add_subdirectory(blockchain)
add_subdirectory(http)
add_subdirectory(keyvalue)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/blockchain/include
  ${CMAKE_CURRENT_SOURCE_DIR}/http/include
)

add_executable(test-blockchain
  ${CMAKE_CURRENT_SOURCE_DIR}/test/test-blockchain.cpp
)

add_executable(test-http
  ${CMAKE_CURRENT_SOURCE_DIR}/test/test-http.cpp
)

target_include_directories(test-blockchain
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/blockchain/include
    ${CMAKE_CURRENT_SOURCE_DIR}/http/include
)

target_include_directories(test-http
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/http/include
)


target_link_libraries(test-blockchain
  PUBLIC
    blockchain
    crypto
)

target_link_libraries(test-http
  PUBLIC
    http
)