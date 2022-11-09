cmake_minimum_required(VERSION 3.10)

project(contract-lang)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(contractlang
    ${CMAKE_CURRENT_SOURCE_DIR}/include/compiler/Parser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/compiler/Tokenizer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/compiler/Token.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/compiler/Preprocessor.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/compiler/Scope.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Parser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Tokenizer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Preprocessor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Scope.cpp
)
