cmake_minimum_required(VERSION 3.10)

project(blockchain)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

enable_language(C)
enable_language(CXX)

# add_subdirectory(third_party/boringssl)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    # ${CMAKE_CURRENT_SOURCE_DIR}/third_party/boringssl/include
)

add_library(blockchain
    ${CMAKE_CURRENT_SOURCE_DIR}/include/blockchain/Wallet.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/blockchain/SHA256.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/blockchain/Tx.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/blockchain/Chain.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Wallet.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Tx.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Chain.cpp
)

target_link_libraries(blockchain
    crypto
)