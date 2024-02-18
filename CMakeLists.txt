cmake_minimum_required(VERSION 3.10)

project(project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(OPENSSL_DIR         "/usr/local/opt/openssl@3.1")

add_subdirectory(blockchain)

add_executable(test-client
	test/test-client.cpp
)

add_executable(test-key
	test/test-key.cpp
)

target_include_directories(test-key
    PUBLIC
    "${OPENSSL_DIR}/include"
	${CMAKE_CURRENT_SOURCE_DIR}/blockchain
)

target_include_directories(test-client
    PUBLIC
    "${OPENSSL_DIR}/include"
	${CMAKE_CURRENT_SOURCE_DIR}/blockchain
)

target_link_libraries(test-key
    PUBLIC
    	core
    	"${OPENSSL_DIR}/lib/libcrypto.dylib"
	"${OPENSSL_DIR}/lib/libssl.dylib"
    
)

target_link_libraries(test-client
    PUBLIC
    	core
    	"${OPENSSL_DIR}/lib/libcrypto.dylib"
	"${OPENSSL_DIR}/lib/libssl.dylib"
    
)





