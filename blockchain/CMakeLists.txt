cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(OPENSSL_DIR         "/usr/local/opt/openssl@3.1")

add_library(core
	SHARED
	Block.cpp
	Message.cpp
	Key.cpp
	Wallet.cpp

	ByteBuffer.cpp
	Socket.cpp
	ServerSocket.cpp
)

target_include_directories(core
	PUBLIC
	"${OPENSSL_DIR}/include"
)

target_link_libraries(core
	PUBLIC
	"${OPENSSL_DIR}/lib/libcrypto.dylib"
	"${OPENSSL_DIR}/lib/libssl.dylib"
)
