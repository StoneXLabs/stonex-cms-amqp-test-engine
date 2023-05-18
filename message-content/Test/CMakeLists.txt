cmake_minimum_required(VERSION 3.16)
project(message-content-test LANGUAGES CXX DESCRIPTION "stonex cms client message content lib tests")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)


file(GLOB sourceFiles ${PROJECT_SOURCE_DIR}/*.cpp)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sourceFiles})

add_executable(message-content-test main.cpp)              

target_include_directories(message-content-test PUBLIC ${PROJECT_SOURCE_DIR}/main.cpp )

target_link_libraries(message-content-test
	message-content
	secur32 
	crypt32 
	Ws2_32
	)

	
configure_file(${PROJECT_SOURCE_DIR}/test_message_property_bool.config ${CMAKE_CURRENT_BINARY_DIR}/test_message_property_bool.config COPYONLY)    
configure_file(${PROJECT_SOURCE_DIR}/test_message_property_byte.config ${CMAKE_CURRENT_BINARY_DIR}/test_message_property_byte.config COPYONLY)    
configure_file(${PROJECT_SOURCE_DIR}/test_message_property_double.config ${CMAKE_CURRENT_BINARY_DIR}/test_message_property_double.config COPYONLY)    
configure_file(${PROJECT_SOURCE_DIR}/test_message_property_float.config ${CMAKE_CURRENT_BINARY_DIR}/test_message_property_float.config COPYONLY)    
configure_file(${PROJECT_SOURCE_DIR}/test_message_property_int.config ${CMAKE_CURRENT_BINARY_DIR}/test_message_property_int.config COPYONLY)    
configure_file(${PROJECT_SOURCE_DIR}/test_message_property_long.config ${CMAKE_CURRENT_BINARY_DIR}/test_message_property_long.config COPYONLY)    
configure_file(${PROJECT_SOURCE_DIR}/test_message_property_short.config ${CMAKE_CURRENT_BINARY_DIR}/test_message_property_short.config COPYONLY)    
