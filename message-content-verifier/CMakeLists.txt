cmake_minimum_required(VERSION 3.16)
project(message-content-verifier LANGUAGES CXX DESCRIPTION "stonex cms client message content verifier lib")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)


file(GLOB sourceFiles ${PROJECT_SOURCE_DIR}/src/MessageContentVerifiers/*.cpp )
file(GLOB headerFiles ${PROJECT_SOURCE_DIR}/include/MessageContentVerifiers/*.h)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sourceFiles} ${headerFiles})

add_library(message-content-verifier STATIC)              

target_sources(message-content-verifier
    PRIVATE ${sourceFiles}
	PUBLIC ${headerFiles}
)

target_include_directories(message-content-verifier 
	PUBLIC ${PROJECT_SOURCE_DIR}/include
	PRIVATE ${PROJECT_SOURCE_DIR}/src
	)

target_link_libraries(message-content-verifier
	PUBLIC apache-cms-interface
	PRIVATE message-content 
	PRIVATE CONAN_PKG::boost
	)