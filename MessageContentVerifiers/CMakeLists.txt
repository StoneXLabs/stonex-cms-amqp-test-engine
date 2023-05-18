cmake_minimum_required(VERSION 3.16)
project(stonex-cms-amqp-message-content-verifier LANGUAGES CXX DESCRIPTION "stonex cms client test configuration")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)


file(GLOB sourceFiles ${PROJECT_SOURCE_DIR}/src/MessageContentVerifiers/*.cpp )
file(GLOB headerFiles ${PROJECT_SOURCE_DIR}/include/MessageContentVerifiers/*.h)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sourceFiles} ${headerFiles})

add_library(stonex-cms-amqp-message-content-verifier STATIC ${sourceFiles} ${headerFiles})              

target_include_directories(stonex-cms-amqp-message-content-verifier PUBLIC ${PROJECT_SOURCE_DIR}/include/ )

target_link_libraries(stonex-cms-amqp-message-content-verifier
	stonex-cms-amqp-message-content 
	apache-cms-interface
	CONAN_PKG::boost
	)