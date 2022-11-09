cmake_minimum_required(VERSION 3.10)

project(PROJECT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

enable_language(C)
enable_language(CXX)

add_subdirectory(blockchain)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/blockchain/include
)

add_executable(test-blockchain
  ${CMAKE_CURRENT_SOURCE_DIR}/test/test-blockchain.cpp
)

target_include_directories(test-blockchain
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/blockchain/include
)

target_link_libraries(test-blockchain
  PUBLIC
    blockchain
    crypto
)