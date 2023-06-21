cmake_minimum_required(VERSION 3.16)
project(message-decorator-test LANGUAGES CXX DESCRIPTION "stonex cms client message decorator lib tests")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)


file(GLOB sourceFiles ${PROJECT_SOURCE_DIR}/*.cpp)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sourceFiles})

add_executable(message-decorator-test main.cpp)              

target_include_directories(message-decorator-test PUBLIC ${PROJECT_SOURCE_DIR}/main.cpp )

target_link_libraries(message-decorator-test
	message-decorator
	CONAN_PKG::boost
	secur32 
	crypt32 
	Ws2_32
	)

	
configure_file(${PROJECT_SOURCE_DIR}/test_message_decorator.config ${CMAKE_CURRENT_BINARY_DIR}/test_message_decorator.config COPYONLY) 

configure_file(${PROJECT_SOURCE_DIR}/test_message_decorator.config ${CMAKE_CURRENT_BINARY_DIR}/../../bin/test_message_decorator.config COPYONLY) 
